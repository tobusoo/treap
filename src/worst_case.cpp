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
    RTreap* rtreap = rtreap_create(1);
    std::ofstream file("plots/output_1.data");

    for (size_t i = 2; i <= N; ++i) {
        rtreap = rtreap_add(rtreap, i);
        if (i % 20000 == 0) {
            const int iter = 1000000;
            double time2 = wtime();
            for (int j = 0; j < iter; ++j) {
                int random = getrand(0, i);
                rtreap_lookup(rtreap, random);
            }
            time2 = wtime() - time2;
            printf("%ld rtreap: %.10lf\n", i, (double)time2 / iter);
            file << i << ' ' << (double)time2 / iter << '\n';
        }
    }

    rtreap_free(rtreap);

    return 0;
}