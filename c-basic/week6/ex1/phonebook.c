#include <stdio.h>
#include <stdlib.h>

#define OUTPUT "phone.dat"

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

address getAddr() {
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

node *newNode() {
    node *new = (node *) malloc(sizeof(node));
    new->addr = getAddr();
    new->next = NULL;
    return new;
}

void addHead() {
    printf("- Add to head:\n");
    node *new = newNode();
    new->next = root;
    root = new;
}

void addAfter(node *new) {
    node *temp;
    if (root == NULL) {
        root = new;
        prev = root;
        now = root;
    } else {
        temp = now->next;
        now->next = new;
        new->next = temp;
        prev = now;
        now = new;
    }
}

void addBefore() {
    if (now == prev) {
        addHead();
        now = root;
        prev = root;
    } else {
        node *new = newNode();
        prev->next = new;
        new->next = now;
        now = new;
    }
}

void printNode(node *cur) {
    printf("%s-%s-%s\n", cur->addr.name, cur->addr.tel, cur->addr.email);
}

void printList(node *cur) {
    if (cur == NULL) return;
    printNode(cur);
    printList(cur->next);
}

void delList(node *cur) {
    if (cur == NULL) return;
    delList(cur->next);
    free(cur);
}

void exportList() {
  FILE *f;
  if ((f = fopen(OUTPUT, "w+b")) == NULL) {
    printf("Cannot open %s\n", OUTPUT);
    return;
  }

  node *cur;
  for (cur = root; cur != NULL; cur = cur->next) {
    fwrite(cur, sizeof(address), 1, f);
  }

  fclose(f);
}

int main(int argc, char *argv[]) {
    int n, x;
    printf("How many phone address do you want to add?: ");
    scanf("%d", &n);
    getchar();

    for (x = 0; x < n; x++) {
        printf("- Address %d:\n", x + 1);
        addAfter(newNode());
    }
    /*
    addHead();
    addAfter(newNode());
    addBefore();
    */
    printList(root);
    exportList();

    delList(root);
    return 0;
}
