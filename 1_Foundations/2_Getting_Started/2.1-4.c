#include <stdio.h>
#include <stdlib.h>

enum {n = 6};

void print_binary_array(size_t n, short A[n]) {
  for (int i = 0; i < n; i += 1) {
    printf("%d", A[i]);
  }
  printf("\n");
}

void sum_binary_array(size_t n, short A[n], short B[n], short C[n+1]) {
  short temp = 0;
  short carry = 0;
  for (int i = n-1; i >= 0; i -= 1) {
    temp = A[i] + B[i] + carry;
    carry = (temp >= 2);
    C[i+1] = temp % 2;
  }
  C[0] = carry;
}

int main(int argc, char* argv[argc+1]) {
  short A[n] = {0, 1, 0, 1, 1, 1};
  short B[n] = {1, 0, 1, 0, 1, 1};
  short C[n+1] = {0};

  print_binary_array(n, A); 
  print_binary_array(n, B); 
  sum_binary_array(n, A, B, C);
  print_binary_array(n+1, C); 

  return EXIT_SUCCESS;
}
