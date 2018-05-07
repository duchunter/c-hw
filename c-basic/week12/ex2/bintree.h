#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char id[15];
  char name[25];
  int total;
  int tp;
  int dt;
  int mm;
} element;

typedef struct Node {
  element data;
  struct Node *left;
  struct Node *right;
} Node;

Node *newNode(element data) {
  Node *new = (Node *) malloc(sizeof(Node));
  new->data = data;
  return new;
}

void addNode(Node **root, element data) {
  if (*root == NULL) {
    *root = newNode(data);
    return;
  }

  int cmp = strcmp((*root)->data.id, data.id);
  if (cmp > 0) {
    addNode(&((*root)->left), data);
  } else if (cmp < 0) {
    addNode(&((*root)->right), data);
  } else {
    (*root)->data.total += data.total;
    (*root)->data.tp += data.tp;
    (*root)->data.dt += data.dt;
    (*root)->data.mm += data.mm;
  }
}

void inOrder(Node *root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf(
      "%-15s%-25s%10d%4d%4d%4d\n",
      root->data.id, root->data.name, root->data.total,
      root->data.tp, root->data.dt, root->data.mm
    );
    inOrder(root->right);
}

void delTree(Node *root) {
  if (root == NULL) return;
  Node *right = (root)->right;
  Node *left = (root)->left;
  free(root);
  delTree(right);
  delTree(left);
}
