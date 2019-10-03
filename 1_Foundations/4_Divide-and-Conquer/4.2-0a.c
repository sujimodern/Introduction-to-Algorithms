#include <stdio.h>
#include <stdlib.h>

enum {n = 4};

typedef double matrix[n][n];

void print_matrix(matrix A) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < n; i += 1) {
    for (size_t j = 0; j < n; j += 1) {
      printf("%g%c", A[i][j], tails[j == n-1]);
    }
  }
}

void square_matrix_multiply(matrix A, matrix B, matrix C) {
  for (size_t i = 0; i < n; i += 1) {
    for (size_t j = 0; j < n; j += 1) {
      C[i][j] = 0;
      for (size_t k = 0; k < n; k += 1) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

int main(int argc, char* argv[argc+1]) {
  matrix A = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  matrix B = {{16, 15, 14, 13}, {12, 11, 10, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}};
  matrix C = {{0}};

  square_matrix_multiply(A, B, C);
  print_matrix(C);

  return EXIT_SUCCESS;
}
