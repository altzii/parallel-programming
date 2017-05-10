//
// Created by a.leontyev on 03.05.17.
//

#include <cstdlib>
#include <mpi.h>
#include <ctime>

int main() {
    double x, y, r;
    r = 1;
    int n = 0, rank;
    const long N = 100000;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(rank);
    for (int i = 0; i < N; i++) {
        x = rand() % 1000000;
        x /= 500000.0 * r;
        y = rand() % 1000000;
        y /= 500000.0 * r;
        if ((x - r) * (x - r) + (y - r) * (y - r) <= r * r)
            n++;
    }
    printf("%d    Pi = %f\n", n, (double) n / N * 4.0);

    MPI_Finalize();
    return 1;
}