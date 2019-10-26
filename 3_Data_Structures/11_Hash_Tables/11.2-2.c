#include <stdio.h>
#include <stdlib.h>

enum { m = 9 };

typedef struct node node;
struct node {
  int key;
  node *prev;
  node *next;
};

typedef struct list list;
struct list {
  node *head;
};

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
  list *L = malloc(sizeof(*L));
  if (L) {
    *L = (list){
        .head = 0,
    };
  }
  return L;
}

void list_delete(list *L) {
  if (L) {
    node *current = L->head;
    node *next;
    while (current) {
      next = current->next;
      free(current);
      current = next;
    }
    free(L);
  }
}

node *list_search(list *L, int k) {
  node *x = L->head;
  while (x && (x->key != k)) {
    x = x->next;
  }
  return x;
}

void list_insert(list *L, node *x) {
  x->next = L->head;
  if (L->head) {
    L->head->prev = x;
  }
  L->head = x;
  x->prev = 0;
}

void list_delete_(list *L, node *x) {
  if (x->prev) {
    x->prev->next = x->next;
  } else {
    L->head = x->next;
  }
  if (x->next) {
    x->next->prev = x->prev;
  }
}

int h(int k) { return k % 9; }

void chained_hash_insert(size_t n, list T[n], node *x) {
  list_insert(&T[h(x->key)], x);
}

node *chained_hash_search(size_t n, list T[n], int k) {
  return list_search(&T[h(k)], k);
}

void chained_hash_delete(size_t n, list T[n], node *x) {
  list_delete_(&T[h(x->key)], x);
}

void print_chained_hash(size_t n, list T[n]) {
  char tails[3] = ",\n";
  char tails2[3] = " \n";
  for (size_t i = 0; i < n; i += 1) {
    list *L = &T[i];
    node *n = L->head;
    printf("%zu:%c", i, tails2[n == 0]);
    while (n) {
      printf("%d%c", n->key, tails[n->next == 0]);
      n = n->next;
    }
  }
}

int main(int argc, char *argv[argc + 1]) {
  node keys[m] = {
      {.key = 5},  {.key = 28}, {.key = 19}, {.key = 15}, {.key = 20},
      {.key = 33}, {.key = 12}, {.key = 17}, {.key = 10},
  };
  list hash_table[m] = {{0}};
  for (size_t i = 0; i < m; i += 1) {
    chained_hash_insert(m, hash_table, &keys[i]);
  }
  print_chained_hash(m, hash_table);
  return EXIT_SUCCESS;
}
