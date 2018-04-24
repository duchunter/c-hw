#include <stdio.h>
#include <stdlib.h>

// Initial data
typedef struct {
  int val;
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

element getData() {
  element data;
  printf("Enter value: ");
  scanf("%d", &data.val);
  return data;
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

// Printing
void printNode(node *cur) {
    printf("%d\n", cur->data.val);
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

element delNode(linkedList *list) {
  node **root = &list->root;
  node **now = &list->now;
  node **prev = &list->prev;

  element data = list->now->data;
  if (*root == NULL) {
    printf("Nothing to delete\n");
    return data;
  }

  if (*now == *root) {
    *root = (*root)->next;
    free(*now);
  } else {
    (*prev)->next = (*now)->next;
    free(*now);
  }

  *now = *root;
  *prev = *root;
  return data;
}

element delHead(linkedList *list) {
  movePtrByIndex(0, list);
  return delNode(list);
}

int isEmpty(linkedList *list) {
    node **root = &list->root;
    return *root == NULL;
}

int push(int val, linkedList *list) {
    element data;
    data.val = val;
    addHead(newNode(data), list);
    return val;
}

int pop(linkedList *list) {
    return delHead(list).val;
}

int top(linkedList *list) {
    return list->root->data.val;
}

// MAIN
int main(int argc, char *argv[]) {
    linkedList list;
    list.root = list.now = list.prev = NULL;
    int x;
    printf("Empty: %d\n\n", isEmpty(&list));
    for (x = 0; x < 10; x++) {
        printf("Push: %d\n", push(x, &list));
    }

    printf("\nEmpty: %d\n", isEmpty(&list));
    printf("Top: %d\n\n", top(&list));

    for (x = 0; x < 10; x++) {
        printf("Pop: %d\n", pop(&list));
    }

    printf("\nEmpty: %d\n", isEmpty(&list));

    delList(&list);
  return 0;
}
