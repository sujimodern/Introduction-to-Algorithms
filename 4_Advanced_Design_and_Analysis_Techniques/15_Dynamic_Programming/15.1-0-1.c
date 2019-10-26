#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum { n = 11 };

int max(int a, int b) { return (a > b) ? a : b; }

int cut_rod(size_t m, int p[m], int n) {
  if (!n) {
    return 0;
  }
  int q = INT_MIN;
  for (size_t i = 1; i <= n; i += 1) {
    q = max(q, p[i] + cut_rod(m, p, n - i));
  }
  return q;
}

int memorized_cut_rod_aux(size_t m, int p[m], int n, size_t l, int r[l]) {
  if (r[n] >= 0) {
    return r[n];
  }
  int q;
  if (!n) {
    q = 0;
  } else {
    q = INT_MIN;
    for (size_t i = 1; i <= n; i += 1) {
      q = max(q, p[i] + memorized_cut_rod_aux(m, p, n - i, l, r));
    }
  }
  r[n] = q;
  return q;
}

int memorized_cut_rod(size_t m, int p[m], int n) {
  int *r = malloc((n + 1) * sizeof(*r));
  for (size_t i = 0; i <= n; i += 1) {
    r[i] = INT_MIN;
  }
  int q = memorized_cut_rod_aux(m, p, n, n + 1, r);
  free(r);
  return q;
}

int bottom_up_cut_rod(size_t m, int p[m], int n) {
  int *r = malloc((n + 1) * sizeof(*r));
  r[0] = 0;
  int q;
  for (size_t j = 1; j <= n; j += 1) {
    q = INT_MIN;
    for (size_t i = 1; i <= j; i += 1) {
      q = max(q, p[i] + r[j - i]);
    }
    r[j] = q;
  }
  int s = r[n];
  free(r);
  return s;
}

int main(int argc, char *argv[argc + 1]) {
  int p[n] = {0,  1,  5,  8,  9, 10,
              17, 17, 20, 24, 30}; // one-based indexing, ignore the first
  int q;
  printf("cut_rod:\n");
  for (size_t i = 1; i < n; i += 1) {
    q = cut_rod(n, p, i);
    printf("q = %d\n", q);
  }
  printf("memorized_cut_rod\n");
  for (size_t i = 1; i < n; i += 1) {
    q = memorized_cut_rod(n, p, i);
    printf("q = %d\n", q);
  }
  printf("bottom_up_cut_rod\n");
  for (size_t i = 1; i < n; i += 1) {
    q = bottom_up_cut_rod(n, p, i);
    printf("i = %zu, q = %d\n", i, q);
  }
  return EXIT_SUCCESS;
}
