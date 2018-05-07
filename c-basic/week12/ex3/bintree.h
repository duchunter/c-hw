#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINE 30

typedef struct Node {
  char name[LINE];
  struct Node *left;
  struct Node *right;
} Node;

Node *newTreeNode(char *name) {
  Node *new = (Node *) malloc(sizeof(Node));
  strcpy(new->name, name);
  return new;
}

void createTree(Node **root, char *win, char arr[][LINE], int l, int level) {
  if (level == 0) return;
  // Pick 1
  char lose[LINE];
  int random;
  do {
    random = rand() % l;
  } while (strlen(arr[random]) == 0);

  strcpy(lose, arr[random]);
  strcpy(arr[random], "\0");

  (*root)->left = newTreeNode(win);
  (*root)->right = newTreeNode(lose);
  createTree(&((*root)->left), win, arr, l, level - 1);
  createTree(&((*root)->right), lose, arr, l, level - 1);
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

void printTree(Node *root, int space, FILE *f) {
  // Base case
  if (root == NULL) return;

  // Decrease distance between levels
  space -= 1;

  // Process right child first
  printTree(root->right, space, f);

  // Print current node after space
  fprintf(f, "\n");
  for (int i = 1; i < space; i++) fprintf(f, "%20s", " ");
  fprintf(f, "%s\n", root->name);

  // Process left child
  printTree(root->left, space, f);
}
