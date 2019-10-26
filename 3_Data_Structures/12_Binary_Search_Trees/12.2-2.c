#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
  int key;
  node *p;
  node *left;
  node *right;
};

int main(int argc, char *argv[argc + 1]) {
  return EXIT_SUCCESS;
}
