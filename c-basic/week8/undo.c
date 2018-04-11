#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

// Supporting functions
void wait() {
  printf("\nEnter anything to return to menu: ");
  getchar();
}

// Initial data
typedef struct {
  int val;
  char action[MAX];
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

void push(int val, char *action, linkedList *list) {
    element data;
    data.val = val;
    strcpy(data.action, action);
    addHead(newNode(data), list);
}

element pop(linkedList *list) {
    return delHead(list);
}

int top(linkedList *list) {
    return list->root->data.val;
}

// MAIN
int main(int argc, char *argv[]) {
    linkedList numStack, actionStack;
    numStack.root = numStack.now = numStack.prev = NULL;
    actionStack.root = actionStack.now = actionStack.prev = NULL;
    int choice, val;
    do {
      system("clear");
      printf("1. Add a number\n2. View top\n3. Pop a number\n4. Undo\n");
      printf("\n0. Exit\n\nYour choice: ");
      scanf("%d", &choice);
      getchar();
      switch (choice) {
        case 1:
          system("clear");
          printf("Enter a number: ");
          scanf("%d", &val);
          getchar();
          push(val, "", &numStack);
          push(val, "push", &actionStack);
          wait();
          break;
        case 2:
          system("clear");
          if (isEmpty(&numStack)) {
            printf("Stack is empty\n");
          } else {
            printf("Top: %d\n", top(&numStack));
          }
          wait();
          break;
        case 3:
          system("clear");
          val = pop(&numStack).val;
          printf("Pop: %d\n", val);
          push(val, "pop", &actionStack);
          wait();
          break;
        case 4:
          system("clear");
          if (isEmpty(&actionStack)) {
            printf("Nothing to undo\n");
          } else {
            element undo = pop(&actionStack);
            if (strcmp(undo.action, "pop") == 0) {
              push(undo.val, "", &numStack);
              printf("Push %d\n", undo.val);
            } else {
              pop(&numStack);
              printf("Pop %d\n", undo.val);
            }
          }

          wait();
          break;
      }
    } while(choice != 0);

    delList(&numStack);
    delList(&actionStack);
  return 0;
}
