#include <stdio.h>
#include <stdlib.h>

#define TARGET "phone.dat"
#define PAGE 25

typedef struct {
  char name[20];
  char tel[11];
  char email[25];
} address;

typedef struct node {
  address addr;
  struct node *next;
} node;

node *root = NULL, *now = NULL;

void wait () {
  printf("\nEnter anything to return to menu: ");

  //Wait for user to enter anything
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

node *newNode(address addr) {
  node *new = (node *) malloc(sizeof(node));
  new->addr = addr;
  new->next = NULL;
  return new;
}

void addHead(node *new) {
  new->next = root;
  root = new;
}

void addAfter(node *new) {
  node *temp;
  if (root == NULL) {
      root = new;
  } else {
    if (now == NULL) now = root;
    temp = now->next;
    now->next = new;
    new->next = temp;
  }

  now = new;
}

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

  printf("List exported\n");
  fclose(f);
}

void delList() {
  for (node *cur = root; cur != NULL; cur = cur-> next) {
    free(cur);
  }

  root = NULL;
  now = NULL;
}

int main(int argc, char *argv[]) {
  importList();
  printList();
  int choice;
  do {
    system("clear");
    printf("\tChoose your action:\n\n");
    printf("1. Print list\n2.Add to head\n3.Add after current position\n");
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
        addHead(newNode(getAddr()));
        wait();
        break;
      case 3:
        system("clear");
        addAfter(newNode(getAddr()));
        wait();
        break;
    }
  } while (choice != 0);

  system("clear");
  exportList();
  delList(root);
  return 0;
}
