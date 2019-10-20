#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum { root = 1, n = 13 };

void print_heap(size_t n, int A[n]) {
  char tails[3] = ",\n";
  int f = 2;
  for (size_t i = root; i < n; i += 1) {
    printf("%d%c", A[i], tails[i == f - 1 || i == n - 1]);
    if (i == f - 1) {
      f *= 2;
    }
  }
}

void exchange(int *a, int *b) {
  int t = *b;
  *b = *a;
  *a = t;
}

int heap_maximum(size_t n, int A[n]) { return A[root]; }

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

int heap_extract_max(size_t n, int A[n], size_t heap_size) {
  if (heap_size < 1) {
    exit(EXIT_FAILURE);
  }
  int max = A[root];
  A[root] = A[heap_size];
  heap_size -= 1;
  max_heapify(n, A, heap_size, root);
  return max;
}

void heap_increase_key(size_t n, int A[n], size_t i, int key) {
  if (key < A[i]) {
    exit(EXIT_FAILURE);
  }
  A[i] = key;
  while (i > root && A[i / 2] < A[i]) {
    exchange(&A[i], &A[i / 2]);
    i = i / 2;
  }
}

void max_heap_insert(size_t n, int A[n], size_t heap_size, int key) {
  heap_size += 1;
  A[heap_size] = INT_MIN;
  heap_increase_key(n, A, heap_size, key);
}

int main(int argc, char *argv[argc + 1]) {
  int A[n] = {0, 15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};

  print_heap(n, A);
  int max = heap_extract_max(n - 1, A, n - 1);
  printf("max = %d\n", max);

  return EXIT_SUCCESS;
}
