#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define SIZE 1000

int main() {
    int matrix[SIZE][SIZE];

    srand(time(NULL));

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = rand() % 100 - 50;
        }

    int vector[SIZE];

    for (int i = 0; i < SIZE; i++) {
        vector[i] = rand() % 41 - 20;
    }

    int result[SIZE];

    double start_time = omp_get_wtime();
    
#pragma omp parallel for schedule (auto)
    for (int i = 0; i < SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < SIZE; j++)
            result[i] += matrix[i][j] * vector[j];
    }
    printf("parallel time %f\n", omp_get_wtime() - start_time);

    start_time = omp_get_wtime();
    for (int i = 0; i < SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < SIZE; j++)
            result[i] += matrix[i][j] * vector[j];
    }
    printf("sequential time %f\n", omp_get_wtime() - start_time);

    return 0;
}
