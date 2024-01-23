#include <assert.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "rtreap/rtreap.h"

#define N 200'000

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
    srand(time(0));
    RTreap* rtreap = rtreap_create(rand());
    std::ofstream file2("plots/output_2.data");

    int* arr = (int*)malloc(sizeof(int) * N);
    assert(arr);
    for (int i = 0; i < N; i++) {
        arr[i] = rand();
    }

    for (size_t i = 2; i <= N; ++i) {
        rtreap = rtreap_add(rtreap, arr[i]);
        if (i % 20000 == 0) {
            const int iter = 1000000;
            double time2 = wtime();
            for (int j = 0; j < iter; ++j) {
                int random = arr[rand() % i];
                rtreap_lookup(rtreap, random);
            }
            time2 = wtime() - time2;
            printf("%ld rtreap: %.10lf\n", i, (double)time2 / iter);
            file2 << i << ' ' << (double)time2 / iter << '\n';
        }
    }

    rtreap_free(rtreap);

    return 0;
}
