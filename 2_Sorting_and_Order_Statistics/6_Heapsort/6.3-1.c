#include <stdio.h>
#include <stdlib.h>

enum { root = 1, n = 10 };

void print_heap(size_t n, int A[n]) {
  size_t f = 2;
  char tails[3] = ",\n";
  for (size_t i = root; i < n; i += 1) {
    printf("%d%c", A[i], tails[i + 1 == f || i == n - 1]);
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

void max_heapify(size_t n, int A[n], size_t heap_size, size_t i) {
  size_t l, r, largest;
  l = 2 * i;
  r = 2 * i + 1;
  if (l <= heap_size && A[l] > A[i]) {
    largest = l;
  } else {
    largest = i;
  }
  if (r <= heap_size && A[r] > A[largest]) {
    largest = r;
  }
  if (largest != i) {
    exchange(&A[i], &A[largest]);
    max_heapify(n, A, heap_size, largest);
  }
}

void build_max_heap(size_t n, int A[n]) {
  size_t heap_size = n;
  for (size_t i = n / 2; i >= root; i -= 1) {
    max_heapify(n, A, heap_size, i);
  }
}

int main(int argc, char *argv[argc + 1]) {
  int A[n] = {0, 5, 3, 17, 10, 84, 19, 6, 22, 9};

  print_heap(n, A);
  build_max_heap(n - 1, A); // from 1 to n-1
  print_heap(n, A);

  return EXIT_SUCCESS;
}
