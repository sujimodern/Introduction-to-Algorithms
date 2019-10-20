#include <stdio.h>
#include <stdlib.h>

typedef enum queue_status queue_status;
enum queue_status { success = 0, underflow = 1, overflow = 2 };

typedef struct queue queue;
struct queue {
  int *set;
  size_t len;
  size_t head;
  size_t tail;
};

queue *queue_new(size_t len) {
  queue *q = malloc(sizeof(*q));
  if (q) {
    if (len) {
      *q = (queue){
          .set = calloc(len, sizeof(int)),
          .len = len,
          .head = 0,
          .tail = 0,
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

queue_status enqueue(queue *q, int x) {
  if (q->head == (q->tail + 1) % q->len) {
    return overflow;
  } else {
    q->set[q->tail] = x;
    if (q->tail == (q->len - 1)) {
      q->tail = 0;
    } else {
      q->tail += 1;
    }
    return success;
  }
}

queue_status dequeue(queue *q, int *x) {
  if (q->head == q->tail) {
    return underflow;
  } else {
    *x = q->set[q->head];
    if (q->head == (q->len - 1)) {
      q->head = 0;
    } else {
      q->head += 1;
    }
    return success;
  }
}

void print_queue(queue *q) {
  char tails[3] = ",\n";
  for (size_t i = 0; i < q->len; i += 1) {
    if ((q->head <= q->tail && q->head <= i && i < q->tail) ||
        (q->tail < q->head && (i < q->tail || q->head <= i))) {
      printf("%d%c", q->set[i], tails[i == (q->len - 1)]);
    } else {
      printf("_%c", tails[i == (q->len - 1)]);
    }
  }
}

int main(int argc, char *argv[argc + 1]) {
  size_t len = 3;
  queue *q = queue_new(len);
  int x;

  for (size_t i = 0; i < len; i += 1) {
    if (dequeue(q, &x) == underflow) {
      printf("underflow\n");
      break;
    }
  }

  for (size_t i = 0; i < len * 2; i += 1) {
    if (enqueue(q, i) == overflow) {
      printf("overflow\n");
      break;
    }
  }

  queue_delete(q);
  return EXIT_SUCCESS;
}
