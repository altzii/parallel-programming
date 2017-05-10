//
// Created by a.leontyev on 03.05.17.
//

#include <cstdlib>
#include <mpi.h>

#define MASTER 0
#define SIZE 10

int main(int argc, char **argv) {
    int world_rank, world_size, max = 0;
    int *a = new int[SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Status status;

    int buf_size = SIZE / world_size;
    int *buf = new int[buf_size];

    if (world_rank == MASTER) {
        for (int i = 0; i < SIZE; ++i) {
            a[i] = rand() % 100;
        }
        for (int j = 1; j < world_size; ++j) {
            MPI_Send(&a[(j - 1) * buf_size], buf_size, MPI_INT, j, 0, MPI_COMM_WORLD);
        }
        for (int i = (world_size - 1) * SIZE; i < SIZE; ++i) {
            if (a[i] > max)
                max = a[i];
        }
        int local_max = max;

        for (int j = 1; j < world_size; ++j) {
            MPI_Recv(&local_max, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            if (local_max > max) {
                max = local_max;
            }
        }
        printf("max = %d\n", max);
    } else {
        MPI_Recv(&buf[0], buf_size, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &status);
        for (int i = 0; i < buf_size; i++) {
            if (buf[i] > max) {
                max = buf[i];
            }
        }
        MPI_Send(&max, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
