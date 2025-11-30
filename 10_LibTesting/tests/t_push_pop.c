#include "test_utils.h"
#include "buf.h"

int main(void) {
    int count_pass = 0;
    int count_fail = 0;

    /* buf_push(), [] operator */
    long *ai = NULL;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);

    TEST("size 10000", buf_size(ai) == 10000);

    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    TEST("match 10000", match == 10000);
    buf_free(ai);

    /* buf_pop() */
    float *a = NULL;
    buf_push(a, 1.1f);
    buf_push(a, 1.2f);
    buf_push(a, 1.3f);
    buf_push(a, 1.4f);

    TEST("size 4", buf_size(a) == 4);
    TEST("pop 3", buf_pop(a) == (float)1.4f);

    /* Trunc inside pop test logic from original file */
    buf_trunc(a, 3);
    TEST("size 3", buf_size(a) == 3);
    TEST("pop 2", buf_pop(a) == (float)1.3f);
    TEST("pop 1", buf_pop(a) == (float)1.2f);
    TEST("pop 0", buf_pop(a) == (float)1.1f);
    TEST("size 0 (pop)", buf_size(a) == 0);

    buf_free(a);
    return count_fail != 0;
}
