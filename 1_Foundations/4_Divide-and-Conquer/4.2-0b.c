#include <stdio.h>
#include <stdlib.h>

enum {n = 4};

void print_matrix(size_t n, double A[n][n]) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < n; i += 1) {
    for (size_t j = 0; j < n; j += 1) {
      printf("%g%c", A[i][j], tails[j == n-1]);
    }
  }
}

void square_matrix_mutiply_recursive(size_t orig_n, size_t vir_n,
                                     double A[orig_n][orig_n], size_t ia, size_t ja,
                                     double B[orig_n][orig_n], size_t ib, size_t jb,
                                     double C[orig_n][orig_n], size_t ic, size_t jc) {
  int h;
  if (vir_n == 1) {
    C[ic][jc] += A[ia][ja] * B[ib][jb];
  } else {
    h = vir_n / 2;
    square_matrix_mutiply_recursive(orig_n, h, A, ia, ja, B, ib, jb, C, ic, jc);
    square_matrix_mutiply_recursive(orig_n, h, A, ia, ja+h, B, ib+h, jb, C, ic, jc);
    square_matrix_mutiply_recursive(orig_n, h, A, ia, ja, B, ib, jb+h, C, ic, jc+h);
    square_matrix_mutiply_recursive(orig_n, h, A, ia, ja+h, B, ib+h, jb+h, C, ic, jc+h);
    square_matrix_mutiply_recursive(orig_n, h, A, ia+h, ja, B, ib, jb, C, ic+h, jc);
    square_matrix_mutiply_recursive(orig_n, h, A, ia+h, ja+h, B, ib+h, jb, C, ic+h, jc);
    square_matrix_mutiply_recursive(orig_n, h, A, ia+h, ja, B, ib, jb+h, C, ic+h, jc+h);
    square_matrix_mutiply_recursive(orig_n, h, A, ia+h, ja+h, B, ib+h, jb+h, C, ic+h, jc+h);
  }
}

int main(int argc, char* argv[argc+1]) {
  double A[n][n] = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};
  double B[n][n] = {{5, 6, 7, 8}, {5, 6, 7, 8}, {5, 6, 7, 8}, {5, 6, 7, 8}};
  double C[n][n] = {{0}};

  square_matrix_mutiply_recursive(n, n, A, 0, 0, B, 0, 0, C, 0, 0);
  
  puts("A");
  print_matrix(n, A);
  puts("B");
  print_matrix(n, B);
  puts("C");
  print_matrix(n, C);

  return EXIT_SUCCESS;
}
