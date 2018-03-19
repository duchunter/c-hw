#include <stdio.h>
#include <stdlib.h>

#define TARGET "phone.dat"
#define PAGE 25

// Initial data
typedef struct {
  char name[20];
  char tel[11];
  char email[25];
} address;

typedef struct node {
  address addr;
  struct node *next;
} node;

node *root = NULL, *now = NULL, *prev = NULL;

// Supporting functions
void wait() {
  printf("\nEnter anything to return to menu: ");
  getchar();
}

address getAddr() {
  printf("\tNew address:\n");
  address addr;
  printf("Name: ");
  scanf("%[^\n]", addr.name);
  printf("Tel: ");
  getchar();
  scanf("%[^\n]", addr.tel);
  printf("Email: ");
  getchar();
  scanf("%[^\n]", addr.email);
  getchar();
  return addr;
}

// Moving
void movePtr(int i) {
  if (root == NULL) return;
  prev = root;
  now = root;
  for (int x = 0; x != i; x++) {
    if (now->next == NULL) break;
    now = now->next;
    if (prev->next != now) prev = prev->next;
  }
}

// Adding
node *newNode(address addr) {
  node *new = (node *) malloc(sizeof(node));
  new->addr = addr;
  new->next = NULL;
  return new;
}

void addHead(node *new) {
  new->next = root;
  root = new;
  now = root;
  prev = root;
}

void addAfter(node *new) {
  node *temp;
  if (root == NULL) {
    root = new;
    prev = root;
    now = root;

  } else {
    if (now == NULL) {
      now = root;
      prev = root;
    }

    temp = now->next;
    now->next = new;
    new->next = temp;
    prev = now;
    now = new;
  }
}

void addBefore(node *new) {
  if (now == prev) {
    addHead(new);
    now = root;
    prev = root;

  } else {
    prev->next = new;
    new->next = now;
    now = new;
  }
}

void insertAt(int i) {
  if (i < 0) {
    printf("Index must be greater than 0\n");
    return;
  }

  if (i == 0) {
    addHead(newNode(getAddr()));
  } else {
    movePtr(i - 1);
    addAfter(newNode(getAddr()));
  }
}

// Printing
void printNode(node *cur) {
  printf(
    "%-21s%-12s%-26s\n", cur->addr.name, cur->addr.tel, cur->addr.email
  );
}

void printList() {
  int page = 0;
  for (node *cur = root; cur != NULL; cur = cur->next) {
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

// Deleting
void delList() {
  for (node *cur = root; cur != NULL; cur = cur-> next) {
    free(cur);
  }

  root = NULL;
  now = NULL;
}

void delNode() {
  if (now == root) {
    root = root->next;
    free(now);
  } else {
    prev->next = now->next;
    free(now);
  }

  now = root;
  prev = root;
}

void delAt(int i) {
  if (i < 0) {
    printf("Index must be greater than 0\n");
    return;
  }

  movePtr(i);
  delNode();
}


// File
void importList() {
  FILE *f;
  if ((f = fopen(TARGET, "rb")) == NULL) {
    printf("Cannot open %s\n", TARGET);
    return;
  }

  address addr[1];
  while (!feof(f)) {
    fread(addr, sizeof(address), 1, f);
    addAfter(newNode(addr[0]));
  }

  fclose(f);
}

void exportList() {
  FILE *f;
  if ((f = fopen(TARGET, "w+b")) == NULL) {
    printf("Cannot open %s\n", TARGET);
    return;
  }

  node *cur;
  for (cur = root; cur != NULL; cur = cur->next) {
    fwrite(cur, sizeof(address), 1, f);
  }

  fclose(f);
}


// MAIN
int main(int argc, char *argv[]) {
  importList();
  printList();
  int choice, i;
  do {
    system("clear");
    printf("\tChoose your action:\n\n");
    printf("1. Print list\n2. Insert at\n3. Delete at\n");
    printf("\n0. Exit\n\nYour choice: ");
    scanf("%d", &choice);
    getchar();
    switch (choice) {
      case 1:
        system("clear");
        printList();
        wait();
        break;
      case 2:
        system("clear");
        printf("Index: ");
        scanf("%d", &i);
        getchar();
        insertAt(i);
        wait();
        break;
      case 3:
        system("clear");
        printf("Index: ");
        scanf("%d", &i);
        getchar();
        delAt(i);
        wait();
        break;
    }
  } while (choice != 0);

  system("clear");
  exportList();
  delList(root);
  return 0;
}
