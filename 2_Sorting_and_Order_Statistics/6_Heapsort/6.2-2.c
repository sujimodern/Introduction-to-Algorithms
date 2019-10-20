#include <stdio.h>
#include <stdlib.h>

enum { root = 1, n = 15 };

void print_heap(size_t n, int A[n]) {
  size_t f = 2;
  char tails[3] = ",\n";
  for (size_t i = root; i <= n; i += 1) {
    printf("%d%c", A[i], tails[i + 1 == f || i == n]);
    if (f == i) {
      f *= 2;
    }
  }
}

void exchange(int *a, int *b) {
  int t = *b;
  *b = *a;
  *a = t;
}

void min_heapify(size_t n, int A[n], size_t heap_size, size_t i) {
  size_t l, r, smallest;
  l = 2 * i;
  r = 2 * i + 1;
  if (l <= heap_size && A[l] < A[i]) {
    smallest = l;
  } else {
    smallest = i;
  }
  if (r <= heap_size && A[r] < A[smallest]) {
    smallest = r;
  }
  if (smallest != i) {
    exchange(&A[i], &A[smallest]);
    min_heapify(n, A, heap_size, smallest);
  }
}

int main(int argc, char *argv[argc + 1]) {
  int A[n] = {0, 27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
  size_t heap_size = n - 1;

  print_heap(n, A);
  min_heapify(n, A, heap_size, root);
  print_heap(n, A);

  return EXIT_SUCCESS;
}
