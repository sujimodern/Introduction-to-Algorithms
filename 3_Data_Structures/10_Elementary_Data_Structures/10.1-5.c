#include <stdio.h>
#include <stdlib.h>

typedef struct deque deque;
struct deque {
  int *set;
  size_t len;
  size_t head;
  size_t tail;
};

deque *deque_new(size_t len) {
  deque *d = malloc(sizeof(*d));
  if (d) {
    if (len) {
      *d = (deque){
          .set = calloc(len, sizeof(int)),
          .len = len,
      };
    } else {
      *d = (deque){0};
    }
  }
  return d;
}

void deque_delete(deque *d) {
  if (d) {
    free(d->set);
    free(d);
  }
}

void enqueue_head(deque *d, int x) {
  if (!d->head) {
    d->head = d->len - 1;
  } else {
    d->head -= 1;
  }
  d->set[d->head] = x;
}

void enqueue_tail(deque *d, int x) {
  d->set[d->tail] = x;
  if (d->tail == (d->len - 1)) {
    d->tail = 0;
  } else {
    d->tail += 1;
  }
}

int dequeue_head(deque *d) {
  int x = d->set[d->head];
  if (d->head == (d->len - 1)) {
    d->head = 0;
  } else {
    d->head += 1;
  }
  return x;
}

int dequeue_tail(deque *d) {
  if (!d->tail) {
    d->tail = d->len - 1;
  } else {
    d->tail -= 1;
  }
  int x = d->set[d->tail];
  return x;
}

void print_deque(deque *d) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < d->len; i += 1) {
    if ((d->head <= d->tail && (d->head <= i && i < d->tail)) ||
        (d->tail < d->head && (i < d->tail && d->head <= i))) {
      printf("%d%c", d->set[i], tails[i == d->len - 1]);
    } else {
      printf("_%c", tails[i == d->len - 1]);
    }
  }
}

int main(int argc, char *argv[argc + 1]) {
  size_t len = 6;
  deque *d = deque_new(len);

  enqueue_tail(d, 1);
  print_deque(d);
  enqueue_tail(d, 2);
  print_deque(d);
  enqueue_tail(d, 3);
  print_deque(d);
  enqueue_tail(d, 4);
  print_deque(d);
  dequeue_head(d);
  print_deque(d);
  dequeue_head(d);
  print_deque(d);
  enqueue_head(d, 0);
  print_deque(d);
  enqueue_head(d, -1);
  print_deque(d);
  dequeue_head(d);
  print_deque(d);
  dequeue_head(d);
  print_deque(d);

  deque_delete(d);
  return EXIT_SUCCESS;
}
