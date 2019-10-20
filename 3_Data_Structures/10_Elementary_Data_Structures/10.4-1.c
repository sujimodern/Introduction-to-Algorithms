#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { xlen = 60, ylen = 30 };

typedef struct node node;
struct node {
  int key;
  node *p;
  node *left;
  node *right;
};

typedef struct binary_tree binary_tree;
struct binary_tree {
  node *root;
};

node *node_new(int key) {
  node *n = malloc(sizeof(*n));
  if (n) {
    *n = (node){
        .key = key,
        .p = 0,
        .left = 0,
        .right = 0,
    };
  }
  return n;
}

void node_delete(node *n) {
  if (n) {
    printf("n->key = %d, deleted\n", n->key);
    free(n);
  }
}

binary_tree *binary_tree_new() {
  binary_tree *t = malloc(sizeof(*t));
  if (t) {
    *t = (binary_tree){
        .root = 0,
    };
  }
  return t;
}

void binary_tree_delete2(node *n) {
  if (n) {
    if (n->left) {
      binary_tree_delete2(n->left);
    }
    if (n->right) {
      binary_tree_delete2(n->right);
    }
    node_delete(n);
  }
}

void binary_tree_delete(binary_tree *t) {
  if (t) {
    node *n = t->root;
    if (n) {
      binary_tree_delete2(n);
    }
    free(t);
  }
}

void print_binary_tree2(node *n, size_t ylen, size_t xlen, char buf[ylen][xlen],
                        size_t y0, size_t x0) {
  printf("y0 = %zu, x0 = %zu\n", y0, x0);
  sprintf(&(buf[y0][x0]), "%d", n->key);
  if (n->left) {
    buf[y0 + 1][x0 - 1] = '/';
    print_binary_tree2(n->left, ylen, xlen, buf, y0 + 2, x0 - 2);
  }
  if (n->right) {
    buf[y0 + 1][x0 + 1] = '\\';
    print_binary_tree2(n->right, ylen, xlen, buf, y0 + 2, x0 + 2);
  }
}

void print_binary_tree(binary_tree *t) {
  char buf[ylen][xlen] = {{0}};
  for (size_t i = 0; i < ylen; i += 1) {
    for (size_t j = 0; j < xlen; j += 1) {
      buf[i][j] = ' ';
    }
  }
  if (t) {
    node *n = t->root;
    print_binary_tree2(n, ylen, xlen, buf, 0, xlen / 2);
  }
  for (size_t i = 0; i < ylen; i += 1) {
    for (size_t j = 0; j < xlen - 1; j += 1) {
      if (buf[i][j] == '\0') {
        buf[i][j] = ' ';
      }
    }
    buf[i][xlen - 1] = '\0';
    printf("%s\n", buf[i]);
  }
}

int main(int argc, char *argv[argc + 1]) {
  binary_tree *t = binary_tree_new();
  node *n1 = node_new(12);
  node *n2 = node_new(15);
  node *n3 = node_new(4);
  node *n4 = node_new(10);
  node *n5 = node_new(2);
  node *n6 = node_new(18);
  node *n7 = node_new(7);
  node *n8 = node_new(14);
  node *n9 = node_new(21);
  node *n10 = node_new(5);
  n1->left = n7;
  n1->right = n3;
  n3->p = n1;
  n7->p = n1;
  n2->left = n8;
  n8->p = n2;
  n3->left = n10;
  n10->p = n3;
  n4->left = n5;
  n4->right = n9;
  n5->p = n4;
  n9->p = n4;
  n6->left = n1;
  n6->right = n4;
  n1->p = n6;
  n4->p = n6;
  n8->left = n6;
  n8->right = n2;
  n6->p = n8;
  n2->p = n8;
  t->root = n6;
  print_binary_tree(t);
  // FIXME index 2 and 8 are not deleted.
  binary_tree_delete(t);
  return EXIT_SUCCESS;
}
