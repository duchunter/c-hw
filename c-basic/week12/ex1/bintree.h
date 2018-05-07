#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Return pointer to the start of lastword
Require address of the last element of the string and its length
*/
char *getLastWord(char *e, int l) {
  // Move the pointer up until reach ' ' or start of the string
  while (*e != ' ' && l > 0) {
    l--;
    e -= 1;
  }
  return e;
}

/*
Compare 2 names in Vietnamese
Require 2 address of last element and 2 length
*/
int namecmp(char *e1, char *e2, int l1, int l2) {
  // Cut out 2 lastwords and decrease string length
  char *ne1 = getLastWord(e1, l1);
  l1 -= e1 - ne1;
  char *ne2 = getLastWord(e2, l2);
  l2 -= e2 - ne2;

  // Compare 2 lastwords
  int cmp = strcmp(ne1 + 1, ne2 + 1);
  if (cmp == 0) {
    // Depend on the remaining character in 2 strings
    if (l1 == 0 && l2 > 0) return -1;
    if (l2 == 0 && l1 > 0) return 1;
    if (l1 == 0 && l2 == 0) return 0;

    // If cannot decide, continue comparing the remaining words
    return namecmp(ne1 - 1, ne2 - 1, l1 - 1, l2 - 1);
  }

  // If can compare from the first words then stop
  return cmp;
}


// Tree code
typedef struct Node {
  char name[30];
  struct Node *left;
  struct Node *right;
} Node;

Node *newNode(char *name) {
  Node *new = (Node *) malloc(sizeof(Node));
  strcpy(new->name, name);
  return new;
}

void addNode(Node **root, char *name) {
  if (*root == NULL) {
    *root = newNode(name);
    return;
  }

  int l1 = strlen((*root)->name);
  int l2 = strlen(name);

  if (namecmp((*root)->name + l1, name + l2, l1, l2) > 0) {
    addNode(&((*root)->left), name);
  } else {
    addNode(&((*root)->right), name);
  }
}

Node *findNode(Node *root, char *name) {
  if (root == NULL) return NULL;
  if (strcmp(root->name, name) == 0) return root;
  Node *temp = findNode(root->left, name);
  return temp ? temp : findNode(root->right, name);
}

void delTree(Node *root) {
  if (root == NULL) return;
  Node *right = (root)->right;
  Node *left = (root)->left;
  free(root);
  delTree(right);
  delTree(left);
}

void prettyPrint(Node *root, int space) {
  // Base case
  if (root == NULL) return;

  // Decrease distance between levels
  space -= 1;

  // Process right child first
  prettyPrint(root->right, space);

  // Print current node after space
  printf("\n");
  for (int i = 1; i < space; i++) printf("%20s", " ");
  printf("%s\n", root->name);

  // Process left child
  prettyPrint(root->left, space);
}

void inOrder(Node *root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%s\n", root->name);
    inOrder(root->right);
}
