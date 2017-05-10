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

    int max = 0;

#pragma omp parallel num_threads(4)
    {
#pragma omp for
        for (int i = 0; i < 30; ++i) {
            if (a[i] % 7 == 0) {
#pragma omp critical
                {
                    if (a[i] > max) {
                        max = a[i];
                    }
                }
            }
        }
    }
    printf("max = %d\n", max);

    return 0;
}