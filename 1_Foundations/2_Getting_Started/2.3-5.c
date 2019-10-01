#include <stdio.h>
#include <stdlib.h>

enum {n = 8};

int iterative_binary_search(size_t length, int A[length], int v, int low,
                            int high) {
  while (low <= high) {
    int mid = (low + high) / 2;
    if (v == A[mid]) {
      return mid;
    } else if (v > A[mid]) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

int recursive_binary_search(size_t length, int A[length], int v, int low,
                            int high) {
  if (low > high) {
    return -1;
  }
  int mid = (low + high) / 2;
  if (v == A[mid]) {
    return mid;
  } else if (v > A[mid]) {
    return recursive_binary_search(length, A, v, mid+1, high);
  } else {
    return recursive_binary_search(length, A, v, low, mid-1);
  }
}

int main(int argc, char* argv[argc+1]) { 
  int A[n] = {3, 9, 26, 38, 41, 52, 57, 49};

  int v, i;
  v = 52;
  i = iterative_binary_search(n, A, v, 0, n-1);
  printf("i = %d\n", i);

  v = 38;
  i = recursive_binary_search(n, A, v, 0, n-1);
  printf("i = %d\n", i);



  return EXIT_SUCCESS;
}
