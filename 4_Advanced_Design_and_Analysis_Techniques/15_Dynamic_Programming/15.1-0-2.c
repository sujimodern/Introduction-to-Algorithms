#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum { n = 11 };

int max(int a, int b) { return (a > b) ? a : b; }

void extended_bottom_up_cut_rod(size_t m, int p[m], int n, int r[n + 1],
                                int s[n + 1]) {
  r[0] = 0;
  int q;
  for (size_t j = 1; j <= n; j += 1) {
    q = INT_MIN;
    for (size_t i = 1; i <= j; i += 1) {
      if (q < p[i] + r[j - i]) {
        q = p[i] + r[j - i];
        s[j] = i;
      }
    }
    r[j] = q;
  }
}

void print_cut_rod_solution(size_t m, int p[m], int n, int r[n + 1],
                            int s[n + 1]) {
  extended_bottom_up_cut_rod(m, p, n, r, s);
  while (n > 0) {
    printf("%d\n", s[n]);
    n -= s[n];
  }
}

int main(int argc, char *argv[argc + 1]) {
  int p[n] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
  int r[n + 1] = {0};
  int s[n + 1] = {0};
  print_cut_rod_solution(n, p, 7, r, s);
  return EXIT_SUCCESS;
}
