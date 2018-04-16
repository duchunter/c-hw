#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./numstack.h"

int getValue(int *a, int *b, linkedList *stack) {
    if (isEmpty(stack)) return -1;
    *a = pop(stack);

    if (isEmpty(stack)) return 0;
    *b = pop(stack);

    return 1;
}

// MAIN
int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("Invalid syntax, should be ./postfix_eval expression\n");
    return -1;
  }

  linkedList stack;
  stack.root = stack.now = stack.prev = NULL;
  int x, y, a, b;
  char ch;
  for (x = 1; x < argc; x++) {
      if (strlen(argv[x]) > 1) {
        for (y = 0; y < strlen(argv[x]); y++) {
          ch = argv[x][y];
          if (!isdigit(ch)) {
              if (ch != '+' && ch != '-') {
                  printf("Invalid expression\n");
                  return -1;
              }
          }
        }

        push(atoi(argv[x]), &stack);
        continue;
      }

      ch = argv[x][0];
      if (isdigit(ch)) {
          push(ch - '0', &stack);
      } else {
          switch (ch) {
          case '+':
              if (getValue(&a, &b, &stack) == 1) {
                  push(a + b, &stack);
              } else {
                printf("Invalid expression\n");
                return -1;
              }
              break;
          case '-':
              y = getValue(&a, &b, &stack);
              if (y == 1) {
                  push(b - a, &stack);
              } else if (y == 0) {
                  push(0 - a, &stack);
              } else {
                printf("Invalid expression\n");
                return -1;
              }
              break;
          case 'x':
              if (getValue(&a, &b, &stack) == 1) {
                  push(a * b, &stack);
              } else {
                printf("Invalid expression\n");
                return -1;
              }
              break;
          case '/':
              if (getValue(&a, &b, &stack) == 1) {
                  push(b / a, &stack);
              } else {
                printf("Invalid expression\n");
                return -1;
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
