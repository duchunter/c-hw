#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGET "phone.dat"
#define PAGE 25

// Supporting functions
void wait() {
  printf("\nEnter anything to return to menu: ");
  getchar();
}

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

element getAddr() {
  element data;
  printf("Name: ");
  scanf("%[^\n]", data.name);
  printf("Tel: ");
  getchar();
  scanf("%[^\n]", data.tel);
  printf("Email: ");
  getchar();
  scanf("%[^\n]", data.email);
  getchar();
  return data;
}

// Moving
void movePtrByIndex(int i, linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  if (*root == NULL) return;
  *prev = *root;
  *now = *root;
  for (int x = 0; x != i; x++) {
    if ((*now)->next == NULL) break;
    *now = (*now)->next;
    if ((*prev)->next != *now) *prev = (*prev)->next;
  }
}

void movePtrByData(char *email, linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  if (*root == NULL) return;
  *prev = *root;
  for (*now = *root; *now != NULL; *now = (*now)->next) {
      if (strcmp((*now)->data.email, email) == 0) break;
      *prev = *now;
  }
}

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

void addAfter(node *new, linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;
  node *temp;

  if (*root == NULL) {
    *root = new;
    *prev = *root;
    *now = *root;

  } else {
    if (*now == NULL) {
      *now = *root;
      *prev = *root;
    }

    temp = (*now)->next;
    (*now)->next = new;
    new->next = temp;
    *prev = *now;
    *now = new;
  }
}

void addBefore(node *new, linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  if (*now == *prev) {
    addHead(new, list);
    *now = *root;
    *prev = *root;

  } else {
    (*prev)->next = new;
    new->next = *now;
    *now = new;
  }
}

void insertAt(int i, linkedList *list) {
  if (i < 0) {
    printf("Index must be greater than 0\n");
    return;
  }

  if (i == 0) {
    addHead(newNode(getAddr()), list);
  } else {
    movePtrByIndex(i - 1, list);
    addAfter(newNode(getAddr()), list);
  }
}

// Printing
void printNode(node *cur) {
  printf(
    "%-21s%-12s%-26s\n", cur->data.name, cur->data.tel, cur->data.email
  );
}

void printList(linkedList *list) {
  node **root = &list->root;

  int page = 0;
  for (node *cur = *root; cur != NULL; cur = cur->next) {
    printNode(cur);
    page++;
    if (page >= PAGE) {
      printf("\n(Press ENTER to see next page)\n");
      getchar();
      system("clear");
      page = 0;
    }
  }
}

void printNodeByData(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  char email[25];
  printf("Enter email: ");
  scanf("%[^\n]", email);
  getchar();

  movePtrByData(email, list);
  if (*now == NULL) {
      printf("No data found\n");
      *now = *root;
      *prev = *root;
  } else {
      printNode(*now);
  }
}

// Deleting
void delList(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  for (node *cur = *root; cur != NULL; cur = cur-> next) {
    free(cur);
  }

  *root = NULL;
  *now = NULL;
}

void delNode(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  if (*now == *root) {
    *root = (*root)->next;
    free(*now);
  } else {
    (*prev)->next = (*now)->next;
    free(*now);
  }

  *now = *root;
  *prev = *root;
}

void delHead(linkedList *list) {
  movePtrByIndex(0, list);
  delNode(list);
}

void delAt(int i, linkedList *list) {
  if (i < 0) {
    printf("Index must be greater than 0\n");
    return;
  }

  movePtrByIndex(i, list);
  delNode(list);
}

void delByData(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  char email[25];
  printf("Enter email: ");
  scanf("%[^\n]", email);
  getchar();

  movePtrByData(email, list);
  if (*now == NULL) {
      printf("No data found\n");
      *now = *root;
      *prev = *root;
  } else {
      delNode(list);
  }
}

// Sorting and mixin
void *reverseList(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  node *cur, *before;
  cur = before = NULL;
  while (*root != NULL) {
      cur = *root;
      *root = (*root)->next;
      cur->next = before;
      before = cur;
  }

  *root = before;
  printf("Done\n");
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
    if (n != 0) addAfter(newNode(data[0]), list);
  }

  fclose(f);
}

void exportList(linkedList *list) {
  node **root = &list->root;

  FILE *f;
  if ((f = fopen(TARGET, "w+b")) == NULL) {
    printf("Cannot open %s\n", TARGET);
    return;
  }

  node *cur;
  for (cur = *root; cur != NULL; cur = cur->next) {
    fwrite(cur, sizeof(element), 1, f);
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
  int choice, i;
  do {
    system("clear");
    printf("\tChoose your action:\n\n");
    printf("1. Print list\n2. Insert at\n3. Delete at\n4. Reverse list\n");
    printf("5. Del by data\n\n0. Exit\n\nYour choice: ");
    scanf("%d", &choice);
    getchar();
    switch (choice) {
      case 1:
        system("clear");
        printList(&list);
        wait();
        break;
      case 2:
        system("clear");
        printf("Index: ");
        scanf("%d", &i);
        getchar();
        insertAt(i, &list);
        wait();
        break;
      case 3:
        system("clear");
        printf("Index: ");
        scanf("%d", &i);
        getchar();
        delAt(i, &list);
        wait();
        break;
      case 4:
        system("clear");
        reverseList(&list);
        wait();
        break;
      case 5:
        system("clear");
        delByData(&list);
        wait();
        break;
    }
  } while (choice != 0);

  system("clear");
  //exportList(&list);
  delList(&list);
  return 0;
}
