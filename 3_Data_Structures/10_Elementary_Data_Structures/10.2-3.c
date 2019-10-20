#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
  int key;
  node *next;
};

typedef struct list list;
struct list {
  node *head;
};

// FIXME
// typedef struct queue queue;
// struct queue {
// };

node *node_new(int key) {
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

list *list_new() {
  list *l = malloc(sizeof(*l));
  if (l) {
    *l = (list){
        .head = 0,
    };
  }
  return l;
}

void list_delete(list *l) {
  if (l) {
    node *current = l->head;
    node *next;
    while (current) {
      next = current->next;
      free(current);
      current = next;
    }
    free(l);
  }
}

void list_insert(list *l, node *x) {
  x->next = l->head;
  l->head = x;
}

node *list_search(list *l, int key) {
  node *x = l->head;
  while (x && (x->key != key)) {
    x = x->next;
  }
  return x;
}

void list_delete_(list *l, node *x) {
  node *current = l->head;
  node *prev = 0;
  while (current != x) {
    prev = current;
    current = current->next;
  }
  if (current == x) {
    if (prev) {
      prev->next = current->next;
    } else {
      l->head = current->next;
    }
    free(current);
  }
}

void print_list(list *l) {
  char tails[3] = ",\n";
  node *cursor = l->head;
  while (cursor) {
    printf("%d%c", cursor->key, tails[cursor->next == 0]);
    cursor = cursor->next;
  }
}

int main(int argc, char *argv[argc + 1]) {
  list *l = list_new();
  node *n1 = node_new(1);
  node *n2 = node_new(2);
  node *n3 = node_new(3);
  list_insert(l, n1);
  list_insert(l, n2);
  list_insert(l, n3);
  print_list(l);
  list_delete(l);
  return EXIT_SUCCESS;
}
