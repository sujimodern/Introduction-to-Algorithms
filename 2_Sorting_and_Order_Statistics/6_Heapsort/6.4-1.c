#include <stdio.h>
#include <stdlib.h>

enum { root = 1, n = 10 };

void print_array(size_t n, int A[n]) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < n; i += 1) {
    printf("%d%c", A[i], tails[i == n - 1]);
  }
}

void print_heap(size_t n, int A[n]) {
  char tails[3] = ",\n";
  size_t f = 2;
  for (size_t i = root; i < n; i += 1) {
    printf("%d%c", A[i], tails[i == f - 1]);
    if (i == f) {
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

void heap_sort(size_t n, int A[n]) {
  size_t heap_size = n;
  build_max_heap(n, A);
  for (size_t i = n; i > root; i -= 1) {
    exchange(&A[root], &A[i]);
    heap_size -= 1;
    max_heapify(n, A, heap_size, root);
  }
}

int main(int argc, char *argv[argc + 1]) {
  int A[n] = {0, 5, 13, 2, 25, 7, 17, 20, 8, 4};

  print_array(n, A);
  heap_sort(n - 1, A); /* take account of the index, 1 ... n-1 */
  print_array(n, A);

  return EXIT_SUCCESS;
}
