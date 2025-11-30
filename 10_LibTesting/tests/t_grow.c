#include "test_utils.h"
#include "buf.h"

int main(void) {
    int count_pass = 0;
    int count_fail = 0;
    long *ai = NULL;

    /* buf_grow(), buf_trunc() */
    buf_grow(ai, 1000);
    TEST("grow 1000", buf_capacity(ai) == 1000);
    TEST("size 0 (grow)", buf_size(ai) == 0);

    buf_trunc(ai, 100);
    TEST("trunc 100", buf_capacity(ai) == 100);

    buf_free(ai);
    return count_fail != 0;
}
