//
// Created by Alexander Leontjev on 03.03.17.
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
        }
    }

#pragma omp parallel sections
    {
#pragma omp section
        {
            int sum = 0;

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    sum += d[i][j];
                }
            }
            printf("average is %f from %d thread\n", (double) sum / 48, omp_get_thread_num());
        }
#pragma omp section
        {
            int max = d[0][0];
            int min = d[0][0];

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    if (d[i][j] < min) {
                        min = d[i][j];
                    }
                    if (d[i][j] > max) {
                        max = d[i][j];
                    }
                }
            }
            printf("max is %d, min is %d from %d thread\n", max, min, omp_get_thread_num());
        }
#pragma omp section
        {
            int count = 0;

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8; j++) {
                    if (d[i][j] % 3 == 0) {
                        count++;
                    }
                }
            }
            printf("count is %d from %d thread\n", count, omp_get_thread_num());
        }
    }
}