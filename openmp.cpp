#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000

int A[N][N], B[N][N];
int C[N][N];

//int A[N][N] = { {1,2,3,4},{5,6,7,8},{9,1,2,3},{4,5,6,7} };
//int B[N][N] = { {1,2,3,4},{5,6,7,8},{9,1,2,3},{4,5,6,7} };

float t1, t2, time_start, time_final;

int main(int argc, char** argv) {
    int i, j, k;
    //Find max number of threads
    int threads = omp_get_num_procs();
    printf("Max threads found: %d\n", threads);

    srand(time(NULL) + threads);

    //Create matrices
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            B[i][j] = rand() % 10;
        }
    }

//  printf("Matrix A: \n");
//  for (i = 0; i < N; i++) {
//      for (j = 0; j < N; j++) {
//          printf(" %d", A[i][j]);
//      }
//      printf("\n");
//  }
//  printf("______________________________________\n");
//  printf("\nMatrix B: \n");
//  for (i = 0; i < N; i++) {
//     for (j = 0; j < N; j++) {
//          printf(" %d", B[i][j]);
//      }
//        printf("\n");
//  }
    //Start counting
    double start = omp_get_wtime();
    printf("Counting...\n");
	for (int i = 1; i <= threads; i++) {
	t1 = omp_get_wtime();
		omp_set_num_threads(i);

	#pragma omp parallel for private(i,j,k)
	    for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
		    C[i][j] = 0;
		    for (k = 0; k < N; k++) {
			C[i][j] += A[i][k] * B[k][j];
		    }
		}
	}
		t2 = omp_get_wtime();
	printf("Threads: %d, time: % .6f\n", i, t2 - t1);
	}

//  Print C
//  for (i = 0; i < N; i++) {
//      for (j = 0; j < N; j++) {
//          printf("%d ", C[i][j]);
//      }
//      printf("\n");
//  }

    double end = omp_get_wtime();
    printf("Total time taken: %f\n", end - start);

    return 0;
}
