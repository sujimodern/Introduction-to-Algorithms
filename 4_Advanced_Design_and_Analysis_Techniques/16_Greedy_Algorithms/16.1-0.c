#include <stdio.h>
#include <stdlib.h>

enum {n = 11};

int recursive_activity_selector(size_t n, int s[n], int f[n], size_t k) {
  size_t m = k + 1;
  while ((m <= n) && (s[m] < f[k])) {
    m += 1; 
  }
  if (m <= n) {
    return 0;
  } else {
    return 0;
  }
  
}

int main(int argc, char *argv[argc + 1]) {
  int s[n] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
  int f[n] = {4, 5, 6, 7, 9, 9. 10, 11, 12, 14, 16};
  return EXIT_SUCCESS;
}
