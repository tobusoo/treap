#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "bstree/bstree.h"
#include "treap/treap.h"

#define N 100000

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
    FILE* file = fopen("plots/output_3.data", "w");
    FILE* file2 = fopen("plots/output_4.data", "w");
    Bstree* bstree = bstree_create(1, "value");

    for (size_t i = 2; i <= N; ++i) {
        rtreap = treap_add(rtreap, i, "value");
        bstree_add(bstree, i, "value");
        if (i % 10000 == 0) {
            const int iter = 100;
            double time2 = wtime();
            for (int j = 0; j < iter; ++j) {
                int random = getrand(1, i);
                treap_lookup(rtreap, random);
            }
            time2 = wtime() - time2;
            double time_bstree = wtime();
            for (int j = 0; j < iter; ++j) {
                int random = getrand(1, i);
                bstree_lookup(bstree, random);
            }
            time_bstree = wtime() - time_bstree;
            printf("%ld treap: %.10lf; bstree: %.10lf\n",
                   i,
                   (double)time2 / iter,
                   (double)time_bstree / iter);
            fprintf(file, "%ld %.10lf\n", i, (double)time2 / iter);
            fprintf(file2, "%ld %.10lf\n", i, (double)time_bstree / iter);
        }
    }

    treap_free(rtreap);
    bstree_delete_all(bstree);
    fclose(file2);
    fclose(file);

    return 0;
}
