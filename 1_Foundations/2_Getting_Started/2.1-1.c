#include <stdio.h>
#include <stdlib.h>

enum {n = 6};

void print_array(size_t length, int A[length]) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < length; i += 1) {
    printf("%d%c", A[i], tails[i == length - 1]);
  }
}

void insertion_sort(size_t length, int A[length]) {
  for (size_t j = 1; j < length; j += 1) {
    int key = A[j];
    int i = j - 1;
    while (i >= 0 && A[i] > key) {
      A[i+1] = A[i];
      i = i - 1;
    }
    A[i+1] = key;
  }
}

int main(int argc, char* argv[argc+1]) {
  int A[n] = {31, 41, 59, 26, 41, 58};

  print_array(n, A);
  insertion_sort(n, A);
  print_array(n, A);

  return EXIT_SUCCESS;
}
