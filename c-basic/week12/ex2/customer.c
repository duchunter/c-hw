#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bintree.h"

#define INPUT "payment.txt"
#define MAX_LINE 80

int parseLine(FILE *f, char divider, Node **root) {
  char *line = (char *) malloc(MAX_LINE * sizeof(char));
  if (fgets(line, MAX_LINE, f) == NULL) {
    return 0;
  }

  element data;
  data.total = 0;
  int l = 0;
  char *p_start = line;
  char *p_end = NULL;
  while ((p_end = strchr(p_start, divider)) != NULL) {
    *p_end = '\0';
    switch (l) {
      case 0:
        strcpy(data.id, p_start);
        break;
      case 1:
        strcpy(data.name, p_start);
        break;
      case 2:
        data.total += atoi(p_start);
        data.tp = *p_start != '0';
        break;
      case 3:
        data.total += atoi(p_start);
        data.dt = *p_start != '0';
        break;
    }

    l++;
    p_start = p_end + 1;
  }

  data.total += atoi(p_start);
  data.mm = *p_start != '0';
  l++;
  addNode(root, data);

  free(line);
  return l;
}

int main(int argc, char const *argv[]) {
  // Preparation
  FILE *in;
  if ((in = fopen(INPUT, "r")) == NULL) {
    printf("Cannot open %s\n", INPUT);
    return -1;
  }

  Node *root = NULL;
  while (parseLine(in, '-', &root) != 0);
  printf(
    "%-15s%-25s%10s%4s%4s%4s\n\n",
    "ID", "Name", "Total", "TP", "DT", "MM"
  );
  inOrder(root);

  delTree(root);
  fclose(in);
  return 0;
}
