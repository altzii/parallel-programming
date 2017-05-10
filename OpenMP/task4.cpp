//
// Created by Alexander Leontyev on 22.02.17.
//

#include <omp.h>
#include <stdio.h>

int main() {
    int a[10] = {0, -1, 3, 7, 5, 1, -3, 4, 1, 22};
    int b[10] = {1, 10, 2, 9, 3, 3, 5, 41, 3, 4};

    int min = a[0];
    int max = b[0];

#pragma omp parallel sections num_threads(2)
    {
#pragma omp section
        {
            for (int i = 0; i < 10; i++) {
                if (a[i] < min) { min = a[i]; }
            }
            printf("min in a is %d, omp_thread_num = %d\n", min, omp_get_thread_num());

        }

#pragma omp section
        {
            for (int i = 0; i < 10; i++) {
                if (b[i] > max) { max = b[i]; }
            }
            printf("max in a is %d, omp_thread_num = %d\n", max, omp_get_thread_num());
        }
    }
}