#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { len_word = 4, len_array = 16, num_alphabets = 26 };

void print_str_array(size_t n, size_t m, char A[n][m], char *comment) {
  if (comment) {
    puts(comment);
  }
  for (size_t i = 0; i < n; i += 1) {
    puts(A[i]);
  }
}

void copy_str_array(size_t n, size_t m, char S[n][m], char T[n][m]) {
  for (size_t i = 0; i < n; i += 1) {
    strcpy(T[i], S[i]);
  }
}

void counting_sort(size_t n, size_t m, char A[n][m], char B[n][m], size_t t) {
  int C[num_alphabets] = {0};
  for (size_t j = 0; j < n; j += 1) {
    C[A[j][t] - 'A'] += 1;
  }
  for (size_t i = 1; i < num_alphabets; i += 1) {
    C[i] += C[i - 1];
  }
  for (int j = n - 1; j >= 0; j -= 1) {
    strcpy(B[C[A[j][t] - 'A'] - 1], A[j]);
    C[A[j][t] - 'A'] -= 1;
  }
}

void radix_sort(size_t n, size_t m, char A[n][m], char B[n][m]) {
  char(*S)[n] = calloc(n, sizeof *S * m);
  char(*T)[n] = calloc(n, sizeof *T * m);
  copy_str_array(n, m, A, S);
  for (int i = m - 2; i >= 0; i -= 1) { /* the last index of string is m-2 */
    counting_sort(n, m, S, T, i);
    copy_str_array(n, m, T, S);
  }
  copy_str_array(n, m, T, B);
  free(T);
  free(S);
}

int main(int argc, char *argv[argc + 1]) {
  char words[len_array][len_word] = {
      "COW", "DOG", "SEA", "RUG", "ROW", "MOB", "BOX", "TAB",
      "BAR", "EAR", "TAR", "DIG", "BIG", "TEA", "NOW", "FOX",
  };
  char sorted[len_array][len_word] = {{0}};

  print_str_array(len_array, len_word, words, "before\n---");
  radix_sort(len_array, len_word, words, sorted);
  print_str_array(len_array, len_word, sorted, "after\n---");

  return EXIT_SUCCESS;
}
