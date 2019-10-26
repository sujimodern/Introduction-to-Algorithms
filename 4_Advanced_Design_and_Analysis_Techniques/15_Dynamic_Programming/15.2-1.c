#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum { n = 6 };

void print_2darray(size_t len, int a[len][len]) {
  char tails[3] = "\t\n";
  for (size_t i = 1; i < len; i += 1) {
    for (size_t j = 1; j < len; j += 1) {
      printf("%d%c", a[i][j], tails[j == (len - 1)]);
    }
  }
}

void matrix_chain_order(size_t len, int p[len], int m[len][len],
                        int s[len][len]) {
  size_t n = len - 1;
  for (size_t l = 2; l <= n; l += 1) {
    for (size_t i = 1; i <= n - l + 1; i += 1) {
      size_t j = i + l - 1;
      m[i][j] = INT_MAX;
      for (size_t k = i; k < j; k += 1) {
        int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
        if (q < m[i][j]) {
          m[i][j] = q;
          s[i][j] = k;
        }
      }
    }
  }
}

void print_optimal_parens(size_t len, int s[len][len], size_t i, size_t j) {
  if (i == j) {
    printf("A%zu", i);
  } else {
    printf("(");
    print_optimal_parens(len, s, i, s[i][j]);
    print_optimal_parens(len, s, s[i][j] + 1, j);
    printf(")");
  }
}

int main(int argc, char *argv[argc + 1]) {
  int p[n + 1] = {5, 10, 3, 12, 5, 50, 6};
  int m[n + 1][n + 1] = {{0}}; // one-based indexing, ignore the first element
  int s[n + 1][n + 1] = {{0}}; // one-based indexing, ignore the first element
  matrix_chain_order(n + 1, p, m, s);
  print_optimal_parens(n + 1, s, 1, 6);
  printf("\n");
  return EXIT_SUCCESS;
}
