#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int getValue(int *a, int *b, linkedList *stack) {
    if (isEmpty(stack)) {
        printf("Invalid expression\n");
        return 0;
    } else {
        *a = pop(stack);
    }

    if (isEmpty(stack)) {
        printf("Invalid expression\n");
        return 0;
    } else {
        *b = pop(stack);
    }

    return 1;
}

// MAIN
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Invalid syntax, should be ./postfix_eval expression\n");
    return -1;
  }

  linkedList stack;
  stack.root = stack.now = stack.prev = NULL;
  int x, a, b;
  char ch;
  for (x = 0; x < strlen(argv[1]); x++) {
      ch = argv[1][x];
      if ('0' <= ch && ch <= '9') {
          push(ch - '0', &stack);
      } else {
          switch (ch) {
          case '+':
              if (getValue(&a, &b, &stack)) {
                  push(a + b, &stack);
              }
              break;
          case '-':
              if (getValue(&a, &b, &stack)) {
                  push(a - b, &stack);
              }
              break;
          case '*':
              if (getValue(&a, &b, &stack)) {
                  push(a * b, &stack);
              }
              break;
          case '/':
              if (getValue(&a, &b, &stack)) {
                  push(a / b, &stack);
              }
              break;
          default:
              printf("Invalid expression\n");
              return -1;
          }
      }
  }

  printf("Result: %d\n", pop(&stack));

  delList(&stack);
  return 0;
}
