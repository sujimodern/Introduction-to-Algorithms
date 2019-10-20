#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
  node *next;
  int key;
};

typedef struct list list;
struct list {
  node *head;
};

typedef struct stack stack;
struct stack {
  list *data;
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
  list *l = malloc(sizeof(*l));
  if (l) {
    *l = (list){
        .head = 0,
    };
  }
  return l;
}

void list_delete(list *l) {
  node *current = l->head;
  node *next;
  while (current) {
    next = current->next;
    free(current);
    current = next;
  }
  free(l);
}

node *list_search(list *l, int key) {
  node *x = l->head;
  while (x && x->key != key) {
    x = x->next;
  }
  return x;
}

void list_insert(list *l, node *x) {
  x->next = l->head;
  l->head = x;
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

stack *stack_new() {
  stack *s = malloc(sizeof(*s));
  if (s) {
    *s = (stack){
        .data = list_new(),
    };
  }
  return s;
}

void stack_delete(stack *s) {
  if (s) {
    list_delete(s->data);
    free(s);
  }
}

bool stack_empty(stack *s) { return !(s->data->head); }

void stack_push(stack *s, int x) {
  node *n = node_new(x);
  list_insert(s->data, n);
}

int stack_pop(stack *s) {
  if (stack_empty(s)) {
    fprintf(stderr, "underflow\n");
    return 0;
  } else {
    int key = s->data->head->key;
    list_delete_(s->data, s->data->head);
    return key;
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

void print_stack(stack *s) { print_list(s->data); }

int main(int argc, char *argv[argc + 1]) {
  stack *s = stack_new();
  stack_push(s, 1);
  stack_push(s, 2);
  stack_push(s, 3);
  print_stack(s);
  int x = stack_pop(s);
  printf("x = %d\n", x);
  print_stack(s);
  stack_delete(s);
  return EXIT_SUCCESS;
}
