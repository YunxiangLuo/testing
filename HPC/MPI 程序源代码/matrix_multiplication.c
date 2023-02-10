#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ROW_A 3
#define COL_A 3
#define COL_B 3

int a[ROW_A][COL_A], b[COL_A][COL_B], c[ROW_A][COL_B];

void fill_matrix(int m[ROW_A][COL_A]) {
    for (int i = 0; i < ROW_A; i++) {
        for (int j = 0; j < COL_A; j++) {
            m[i][j] = i + j;
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size, rows;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        fill_matrix(a);
        fill_matrix(b);
    }

    rows = ROW_A / size;
    int a_part[rows][COL_A], c_part[rows][COL_B];
    MPI_Scatter(a, rows * COL_A, MPI_INT, a_part, rows * COL_A, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, COL_A * COL_B, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COL_B; j++) {
            c_part[i][j] = 0;
            for (int k = 0; k < COL_A; k++) {
                c_part[i][j] += a_part[i][k] * b[k][j];
            }
        }
    }

    MPI_Gather(c_part, rows * COL_B, MPI_INT, c, rows * COL_B, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < ROW_A; i++) {
            for (int j = 0; j < COL_B; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
