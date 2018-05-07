#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char word[10];
  int count;
  struct Node *left;
  struct Node *right;
} Node;

Node *newNode(char *word) {
  Node *new = (Node *) malloc(sizeof(Node));
  new->count = 1;
  strcpy(new->word, word);
  return new;
}

void addNode(Node **root, char *word) {
  if (*root == NULL) {
    *root = newNode(word);
    return;
  }

  int compare = strcmp((*root)->word, word);
  if (compare > 0) {
    addNode(&((*root)->left), word);
  } else if (compare < 0) {
    addNode(&((*root)->right), word);
  } else {
    (*root)->count += 1;
  }
}

void inOrder(Node *root, FILE *f) {
    if (root == NULL) return;
    inOrder(root->left, f);
    fprintf(f, "%s: %d\n", root->word, root->count);
    inOrder(root->right, f);
}

void delTree(Node *root) {
  if (root == NULL) return;
  Node *right = (root)->right;
  Node *left = (root)->left;
  free(root);
  delTree(right);
  delTree(left);
}
