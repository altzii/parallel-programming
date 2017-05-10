//
// Created by Alexander Leontjev on 10.03.17.
//

#include <omp.h>
#include <stdio.h>

int main() {
    int a[12];
    int b[12];
    int c[12];

#pragma omp parallel num_threads(3)
    {
#pragma omp for schedule(static, 3)
        for (int i = 0; i < 12; i++) {
            a[i] = 2;
            b[i] = 5;
            printf("thread_num is %d\n", omp_get_thread_num());
        }
    }

    for (int i = 0; i < 12; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");


    for (int i = 0; i < 12; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

#pragma omp parallel num_threads(4)
    {
#pragma omp for schedule(dynamic, 2)
        for (int i = 0; i < 12; i++) {
            c[i] = a[i] + b[i];
            printf("thread_num is %d\n", omp_get_thread_num());
        }
    }

    for (int i = 0; i < 12; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");
}