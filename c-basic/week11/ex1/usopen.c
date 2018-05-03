#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT "usopen.txt"
#define OUTPUT "treegame.txt"
#define LINE 30
#define PLAYER 16

typedef struct Node {
  char name[LINE];
  struct Node *left;
  struct Node *right;
} Node;

Node *newNode(char *name) {
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

  (*root)->left = newNode(win);
  (*root)->right = newNode(lose);
  createTree(&((*root)->left), win, arr, l, level - 1);
  createTree(&((*root)->right), lose, arr, l, level - 1);
}

void printTree(Node *root, FILE *f, char *last) {
  if (root == NULL) return;
  if (strcmp(root->name, last) != 0) {
    fprintf(f, "\n\n");
  }

  fprintf(f, "%-20s", root->name);
  printTree(root->left, f, root->name);
  printTree(root->right, f, root->name);
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

int main(int argc, char const *argv[]) {
  // Preparation
  FILE *in, *out;
  if ((in = fopen(INPUT, "r")) == NULL) {
    printf("Cannot open %s\n", INPUT);
    return -1;
  }

  if ((out = fopen(OUTPUT, "w+")) == NULL) {
    printf("Cannot open %s\n", OUTPUT);
    return -1;
  }

  char name[PLAYER][LINE];
  int l = 0;
  while (fgets(name[l], LINE, in) != NULL) {
    name[l][strlen(name[l]) - 1] = '\0';
    l++;
  }

  // Start operation
  srand((unsigned)time(NULL));
  int random;
  char temp[LINE];
  Node *new;
  // Pick 1
  random = rand() % l;
  strcpy(temp, name[random]);
  strcpy(name[random], "\0");
  Node *root = newNode(temp);
  createTree(&root, temp, name, l, 4);
  printTree(root, out, root->name);

  // Done
  printf("Done\n");
  delTree(&root);
  fclose(in);
  fclose(out);
  return 0;
}
