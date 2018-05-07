#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bintree.h"

#define LINE 80
#define INPUT "student.txt"

void wait () {
  printf("\nEnter anything to return to menu: ");
  getchar();
}

void import(Node **root) {
  FILE *f;
  if ((f = fopen(INPUT, "r")) == NULL) {
    printf("Cannot open %s\n", INPUT);
    return;
  }

  char name[30];
  while (fgets(name, LINE, f) != NULL) {
    name[strlen(name) - 1] = '\0';
    addNode(root, name);
  }

  fclose(f);
}

int main(int argc, char const *argv[]) {
  Node *root = NULL;
  char name[30];
  import(&root);
  int choice;
  do {
    system("clear");
    printf("1. Print sorted list\n2. Find student\n");
    printf("3. Pretty print\n");
    printf("\n\n0. Exit\n\nYour choice: ");
    scanf("%d", &choice);
    getchar();
    switch (choice) {
      case 1:
        system("clear");
        inOrder(root);
        wait();
        break;
      case 2:
        system("clear");
        printf("Enter name: ");
        scanf("%[^\n]", name);
        getchar();
        if (findNode(root, name) == NULL) {
          printf("Not found\n");
        } else {
          printf("Student found\n");
        }

        wait();
        break;
      case 3:
        system("clear");
        prettyPrint(root, 6);
        wait();
        break;
    }
  } while (choice != 0);

  delTree(root);
  return 0;
}
