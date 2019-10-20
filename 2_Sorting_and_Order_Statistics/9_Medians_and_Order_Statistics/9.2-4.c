#include <stdio.h>
#include <stdlib.h>

enum {n = 10};

void exchange(int* a, int* b) {
  int t = *b;
  *b = *a;
  *a = t;
}

int partition(size_t n, int A[n], int p, int r) {
  int x, i;
  x = A[r];
  i = p - 1;
  for (size_t j = p; j < r-1; j += 1) {
    if (A[j] <= x) {
      i += 1;
      exchange(&A[i], &A[j]);
    }
  }
  exchange(&A[i+1], &A[r]);
  return i+1;
}

int randomized_partition(size_t n, int A[n], int p, int r) {
  int i = rand() % (r - p + 1) + p;
  exchange(&A[r], &A[i]);
  return partition(n, A, p, r);
}

int randomized_select(size_t n, int A[n], int p, int r, int i) {
  int q, k;
  if (p == r) {
    return A[p];
  }
  q = randomized_partition(n, A, p, r);
  k = q - p + 1;
  if (i == k) {
    return A[q];
  } else if (i < k) {
    return randomized_select(n, A, p, q-1, i);
  } else {
    return randomized_select(n, A, q+1, r, i-k);
  }
}

int main(int argc, char* argv[argc+1]) {
  srand(0);
  int A[n] = {3, 2, 9, 0, 7, 5, 4, 8, 6, 1};
  int r = randomized_select(n, A, 0, n-1, 0);
  printf("r = %d\n", r);
  return EXIT_SUCCESS;
}
