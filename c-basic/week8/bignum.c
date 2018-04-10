#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// MAIN
int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Invalid syntax, should be ./bignum num1 operation num2\n");
    return -1;
  }

  linkedList num1, num2, result;
  num1.root = num1.now = num1.prev = NULL;
  num2.root = num2.now = num2.prev = NULL;
  result.root = result.now = result.prev = NULL;

  int x, remain = 0, temp, compare;
  int l1 = strlen(argv[1]);
  int l2 = strlen(argv[3]);
  if (l1 == l2) {
    compare = strcmp(argv[1], argv[3]);
    if ((compare == 0) && (strcmp(argv[2], "-") == 0)) {
      printf("Result: 0\n");
      return 0;
    }
  } else {
    compare = (l1 > l2) ? 1 : -1;
  }

  for (x = 0; x < l1; x++) {
    if (isalpha(argv[1][x])) {
      printf("Number 1 contains strange character\n");
      return -1;
    }

    temp = argv[1][x] - '0';
    push(temp, &num1);
  }

  for (x = 0; x < l2; x++) {
    if (isalpha(argv[3][x])) {
      printf("Number 2 contains strange character\n");
      return -1;
    }

    temp = argv[3][x] - '0';
    push(temp, &num2);
  }

  while (!isEmpty(&num1) || !isEmpty(&num2)) {
    if (strcmp(argv[2], "+") == 0) {
      temp = remain;
      if (!isEmpty(&num1)) temp += pop(&num1);
      if (!isEmpty(&num2)) temp += pop(&num2);
      if (temp >= 10) {
        remain = 1;
        temp -= 10;
      } else {
        remain = 0;
      }

      push(temp, &result);
    }

    else if (strcmp(argv[2], "-") == 0) {
      temp = 0 - remain;
      if (compare == 1) {
        if (!isEmpty(&num1)) temp += pop(&num1) + 10;
        if (!isEmpty(&num2)) temp -= pop(&num2);
      } else {
        if (!isEmpty(&num2)) temp += pop(&num2) + 10;
        if (!isEmpty(&num1)) temp -= pop(&num1);
      }

      if (temp >= 10) {
        remain = 0;
        temp -= 10;
      } else {
        remain = 1;
      }

      push(temp, &result);
    }

    else {
      printf("Operation not supported\n");
      return -1;
    }
  }

  printf("Result: ");
  if ((strcmp(argv[2], "-") == 0) && (compare == -1)) {
    printf("-");
  }

  if ((strcmp(argv[2], "+") == 0) && remain != 0) {
    push(1, &result);
  }

  while (!isEmpty(&result)) {
    printf("%d", pop(&result));
  }

  printf("\n");
  delList(&num1);
  delList(&num2);
  delList(&result);
  return 0;
}
