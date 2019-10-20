#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack stack;
struct stack {
  size_t top;
  size_t len;
  int *set;
};

stack *stack_new(size_t len) {
  stack *s = malloc(sizeof(s));
  if (s) {
    if (len) {
      *s = (stack){
          .top = 0,
          .len = len,
          .set = malloc(sizeof(int[len])),
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

bool stack_empty(stack *s) { return (s->top) ? false : true; }

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

int main(int argc, char *argv[argc + 1]) {
  size_t len = 6;
  stack *s = stack_new(len);

  stack_push(s, 15);
  stack_push(s, 6);
  stack_push(s, 2);
  stack_push(s, 9);
  stack_push(s, 17);
  stack_push(s, 3);
  int x = stack_pop(s);
  printf("x = %d\n", x);

  stack_delete(s);
  return EXIT_SUCCESS;
}
