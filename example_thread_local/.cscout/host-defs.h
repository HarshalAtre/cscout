/* 
 * Standard definitions for CScout
 * C11 version with _Thread_local support
 */

#define __DATE__  "Mar 01 2026"
#define __TIME__ "12:00:00"
#define __FILE__ "UNKNOWN.c"
#define __LINE__ 1
#define __STDC__ 1
#define __STDC_VERSION__ 201112L

/* To make it appear as a read-only identifier */
int main();
/* To avoid unused include file warnings */
static void _cscout_dummy1(void) { _cscout_dummy1(); }
