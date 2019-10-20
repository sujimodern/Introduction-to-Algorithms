#include <stdio.h>
#include <stdlib.h>

#define ILLUSTRATE_PARTITION 1

enum { seed = 0, n = 12 };

void print_array(size_t n, int A[n]) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < n; i += 1) {
    printf("%d%c", A[i], tails[i == n - 1]);
  }
}

void print_partition(size_t n, int A[n], int p, int i, int j, int r) {
  char tails[3] = ",\n";
  for (size_t k = 0; k < n; k += 1) {
    printf("%d", A[k]);
    if (k == p) {
      printf("(p)");
    }
    if (k == i) {
      printf("(i)");
    }
    if (k == j) {
      printf("(j)");
    }
    if (k == r) {
      printf("(r)");
    }
    printf("%c", tails[k == n - 1]);
  }
}

void exchange(int *a, int *b) {
  int t = *b;
  *b = *a;
  *a = t;
}

int partition(size_t n, int A[n], int p, int r) {
  int x = A[r];
  int i = p - 1;
  for (int j = p; j < r; j += 1) {
#if ILLUSTRATE_PARTITION
    print_partition(n, A, p, i, j, r);
#endif
    if (A[j] <= x) {
      i += 1;
      exchange(&A[i], &A[j]);
    }
  }
  exchange(&A[i + 1], &A[r]);
  return i + 1;
}

int randomized_partition(size_t n, int A[n], int p, int r) {
  srand(seed);
  int i = p + (rand() % (r - p + 1));
  printf("p = %d, r = %d, i = %d\n", p, r, i);
  exchange(&A[r], &A[i]);
  return partition(n, A, p, r);
}

void randomized_quicksort(size_t n, int A[n], int p, int r) {
  int q;
  if (p < r) {
    q = randomized_partition(n, A, p, r);
    randomized_quicksort(n, A, p, q - 1);
    randomized_quicksort(n, A, q + 1, r);
  }
}

int main(int argc, char *argv[argc + 1]) {
  int A[n] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};

  randomized_quicksort(n, A, 0, n - 1);

  return EXIT_SUCCESS;
}
