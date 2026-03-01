/*
 * Test file for _Thread_local support in CScout.
 *
 * These patterns are taken from real-world C11 code:
 *   - tinycthread (static _Thread_local)
 *   - various logging/error handling libraries (extern _Thread_local)
 *   - C11 standard examples (_Thread_local alone)
 *
 * C11 6.7.1: _Thread_local may appear with static or extern.
 */

#include <stdlib.h>

/* --- Pattern 1: static _Thread_local (from tinycthread) --- */

struct TSSData {
    void *value;
    int key;
    struct TSSData *next;
};

static _Thread_local struct TSSData *tss_head = NULL;
static _Thread_local struct TSSData *tss_tail = NULL;

/* --- Pattern 2: _Thread_local alone (file scope, C11 standard) --- */

_Thread_local int error_code = 0;
_Thread_local const char *error_message = NULL;

/* --- Pattern 3: extern _Thread_local (declared in another TU) --- */

extern _Thread_local int global_thread_id;
extern _Thread_local unsigned long thread_sequence;

/* --- Pattern 4: _Thread_local static (reversed order) --- */

_Thread_local static int local_counter = 0;
_Thread_local static char thread_name[64];

/* --- Pattern 5: _Thread_local with qualifiers --- */

_Thread_local volatile int thread_signal_flag = 0;
static _Thread_local const int thread_version = 1;

/* --- Pattern 6: _Thread_local with pointer types --- */

static _Thread_local void *thread_context = NULL;
extern _Thread_local int *thread_errno_ptr;

/* --- Functions using the thread-local variables --- */

static void tss_cleanup(void)
{
    struct TSSData *data;
    for (data = tss_head; data != NULL; data = data->next) {
        if (data->value != NULL) {
            data->value = NULL;
        }
    }
    tss_head = NULL;
    tss_tail = NULL;
}

int get_error_code(void)
{
    return error_code;
}

void set_error(int code, const char *msg)
{
    error_code = code;
    error_message = msg;
}

static void increment_counter(void)
{
    local_counter++;
}

int get_counter(void)
{
    return local_counter;
}

void init_thread(void *ctx)
{
    thread_context = ctx;
    thread_signal_flag = 0;
    local_counter = 0;
    tss_cleanup();
}

/* Definitions for the extern _Thread_local variables */
_Thread_local int global_thread_id = 0;
_Thread_local unsigned long thread_sequence = 0;
_Thread_local int *thread_errno_ptr = NULL;

int main(void)
{
    set_error(0, "ok");
    init_thread(NULL);
    increment_counter();
    global_thread_id = 1;
    thread_sequence = 100;
    return get_error_code() + get_counter();
}
