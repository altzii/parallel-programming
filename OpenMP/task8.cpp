//
// Created by Alexander Leontjev on 14.03.17.
//

#include <omp.h>
#include <stdio.h>

int main() {
    double a[16000];

    for (int i = 0; i < 16000; i++) {
        a[i] = i;
    }

    double b[16000];

    double start_time = omp_get_wtime();
    double end_time;

#pragma omp parallel num_threads(8)
    {
#pragma omp schedule(static) for
        for (int i = 0; i < 16000; i++) {
            if (i != 0 | i != 15999)
                b[i] = (a[i] + a[i - 1] + a[i + 1]) / 3.0;
            else
                b[i] = i;
        }
    }
    end_time = omp_get_wtime();
    printf("schedule(static) time is %f \n", (end_time - start_time));


#pragma omp parallel num_threads(8)
    {
#pragma omp schedule(dynamic) for
        for (int i = 0; i < 16000; i++) {
            if (i != 0 | i != 15999)
                b[i] = (a[i] + a[i - 1] + a[i + 1]) / 3.0;
            else
                b[i] = i;
        }
        start_time = end_time;
        end_time = omp_get_wtime();
    }
    printf("schedule(dynamic) time is %f \n", (end_time - start_time));

#pragma omp parallel num_threads(8)
    {
#pragma omp schedule(guided) for
        for (int i = 0; i < 16000; i++) {
            if (i != 0 | i != 15999)
                b[i] = (a[i] + a[i - 1] + a[i + 1]) / 3.0;
            else
                b[i] = i;
        }
        start_time = end_time;
        end_time = omp_get_wtime();
    }
    printf("schedule(guided) time is %f \n", (end_time - start_time));

#pragma omp parallel num_threads(8)
    {
#pragma omp schedule(auto) for
        for (int i = 0; i < 16000; i++) {
            if (i != 0 | i != 15999)
                b[i] = (a[i] + a[i - 1] + a[i + 1]) / 3.0;
            else
                b[i] = i;
        }
        start_time = end_time;
        end_time = omp_get_wtime();
    }
    printf("schedule(auto) time is %f \n", (end_time - start_time));

    return 0;
}


