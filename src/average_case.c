#include <assert.h>
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

int main()
{
    srand(time(0));
    Treap* rtreap = treap_create(rand(), "value");
    FILE* file = fopen("plots/output_2.data", "w");

    int* arr = (int*)malloc(sizeof(int) * N);
    assert(arr);
    for (int i = 0; i < N; i++) {
        arr[i] = rand();
    }

    for (size_t i = 2; i <= N; ++i) {
        rtreap = treap_add(rtreap, arr[i], "value");
        if (i % 20000 == 0) {
            const int iter = 1000000;
            double time2 = wtime();
            for (int j = 0; j < iter; ++j) {
                int random = arr[rand() % i];
                treap_lookup(rtreap, random);
            }
            time2 = wtime() - time2;
            printf("%ld treap: %.10lf\n", i, (double)time2 / iter);
            fprintf(file, "%ld %.10lf\n", i, (double)time2 / iter);
        }
    }

    treap_free(rtreap);
    fclose(file);

    return 0;
}
