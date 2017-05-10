//
// Created by Alexander Leontyev on 22.02.17.
//

#include <omp.h>
#include <stdio.h>

int main() {
    omp_set_num_threads(8);

#pragma omp parallel
    {
        printf("Hello world! My identificator is %d out of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
    return 0;
}