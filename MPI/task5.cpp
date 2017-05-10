//
// Created by a.leontyev on 03.05.17.
//

#include <cstdlib>
#include <mpi.h>
#include <ctime>

int main() {
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n = 10;
    int *a = new int[n];
    int *b = new int[n];
    srand(time(NULL));

    for (int i = 0; i < n && !rank; i++) {
        a[i] = rand() % 5 + 1;
        b[i] = rand() % 5 + 1;
        printf("%d\t%d\n", a[i], b[i]);
    }

    int *len = new int[size];
    int *index = new int[size];
    len[0] = n / size;
    index[0] = 0;
    int sch = n;

    for (int i = 1; i < size; i++) {
        sch -= len[i - 1];
        len[i] = sch / (size - i);
        index[i] = index[i - 1] + len[i - 1];
    }

    int procN = len[rank];
    int *procA = new int[procN];
    int *procB = new int[procN];
    int sum = 0, procSum = 0;

    MPI_Scatterv(a, len, index, MPI_INT, procA, procN, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatterv(b, len, index, MPI_INT, procB, procN, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < procN; i++) {
        procSum += procA[i] * procB[i];
    }

    MPI_Reduce(&procSum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (!rank)
        printf("result %d", sum);

    MPI_Finalize();
    return 1;
}