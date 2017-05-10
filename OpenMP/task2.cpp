//
// Created by Alexander Leontyev on 22.02.17.
//

#include <omp.h>
#include <stdio.h>

int main() {
    int nthreads = 3;
    omp_set_num_threads(nthreads);

#pragma omp parallel if (nthreads > 2 )
    {
        if (omp_in_parallel()) {
            printf("My identificator is %d out of %d\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }

    nthreads = 1;
    omp_set_num_threads(nthreads);
#pragma omp parallel if (nthreads > 2)
    {
        if (omp_in_parallel()) {
            printf("My identificator is %d out of %d\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }
    return 0;
}