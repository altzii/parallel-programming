//
// Created by Alexander Leontyev on 22.03.17.
//

#include <omp.h>
#include <stdio.h>

int main() {
    int count = 7;

#pragma omp parallel num_threads(8)
    {
        double condition = true;

        while (condition) {
            if (omp_get_thread_num() == count) {
                printf("Hello world! My identificator is %d out of %d\n", omp_get_thread_num(), omp_get_num_threads());
                count -= 1;
                condition = false;
                break;
            }
        }
    }

    return 0;
}
