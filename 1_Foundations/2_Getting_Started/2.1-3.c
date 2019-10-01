#include <stdio.h>
#include <stdlib.h>

enum {n = 6};

int linear_search(size_t length, int A[length], int v) {
  int i = -1;
  for (size_t j = 0; j < length; j += 1) {
    if (A[j] == v) {
      i = j;
      break;
    }
  }
  return i;
}

int main(int argc, char* argv[argc+1]) {
  int A[n] = {31, 41, 59, 26, 41, 58}; 

  int i = linear_search(n, A, 26);
  printf("i = %d\n", i);

  return EXIT_SUCCESS;
}
