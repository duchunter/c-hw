#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

#define INPUT "phone.dat"
#define SEARCH_OUTPUT "found.txt"
#define SORT_OUTPUT "sorted.dat"

void wait () {
  printf("\nEnter anything to return to menu: ");
  getchar();
}

void importData(Node **root) {
  FILE *f;
  if ((f = fopen(INPUT, "rb")) == NULL) {
    printf("Cannot open %s\n", INPUT);
    return;
  }

  element *data = (element *) malloc(sizeof(element));
  int read;
  while (!feof(f)) {
    read = fread(data, sizeof(element), 1, f);
    if (read != 0) addNode(root, *data);
  }

  free(data);
  fclose(f);
}

void exportFound(element data) {
  FILE *f;
  if ((f = fopen(SEARCH_OUTPUT, "w+")) == NULL) {
    printf("Cannot open %s\n", SEARCH_OUTPUT);
    return;
  }

  fprintf(f, "%s - %s - %s\n", data.name, data.tel, data.email);
  fclose(f);
}

void exportSort(Node **root) {
  FILE *f;
  if ((f = fopen(SORT_OUTPUT, "wb+")) == NULL) {
    printf("Cannot open %s\n", SORT_OUTPUT);
    return;
  }

  Node *cur, *dad;
  while (1) {
    cur = findMin(*root);
    if (cur) {
      fwrite(cur, sizeof(element), 1, f);
      if (cur == *root) {
        *root = (*root)->right;
      } else {
        dad = parent(*root, cur->data.email);
        dad->left = cur->right;
        free(cur);
      }
      continue;
    }
    break;
  }

  fclose(f);
}

int main(int argc, char const *argv[]) {
  Node *root = NULL;
  importData(&root);
  int choice;
  char email[25];
  Node *temp;
  do {
    system("clear");
    printf("1. Print tree\n2. Search email\n3. Output sorted list\n");
    printf("\n0. Exit\n\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();
    switch (choice) {
      case 1:
        system("clear");
        printTree(root);
        wait();
        break;
      case 2:
        system("clear");
        printf("Enter email: ");
        scanf("%[^\n]", email);
        getchar();
        temp = findNode(root, email);
        if (temp == NULL) {
          printf("Not found\n");
        } else {
          printf(
            "Found: %s - %s - %s\n",
            temp->data.name, temp->data.tel, temp->data.email
          );
          exportFound(temp->data);
          printf("Done\n");
        }

        wait();
        break;
      case 3:
        system("clear");
        exportSort(&root);
        importData(&root);
        printf("Done\n");
        wait();
        break;
    }
  } while (choice != 0);

  return 0;
}
