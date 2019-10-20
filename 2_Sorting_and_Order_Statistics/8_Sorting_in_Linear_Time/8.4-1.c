#include <stdio.h>
#include <stdlib.h>

enum { base = 10, n = 10 };

typedef struct linked_list linked_list;
struct linked_list {
  double val;
  linked_list *next;
};

void linked_list_init(linked_list *ll, double val) {
  if (ll) {
    if (val) {
      *ll = (linked_list){
          .val = val,
          .next = 0,
      };
    } else {
      *ll = (linked_list){0};
    }
  }
  return ll;
}
void linked_list_destroy(linked_list *ll) {
  while (ll) {
    linked_list *next = ll->next;
    free(ll);
    ll = next;
  }
}

void print_array(size_t n, double A[n]) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < n; i += 1) {
    printf("%g%c", A[i], tails[i == n - 1]);
  }
}

void bucket_sort(size_t n, double A[n], double C[n]) {
  linked_list B[base] = {0};
  for (size_t i = 0; i < n; i += 1) {
    int j = (int)(base * A[i]);
    B[j]
  }
}

int main(int argc, char *argv[argc + 1]) {
  double A[n] = {.79, .13, .16, .64, .39, .20, .89, .53, .71, .42};
  double C[n] = {0};

  print_array(n, A);
  bucket_sort(n, A, C);

  return EXIT_SUCCESS;
}
