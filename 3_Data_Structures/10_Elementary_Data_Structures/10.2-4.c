#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
  int key;
  node *next;
};

typedef struct list list;
struct list {
  node *nil;
};

node *node_new(int key) {
  node *n = malloc(sizeof *n);
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

list *list_new() {
  list *l = malloc(sizeof *l);
  node *nil = node_new(0);
  nil->next = nil;
  if (l) {
    *l = (list){
        .nil = nil,
    };
  }
  return l;
}

void list_delete(list *l) {
  if (l) {
    node *current = l->nil->next;
    node *next;
    while (current != l->nil) {
      next = current->next;
      node_delete(current);
      current = next;
    }
    node_delete(l->nil);
    free(l);
  }
}

void list_insert(list *l, node *x) {
  x->next = l->nil->next;
  l->nil->next = x;
}

void list_delete_(list *l, node *x) {}

node *list_search(list *l, int key) {
  node *x = l->nil->next;
  int orig = l->nil->key;
  l->nil->key = !key; // assign definitely different value from the key.
  while (x->key != key) {
    x = x->next;
  }
  l->nil->key = orig;
  return x;
}

int main(int argc, char *argv[argc + 1]) {
  list *l = list_new();
  node *n1 = node_new(1);
  node *n2 = node_new(2);
  node *n3 = node_new(3);
  list_insert(l, n1);
  list_insert(l, n2);
  list_insert(l, n3);
  node *x = list_search(l, 2);
  printf("x = %p (n2 = %p)\n", x, n2);
  list_delete(l);
  return EXIT_SUCCESS;
}
