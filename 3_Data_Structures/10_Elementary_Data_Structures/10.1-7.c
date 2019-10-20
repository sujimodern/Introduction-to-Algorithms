#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct queue queue;
struct queue {
  int *set;
  size_t len;
  size_t head;
  size_t tail;
};

typedef struct stack2 stack2;
struct stack2 {
  queue *first;
  queue *second;
};

queue *queue_new(size_t len) {
  queue *q = malloc(sizeof(*q));
  if (q) {
    if (len) {
      *q = (queue){
          .set = calloc(len, sizeof(int)),
          .len = len,
      };
    } else {
      *q = (queue){0};
    }
  }
  return q;
}

void queue_delete(queue *q) {
  if (q) {
    free(q->set);
    free(q);
  }
}

void queue_enqueue(queue *q, int x) {
  q->set[q->tail] = x;
  if (q->tail == (q->len - 1)) {
    q->tail = 0;
  } else {
    q->tail += 1;
  }
}

int queue_dequeue(queue *q) {
  int x = q->set[q->head];
  if (q->head == (q->len - 1)) {
    q->head = 0;
  } else {
    q->head += 1;
  }
  return x;
}

stack2 *stack2_new(size_t len) {
  stack2 *s = malloc(sizeof(*s));
  if (s) {
    if (len) {
      *s = (stack2){
          .first = queue_new(len),
          .second = queue_new(len),
      };
    } else {
      *s = (stack2){0};
    }
  }
  return s;
}

void stack2_delete(stack2 *s) {
  if (s) {
    queue_delete(s->first);
    queue_delete(s->second);
    free(s);
  }
}

bool stack2_emtpy(stack2 *s) { return (s->first->head == s->first->tail); }

void stack2_push(stack2 *s, int x) { queue_enqueue(s->first, x); }

int stack2_pop(stack2 *s) {
  if (stack2_empty(s)) {
    fprintf(stderr, "underflow\n");
    return 0;
  } else {
    int x;
    while (!stack2_emtpy(s)) {
      x = queue_dequeue(s->first);
      queue_enqueue(s->second, x);
      // FIXME
    }
  }
}

int main(int argc, char *argv[argc + 1]) {
  size_t len = 12;
  stack2 *s = stack2_new(len);
  stack2_delete(s);
  return EXIT_SUCCESS;
}
