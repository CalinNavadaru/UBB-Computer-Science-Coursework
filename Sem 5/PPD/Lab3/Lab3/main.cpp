#include <iostream>
#include <mpi.h>
#include <cstdlib>

void print(int* a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
}


int main(int argc, char** argv)
{
    // MPI_Init(&argc, &argv);
    //
    // int world_size;
    // MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    //
    // int world_rank;
    // MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // std::cout << "Hello world from processes" << world_rank
    // << "out of" << world_size << "processes! "<< std::endl;
    //
    // const int n = 10;
    // int a[n], b[n], c[n];
    // int start, end;
    // MPI_Status status;
    // if (world_rank == 0) {
    //     for (int i = 0; i < n; i++) {
    //         a[i] = rand() % 10;
    //         b[i] = rand() % 10;
    //     }
    //
    //     int p = world_size - 1;
    //     int step = n / p, rest = n % p;
    //     start = 0;
    //     end = step;
    //     for (int i = 1; i < world_size; i++) {
    //         if (rest) {
    //             end++;
    //             rest--;
    //         }
    //         MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    //         MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    //         MPI_Send(a + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
    //         MPI_Send(b + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
    //         start = end;
    //         end += step;
    //     }
    //
    //     for (int i = 1; i < world_size; i++) {
    //         MPI_Recv(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
    //         MPI_Recv(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
    //         MPI_Recv(c + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
    //     }
    //
    //     print(a, n);
    //     print(b, n);
    //     print(c, n);
    // }
    // else {
    //     MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    //     MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    //     MPI_Recv(a + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    //     MPI_Recv(b + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    //
    //     for (int i = start; i < end; i++) {
    //         c[i] = a[i] + b[i];
    //     }
    //
    //     MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    //     MPI_Send(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    //     MPI_Send(c + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD);
    // }
    // MPI_Finalize();
    // return 0;
    // MPI_Init(&argc, &argv);
    //
    // int world_size;
    // MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    //
    // int world_rank;
    // MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // // std::cout << "Hello world from processes" << world_rank
    // // << "out of" << world_size << "processes! "<< std::endl;
    //
    // //MPI_Scatterv, MPI_Gatherv
    //
    // const int n = 10;
    // int a[n], b[n], c[n];
    // MPI_Status status;
    // if (world_rank == 0) {
    //     for (int i = 0; i < n; i++) {
    //         a[i] = rand() % 10;
    //         b[i] = rand() % 10;
    //     }
    // }
    // int chunk_size = n / world_size;
    // int *aux_a = new int[chunk_size];
    // int *aux_b = new int[chunk_size];
    // int *aux_c = new int[chunk_size];
    // MPI_Scatter(a, chunk_size, MPI_INT, aux_a, chunk_size, MPI_INT,0 ,MPI_COMM_WORLD);
    // MPI_Scatter(b, chunk_size, MPI_INT, aux_a, chunk_size, MPI_INT,0 ,MPI_COMM_WORLD);
    // for (int i = 0; i < chunk_size; i++) {
    //     aux_c[i] = aux_a[i] + aux_b[i];
    // }
    // MPI_Gather(aux_c, chunk_size, MPI_INT, c, chunk_size, MPI_INT,0 , MPI_COMM_WORLD);
    // if (world_rank == 0) {
    //     print(a, n);
    //     print(b, n);
    //     print(c, n);
    // }
    //
    // delete[] aux_a;
    // delete[] aux_b;
    // delete[] aux_c;
    //
    // MPI_Finalize();

    //ISend, Ireceive
    // int nprocs, myrank;
    // MPI_Status status;
    // MPI_Init(&argc, &argv);
    // MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    // MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    // int value = myrank * 10;
    // if (myrank == 0)
    //     MPI_Recv(&value, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
    // if (myrank == 1)
    //     MPI_Send(&value, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
    // if (myrank == 0)
    //     printf("%d", value);
    // MPI_Finalize();
    // return 0;
    int nprocs, myrank;
    int i, value = 0;
    int *a, *b;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if (myrank == 0)
    {
        a = (int*)malloc(nprocs * sizeof(int));
        for (int i = 0; i < nprocs; i++) a[i] = i + 1;
    }
    b = (int*)malloc(sizeof(int));
    MPI_Scatter(a, 1, MPI_INT, b, 1, MPI_INT, 0,MPI_COMM_WORLD);
    b[0] += myrank;
    MPI_Reduce(&b[0], &value, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myrank == 0)
    {
        printf("value = %d \n", value);
        free(a);
    }
    MPI_Finalize();
    free(b);
    return 0;
}
