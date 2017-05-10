//
// Created by Alexander Leontyev on 20.03.17.
//

#include <omp.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

int main() {
    int d[6][8];

    srand(time(NULL));

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            d[i][j] = rand() % 41 - 20;
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int min = d[0][0];
    int max = d[0][0];

#pragma omp parallel for num_threads(6)
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
#pragma omp critical(min)
            {
                if (d[i][j] < min) {
                    min = d[i][j];
                }
            }
#pragma omp critical(max)
            {
                if (d[i][j] > max) {
                    max = d[i][j];
                }
            }
        }
    }
    printf("max = %d\n", max);
    printf("min = %d\n", min);

    return 0;
}