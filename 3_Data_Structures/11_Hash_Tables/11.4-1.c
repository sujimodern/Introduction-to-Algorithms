#include <stdio.h>
#include <stdlib.h>

enum { m = 19 };

int h(int k, int i) {
  return 0;
}

void hash_insert(size_t n, int T[n], int k) {
  int i = 0;
  int j;
  do {
    j = h(k, i);
    if (T[j] == 0) {
      T[j] = k;
      return j;
    } else {
      i += 1;
    }
  } while (i == n);
  fprintf(stderr, "hash table overflow");
  exit(EXIT_FAILURE);
}

void hash_search(size_t n, int T[n], int k) {
  int i = 0;
  int j;
  do {
    j = h(k, i);
    if (T[j] == k) {
      return j;
    }
    i += 1;
  } while (T[j] == 0 || i == n);
  return 0;
}

int main(int argc, char *argc[argc + 1]) {
  int T[m] = {0};
  return EXIT_SUCCESS;
}
