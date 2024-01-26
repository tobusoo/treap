#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "treap/treap.h"

#define N 200000

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main()
{
    srand(time(0));
    Treap* rtreap = treap_create(1, "value");
    FILE* file = fopen("plots/output_1.data", "w");

    for (size_t i = 2; i <= N; ++i) {
        rtreap = treap_add(rtreap, i, "value");
        if (i % 20000 == 0) {
            const int iter = 1000000;
            double time2 = wtime();
            for (int j = 0; j < iter; ++j) {
                int random = getrand(0, i);
                treap_lookup(rtreap, random);
            }
            time2 = wtime() - time2;
            printf("%ld rtreap: %.10lf\n", i, (double)time2 / iter);
            fprintf(file, "%ld %.10lf\n", i, (double)time2 / iter);
        }
    }

    treap_free(rtreap);
    fclose(file);

    return 0;
}