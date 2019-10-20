#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack stack;
struct stack {
  int top;
  size_t len;
  int *set;
};

typedef struct queue2 queue2;
struct queue2 {
  stack *first;
  stack *second;
};

stack *stack_new(size_t len) {
  stack *s = malloc(sizeof(*s));
  if (s) {
    if (len) {
      *s = (stack){
          .set = calloc(len, sizeof(int)),
          .top = -1,
          .len = len,
      };
    } else {
      *s = (stack){0};
    }
  }
  return s;
}

void stack_delete(stack *s) {
  if (s) {
    free(s->set);
    free(s);
  }
}

bool stack_empty(stack *s) { return (s->top == -1) ? true : false; }

void stack_push(stack *s, int x) {
  s->top += 1;
  s->set[s->top] = x;
}

int stack_pop(stack *s) {
  if (stack_empty(s)) {
    fprintf(stderr, "underflow\n");
    return 0;
  } else {
    s->top -= 1;
    return s->set[s->top + 1];
  }
}

queue2 *queue2_new(size_t len) {
  queue2 *q = malloc(sizeof(*q));
  if (q) {
    if (len) {
      *q = (queue2){
          .first = stack_new(len),
          .second = stack_new(len),
      };
    } else {
      *q = (queue2){0};
    }
  }
  return q;
}

void queue2_delete(queue2 *q) {
  if (q) {
    stack_delete(q->first);
    stack_delete(q->second);
    free(q);
  }
}

void queue2_enqueue(queue2 *q, int x) {
  int t;
  while (!stack_empty(q->second)) {
    t = stack_pop(q->second);
    stack_push(q->first, t);
  }
  stack_push(q->first, x);
  while (!stack_empty(q->first)) {
    t = stack_pop(q->first);
    stack_push(q->second, t);
  }
}

int queue2_dequeue(queue2 *q) { return stack_pop(q->second); }

void print_stack(stack *s) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < s->len; i += 1) {
    printf("%d%c", s->set[i], tails[i == (s->len - 1)]);
  }
}

int main(int argc, char *argv[argc + 1]) {
  size_t len = 12;
  queue2 *q = queue2_new(len);

  queue2_enqueue(q, 1);
  queue2_enqueue(q, 2);
  queue2_enqueue(q, 3);
  queue2_enqueue(q, 4);
  queue2_enqueue(q, 5);
  int x = queue2_dequeue(q);
  printf("x = %d\n", x);

  queue2_delete(q);
  return EXIT_SUCCESS;
}
