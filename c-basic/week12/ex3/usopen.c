#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bintree.h"
#include "listqueue.h"

#define INPUT "usopen.txt"
#define OUTPUT "treegame.txt"
#define BFSOUT "bfs.txt"
#define LINE 30
#define PLAYER 16

void bfs(Node *root, doublelist *q, FILE *f) {
  enqueue(q, root);
  element data;
  while (!isEmpty(q)) {
    data = dequeue(q);
    fprintf(f, "%s\n", data.treeNode->name);
    if (data.treeNode->left) enqueue(q, data.treeNode->left);
    if (data.treeNode->right) enqueue(q, data.treeNode->right);
  }
}

int main(int argc, char const *argv[]) {
  // Preparation
  FILE *in, *out, *bfsfile;
  if ((in = fopen(INPUT, "r")) == NULL) {
    printf("Cannot open %s\n", INPUT);
    return -1;
  }

  if ((out = fopen(OUTPUT, "w+")) == NULL) {
    printf("Cannot open %s\n", OUTPUT);
    return -1;
  }

  if ((bfsfile = fopen(BFSOUT, "w+")) == NULL) {
    printf("Cannot open %s\n", BFSOUT);
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
  doublelist queue;
  queue.root = queue.now = queue.tail = NULL;

  // Pick 1
  random = rand() % l;
  strcpy(temp, name[random]);
  strcpy(name[random], "\0");
  Node *root = newTreeNode(temp);
  createTree(&root, temp, name, l, 4);
  printTree(root, 6, out);
  bfs(root, &queue, bfsfile);

  // Done
  printf("Done\n");
  delTree(&root);
  fclose(in);
  fclose(out);
  return 0;
}
