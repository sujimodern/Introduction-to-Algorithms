#include <stdio.h>
#include <stdlib.h>

enum {n = 2};

void print_matrix(size_t n, double A[n][n]) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < n; i += 1) {
    for (size_t j = 0; j < n; j += 1) {
      printf("%g%c", A[i][j], tails[j == n-1]);
    }
  }
}

void square_matrix_add(size_t orig, size_t vir,
                       double A[orig][orig], size_t ia, size_t ja,
                       double B[orig][orig], size_t ib, size_t jb,
                       double C[orig][orig], size_t ic, size_t jc) {
  for (size_t i = 0; i < vir; i += 1) {
    for (size_t j = 0; j < vir; j += 1) {
      C[ic+i][jc+j] = A[ia+i][ja+j] + B[ib+i][jb+j];
    }
  }
}

void square_matrix_sub(size_t orig, size_t vir,
                            double A[orig][orig], size_t ia, size_t ja,
                            double B[orig][orig], size_t ib, size_t jb,
                            double C[orig][orig], size_t ic, size_t jc) {
  for (size_t i = 0; i < vir; i += 1) {
    for (size_t j = 0; j < vir; j += 1) {
      C[ic+i][jc+j] = A[ia+i][ja+j] - B[ib+i][jb+j];
    }
  }
}

void square_matrix_multiply_strassen(size_t orig, size_t vir,
                                    double A[orig][orig], size_t ia, size_t ja,
                                    double B[orig][orig], size_t ib, size_t jb,
                                    double C[orig][orig], size_t ic, size_t jc) {
  if (vir == 1) {
    C[ic][jc] = A[ia][ja] * B[ib][jb];
  } else {
    int h = vir / 2;
    double (*S1)[h] = calloc(h, sizeof *S1);
    double (*S2)[h] = calloc(h, sizeof *S2);
    double (*S3)[h] = calloc(h, sizeof *S3);
    double (*S4)[h] = calloc(h, sizeof *S4);
    double (*S5)[h] = calloc(h, sizeof *S5);
    double (*S6)[h] = calloc(h, sizeof *S6);
    double (*S7)[h] = calloc(h, sizeof *S7);
    double (*S8)[h] = calloc(h, sizeof *S8);
    double (*S9)[h] = calloc(h, sizeof *S9);
    double (*S10)[h] = calloc(h, sizeof *S10);
    square_matrix_sub(orig, h, B, ib, jb+h, B, ib+h, jb+h, S1, 0, 0);
    square_matrix_add(orig, h, A, ia, ja, A, ia, ja+h, S2, 0, 0);
    square_matrix_add(orig, h, A, ia+h, ja, A, ia+h, ja+h, S3, 0, 0);
    square_matrix_sub(orig, h, B, ib+h, jb, B, ib, jb, S4, 0, 0);
    square_matrix_add(orig, h, A, ia, ja, A, ia+h, ja+h, S5, 0, 0);
    square_matrix_add(orig, h, B, ib, jb, B, ib+h, jb+h, S6, 0, 0);
    square_matrix_sub(orig, h, A, ia, ja+h, A, ia+h, ja+h, S7, 0, 0);
    square_matrix_add(orig, h, B, ib+h, jb, B, ib+h, jb+h, S8, 0, 0);
    square_matrix_sub(orig, h, A, ia, ja, A, ia+h, ja, S9, 0, 0);
    square_matrix_add(orig, h, B, ib, jb, B, ib, jb+h, S10, 0, 0);

    double (*P1)[h] = calloc(h, sizeof *P1);
    double (*P2)[h] = calloc(h, sizeof *P2);
    double (*P3)[h] = calloc(h, sizeof *P3);
    double (*P4)[h] = calloc(h, sizeof *P4);
    double (*P5)[h] = calloc(h, sizeof *P5);
    double (*P6)[h] = calloc(h, sizeof *P6);
    double (*P7)[h] = calloc(h, sizeof *P7);
    square_matrix_multiply_strassen(orig, h, A, ia, ja, S1, 0, 0, P1, 0, 0);
    square_matrix_multiply_strassen(orig, h, S2, 0, 0, B, ib+h, jb+h, P2, 0, 0);
    square_matrix_multiply_strassen(orig, h, S3, 0, 0, B, ib, jb, P3, 0, 0);
    square_matrix_multiply_strassen(orig, h, A, ia+h, ja+h, S4, 0, 0, P4, 0, 0);
    square_matrix_multiply_strassen(orig, h, S5, 0, 0, S6, 0, 0, P5, 0, 0);
    square_matrix_multiply_strassen(orig, h, S7, 0, 0, S8, 0, 0, P6, 0, 0);
    square_matrix_multiply_strassen(orig, h, S9, 0, 0, S10, 0, 0, P7, 0, 0);

    square_matrix_add(orig, h, P5, 0, 0, P4, 0, 0, C, ic, jc);
    square_matrix_sub(orig, h, C, ic, jc, P2, 0, 0, C, ic, jc);
    square_matrix_add(orig, h, C, ic, jc, P6, 0, 0, C, ic, jc);
    square_matrix_add(orig, h, P1, 0, 0, P2, 0, 0, C, ic, jc+h);
    square_matrix_add(orig, h, P3, 0, 0, P4, 0, 0, C, ic+h, jc);
    square_matrix_add(orig, h, P5, 0, 0, P1, 0, 0, C, ic+h, jc+h);
    square_matrix_sub(orig, h, C, ic+h, jc+h, P3, 0, 0, C, ic+h, jc+h);
    square_matrix_sub(orig, h, C, ic+h, jc+h, P7, 0, 0, C, ic+h, jc+h);

    free(P1);
    free(P2);
    free(P3);
    free(P4);
    free(P5);
    free(P6);
    free(P7);

    free(S1);
    free(S2);
    free(S3);
    free(S4);
    free(S5);
    free(S6);
    free(S7);
    free(S8);
    free(S9);
    free(S10);
  }
}

int main(int argc, char* argv[argc+1]) {
  double A[n][n] = {{1, 3}, {7, 5}};
  double B[n][n] = {{6, 8}, {4, 2}};
  double C[n][n] = {{0}};

  square_matrix_multiply_strassen(n, n, A, 0, 0, B, 0, 0, C, 0, 0);
  
  puts("A");
  print_matrix(n, A);
  puts("B");
  print_matrix(n, B);
  puts("C");
  print_matrix(n, C);

  return EXIT_SUCCESS;
}
