//
// Created by Alexander Leontjev on 05.03.17.
//

#include <omp.h>
#include <stdio.h>

int main() {
    int a[10] = {0, -1, 3, 7, 5, 1, -3, 4, 1, 22};
    int b[10] = {1, 10, 2, 9, 3, 3, 5, 41, 3, 4};

    int sum1 = 0;
    int sum2 = 0;

#pragma omp parallel for reduction(+:sum1), reduction(+:sum2)
    for (int i = 0; i < 10; i++) {
        sum1 += a[i];
        sum2 += b[i];
    }

    printf("average from a = %f\n", (double) sum1 / 10);
    printf("average from b = %f\n", (double) sum2 / 10);
}