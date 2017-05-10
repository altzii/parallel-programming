//
// Created by Alexander Leontyev on 20.03.17.
//

#include <omp.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

int main() {
    int a[30];

    srand(time(NULL));

    for (int i = 0; i < 30; ++i) {
        a[i] = rand() % 41 - 20;
        printf("%d ", a[i]);
    }

    printf("\n");

    int count = 0;

#pragma omp parallel num_threads(4)
    {
#pragma omp for
        for (int i = 0; i < 30; ++i) {
            if (a[i] % 9 == 0) {
                printf("a[%d] = %d\n", i, a[i]);
#pragma omp atomic
                count++;
            }
        }
    }
    printf("count = %d\n", count);

    return 0;
}