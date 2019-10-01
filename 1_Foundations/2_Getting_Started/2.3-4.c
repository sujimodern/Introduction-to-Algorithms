#include <stdio.h>
#include <stdlib.h>

enum {n = 8};

void print_array(size_t length, int A[length]) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < length; i += 1) {
    printf("%d%c", A[i], tails[i == length-1]);
  }
}
void last_sort(size_t length, int A[length]) {
  int key = A[length-1];
  int i = length - 2;
  while (i >= 0 && A[i] > key) {
    A[i+1] = A[i];
    i -= 1;
  }
  A[i+1] = key;
}

void recursive_insert_sort(size_t length, int A[length]) {
  if (length > 1) {
    recursive_insert_sort(length-1, A);
    last_sort(length-1, A);
  }
}

int main(int argc, char* argv[argc+1]) {
  int A[n] = {3, 41, 52, 26, 38, 57, 9, 49};

  print_array(n, A);
  recursive_insert_sort(n, A);
  print_array(n, A);

  return EXIT_SUCCESS;
}
