//
// Created by Alexander Leontyev on 22.03.17.
//

#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main() {
#pragma omp parallel num_threads(8)
    {
        sleep(7 - omp_get_thread_num());
        printf("Hello world! My identificator is %d out of %d\n", omp_get_thread_num(), omp_get_num_threads());

    }

    return 0;
}