#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum {n = 8};

void print_array(size_t length, int A[length]) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < length; i += 1) {
    printf("%d%c", A[i], tails[i == length-1]);
  }
}

void merge(size_t length, int A[length], int p, int q, int r) {
  size_t n1 = q - p + 1;
  size_t n2 = r - q;
  int* L = malloc(sizeof(int[n1 + 1]));
  int* R = malloc(sizeof(int[n2 + 1]));
  size_t i, j;
  for (i = 0; i < n1; i += 1) {
    L[i] = A[p + i];     
  }
  for (j = 0; j < n2; j += 1) {
    R[j] = A[(q+1) + j];
  }
  L[n1] = INT_MAX;
  R[n2] = INT_MAX;
  i = 0;
  j = 0;
  for (size_t k = p; k <= r; k += 1) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i += 1;
    } else {
      A[k] = R[j];
      j += 1;
    }
  }
  free(L);
  free(R);
}

void merge_sort(size_t length, int A[length], int p, int r) {
  int q;
  if (p < r) {
    q = (p+r) / 2;
    merge_sort(n, A, p, q);
    merge_sort(n, A, q+1, r);
    merge(n, A, p, q, r);
  }
}

int main(int argc, char* argv[argc+1]) {
  int A[n] = {3, 41, 52, 26, 38, 57, 9, 49};

  print_array(n, A);
  merge_sort(n, A, 0, n-1);
  print_array(n, A);

  return EXIT_SUCCESS;
}
