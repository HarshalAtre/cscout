// workspace thread_local_test
#pragma echo "Processing workspace thread_local_test\n"
// project thread_local_test
#pragma echo "Processing project thread_local_test\n"
#pragma project "thread_local_test"
#pragma block_enter
// file thread_local_test.c
#pragma echo "Processing file thread_local_test.c\n"
#pragma block_enter
#pragma clear_defines
#pragma clear_pragma process
#include ".cscout/host-defs.h"
#include ".cscout/host-incs.h"
#pragma process "thread_local_test.c"

#pragma block_exit
#pragma echo "Done processing file thread_local_test.c\n"

#pragma block_exit
#pragma echo "Done processing project thread_local_test\n"
