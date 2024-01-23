#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "rtreap/rtreap.h"
#include "treap/treap.h"

#define N 200'000

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
    Treap* treap = treap_create(1, 1);
    RTreap* rtreap = rtreap_create(1);
    std::ofstream file("../plots/output_1.data");
    std::ofstream file2("../plots/output_2.data");

    for (size_t i = 2; i <= N; ++i) {
        treap = treap_add(treap, i, i);
        rtreap = rtreap_add(rtreap, i);
        if (i % 20000 == 0) {
            double time = wtime();
            Treap* node1 = NULL;
            RTreap* node2 = NULL;
            const int iter = 1000;
            for (int j = 0; j < iter; ++j) {
                int random = getrand(0, i);
                node1 = treap_lookup(treap, random);
            }
            time = wtime() - time;
            double time2 = wtime();
            for (int j = 0; j < iter; ++j) {
                int random = getrand(0, i);
                node2 = rtreap_lookup(rtreap, random);
            }
            time2 = wtime() - time2;
            printf("%ld treap: %lf; rtreap: %lf\n",
                   i,
                   (double)time / iter * 1000,
                   (double)time2 / iter * 1000);
            file << i << ' ' << (double)time / iter * 1000 << '\n';
            file2 << i << ' ' << (double)time2 / iter * 1000 << '\n';
        }
    }

    rtreap_free(rtreap);
    treap_free(treap);

    return 0;
}