#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum {n = 6};

void print_array(size_t length, int A[length]) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < length; i += 1) {
    printf("%d%c", A[i], tails[i == length-1]);
  }
}

void selection_sort(size_t length, int A[length]) {
  int smallest, temp;
  for (size_t j = 0; j < length-1; j += 1) {
    smallest = j;
    for (size_t i = j; i < length; i += 1) {
      if (A[i] < A[smallest]) {
        smallest = i;
      }
    }
    temp = A[j];
    A[j] = A[smallest];
    A[smallest] = temp;
  }
}

int main(int argc, char* argv[argc+1]) {
  int A[n] = {31, 41, 59, 26, 41, 58};

  print_array(n, A);
  selection_sort(n, A);
  print_array(n, A);

  return EXIT_SUCCESS;
}
