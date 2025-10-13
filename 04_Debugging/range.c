#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Without parameters - displays help\n");
        printf("With one parameter N - displays the sequence [0, 1,  … N-1] in a column\n");
        printf("With two - M, N - in turn [M, M+1, … N-1]\n");
        printf("With complications - M, N, S - in sequence [M, M+S, M+2S, … N-1]\n");
        return 0;
    }
    int m, n, s;
    if (argc == 2) {
         m = 0;
         n = atoi(argv[1]);
         s = 1;
    } else if (argc == 3) {
         m = atoi(argv[1]);
         n = atoi(argv[2]);
         s = 1;
    } else {
         m = atoi(argv[1]);
         n = atoi(argv[2]);
         s = atoi(argv[3]);
    }

    int i = m;
    int d = m <= n ? 1 : -1;
    while (i*d < n*d) {
        printf("%d\n", i);
        i += s;
    }

    return 0;
}
