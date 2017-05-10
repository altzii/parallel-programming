//
// Created by Alexander Leontyev on 20.03.17.
//

#include <omp.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

int main() {
    int matrix[1000][1000];

    srand(time(NULL));

    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++) {
            matrix[i][j] = rand() % 41 - 20;
        }

    int vector[1000];

    for (int i = 0; i < 1000; i++) {
        vector[i] = rand() % 41 - 20;
    }

    int result[1000];

    double start_time = omp_get_wtime();
#pragma omp parallel for schedule (auto)
    for (int i = 0; i < 1000; i++) {
        result[i] = 0;
        for (int j = 0; j < 1000; j++)
            result[i] += matrix[i][j] * vector[j];
    }
    printf("parallel time %f\n", omp_get_wtime() - start_time);

    start_time = omp_get_wtime();
    for (int i = 0; i < 1000; i++) {
        result[i] = 0;
        for (int j = 0; j < 1000; j++)
            result[i] += matrix[i][j] * vector[j];
    }
    printf("sequential time %f\n", omp_get_wtime() - start_time);

    return 0;
}
