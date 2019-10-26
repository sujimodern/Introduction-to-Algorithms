#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum { m = 10 };

typedef struct node node;
struct node {
  size_t key;
  int data;
};

node *node_new(size_t key) {
  node *n = malloc(sizeof(*n));
  if (n) {
    *n = (node){
      .key = key,
    };
  }
  return n;
}

void node_delete(node *n) {
  if (n) {
    free(n);
  }
}

node *direct_address_search(size_t n, node *T[n], size_t k) {
  return T[k];
}

void direct_address_insert(size_t n, node *T[n], node *x) {
  T[x->key] = x;
}

void direct_address_delete(size_t n, node *T[n], node *x) {
  T[x->key] = 0;
}

int main(int argc, char *argv[argc + 1]) {
  node* direct_address_table[m] = {0};
  node *n2 = node_new(2);
  node *n3 = node_new(3);
  node *n5 = node_new(5);
  node *n8 = node_new(8);
  n2->data = 67;
  n3->data = 19;
  n5->data = 81;
  n8->data = 20;
  direct_address_insert(m, direct_address_table, n2); 
  direct_address_insert(m, direct_address_table, n3); 
  direct_address_insert(m, direct_address_table, n5); 
  direct_address_insert(m, direct_address_table, n8); 
  int max = INT_MIN;
  node *n;
  for (size_t k = 0; k < m; k += 1) {
    n = direct_address_search(m, direct_address_table, k);
    if (n && n->data > max) {
      max = n->data;
    }
  }
  printf("max = %d\n", max);
  node_delete(n2);
  node_delete(n3);
  node_delete(n5);
  node_delete(n8);
  return EXIT_SUCCESS;
}
