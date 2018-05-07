#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    char tel[11];
    char email[25];
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

void padding(char ch, int n) {
  for (int i = 0; i < n; i++) {
    putchar(ch);
  }
}

void prettyPrint(Node *root, int level) {
  int i;
  if (root == NULL) {
    padding('\t', level);
    puts("-");
  } else {
    prettyPrint(root->right, level + 1);
    padding('\t', level);
    printf("%s\n", root->data.tel);
    prettyPrint(root->left, level + 1);
  }
}

Node *findNode(Node *root, char *email) {
  if (root == NULL) return NULL;
  if (strcmp(root->data.email, email) == 0) return root;
  Node *temp = findNode(root->left, email);
  return temp ? temp : findNode(root->right, email);
}

Node *parent(Node *root, char *email) {
  if (root == NULL) return NULL;
  if (
    (root->left && strcmp(root->left->data.email, email) == 0)
    || (root->right && strcmp(root->right->data.email, email) == 0)
  ) {
    return root;
  }

  Node *temp = parent(root->left, email);
  return temp ? temp : parent(root->right, email);
}

Node *findMin(Node *root) {
  if (root == NULL) return NULL;
  Node *cur;
  for (cur = root; cur->left != NULL; cur = cur->left);
  return cur;
}

Node *findMax(Node *root) {
  if (root == NULL) return NULL;
  Node *cur;
  for (cur = root; cur->right != NULL; cur = cur->right);
  return cur;
}

void addNode(Node **root, element data) {
  if (*root == NULL) {
    *root = newNode(data);
    return;
  }

  if (strcmp((*root)->data.email, data.email) > 0) {
    addNode(&((*root)->left), data);
  } else {
    addNode(&((*root)->right), data);
  }
}

void delTree(Node **root) {
  if (*root == NULL) return;
  Node *right = (*root)->right;
  Node *left = (*root)->left;
  free(*root);
  *root = NULL;
  delTree(&right);
  delTree(&left);
}

void printTree(Node *root) {
  if (root == NULL) return;
  printf("%s\n", root->data.name);
  printTree(root->left);
  printTree(root->right);
}

int nbNode(Node *root) {
    if (root == NULL) return 0;
    return 1 + nbNode(root->left) + nbNode(root->right);
}
