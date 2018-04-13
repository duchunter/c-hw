#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

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
    if (argc != 2) {
        printf("Invalid syntax, should be ./infix_to_postfix expression\n");
        return -1;
    }

    linkedList stack;
    stack.root = stack.now = stack.prev = NULL;

    int x, l = 0;
    char ch, output[MAX];
    for (x = 0; x < strlen(argv[1]); x++) {
        ch = argv[1][x];
        if ('0' <= ch && ch <= '9') {
            output[l] = ch;
            l += 1;
        }

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (isEmpty(&stack) || top(&stack) == '(') {
                push(ch, &stack);
            } else {
                if (ch == '+' || ch == '-') {
                    while (!isEmpty(&stack) && top(&stack) != '(') {
                        output[l] = pop(&stack);
                        l += 1;
                    }

                    push(ch, &stack);
                } else {
                    while (
                        !(isEmpty(&stack))
                        && (
                            top(&stack) == '*'
                            || top(&stack) == '/'
                            || top(&stack) == '('
                        )
                    ) {
                        output[l] = pop(&stack);
                        l += 1;
                    }

                    push(ch, &stack);
                }
            }
        }

        if (ch == '(') {
            push(ch, &stack);
        }

        if (ch == ')') {
            while (top(&stack) != '(') {
                if (isEmpty(&stack)) {
                    printf("Invalid infix\n");
                    return -1;
                }

                output[l] = pop(&stack);
                l += 1;
            }

            pop(&stack);
        }
    }

    while (!isEmpty(&stack)) {
        output[l] = pop(&stack);
        l++;
    }

    output[l] = '\0';
    printf("Postfix expression: %s\n", output);
    char pipe[MAX + 10];
    strcat(pipe, "./postfix_eval ");
    strcat(pipe, output);
    system(pipe);

    delList(&stack);
    return 0;
}
