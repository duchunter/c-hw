#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGET "phone.dat"
#define PAGE 25

// Initial data
typedef struct {
  char name[20];
  char tel[11];
  char email[25];
} element;

typedef struct node {
  element data;
  struct node *next;
} node;

typedef struct {
  node *root;
  node *now;
  node *prev;
} linkedList;

// Adding
node *newNode(element data) {
  node *new = (node *) malloc(sizeof(node));
  new->data = data;
  new->next = NULL;
  return new;
}

void addHead(node *new, linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  new->next = *root;
  *root = new;
  *now = *root;
  *prev = *root;
}

void printList(linkedList *list) {
  node *root = list->root;
  int page = 0;
  for (node *cur = root; cur != NULL; cur = cur->next) {
    printf(
      "%-21s%-12s%-26s\n", cur->data.name, cur->data.tel, cur->data.email
    );
  }
}

// File
void importList(linkedList *list) {
  FILE *f;
  if ((f = fopen(TARGET, "rb")) == NULL) {
    printf("Cannot open %s\n", TARGET);
    return;
  }

  element data[1];
  while (!feof(f)) {
    int n = fread(data, sizeof(element), 1, f);
    if (n != 0) addHead(newNode(data[0]), list);
  }

  fclose(f);
}

// MAIN
int main(int argc, char *argv[]) {
  linkedList list;
  list.root = NULL;
  list.now = NULL;
  list.prev = NULL;
  importList(&list);
  printList(&list);
  return 0;
}
