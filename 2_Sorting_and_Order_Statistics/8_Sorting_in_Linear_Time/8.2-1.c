#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum { n = 11 };

void print_array(size_t n, int A[n]) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < n; i += 1) {
    printf("%d%c", A[i], tails[i == n - 1]);
  }
}

void counting_sort(size_t n, int A[n], int B[n], size_t k) {
  int *C = calloc(k + 1, sizeof *C);
  for (size_t j = 0; j < n; j += 1) {
    C[A[j]] += 1;
  }
  for (size_t i = 1; i < k + 1; i += 1) {
    C[i] += C[i - 1];
  }
  for (int j = n - 1; j >= 0; j -= 1) {
    B[C[A[j]] - 1] = A[j]; /* C returns 1-based indexing */
    C[A[j]] = C[A[j]] - 1;
  }
  free(C);
}

int main(int argc, char *argv[argc + 1]) {
  int A[n] = {6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
  int B[n] = {0};
  int k = 6;

  print_array(n, A);
  counting_sort(n, A, B, k);
  print_array(n, B);

  return EXIT_SUCCESS;
}
