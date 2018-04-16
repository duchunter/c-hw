#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./numstack.h"

#define MAX 30

// MAIN
int main(int argc, char *argv[]) {
    char input[MAX];
    printf("Enter expression: ");
    scanf("%[^\n]", input);
    getchar();

    linkedList stack;
    stack.root = stack.now = stack.prev = NULL;

    int x, l = 0, flag = 1;
    char ch, output[MAX + 10];
    for (x = 0; x < strlen(input); x++) {
        ch = input[x];
        if (isdigit(ch)) {
            output[l++] = ch;
            if (!isdigit(input[x + 1])) {
              output[l++] = ' ';
            }

            flag = 0;
            continue;
        }

        if (ch == '+' || ch == '-' || ch == 'x' || ch == '/') {
            if (
              l != 0
              && (
                isEmpty(&stack)
                || (
                  top(&stack) == '(')
                  && flag == 0
                )
              ) {
                push(ch, &stack);
                flag = 1;
                continue;
            }

            if (ch == '+' || ch == '-') {
                if (
                  flag == 1
                  && (
                    input[x + 1] != '('
                    || input[x - 1] == '('
                  )
                ) {
                  output[l++] = ch;
                  continue;
                }

                while (!isEmpty(&stack) && top(&stack) != '(') {
                    output[l++] = pop(&stack);
                    output[l++] = ' ';
                }

                push(ch, &stack);
            } else {
                while (
                    !(isEmpty(&stack))
                    && (
                        top(&stack) == 'x'
                        || top(&stack) == '/'
                        || top(&stack) == '('
                    )
                ) {
                    output[l++] = pop(&stack);
                    output[l++] = ' ';
                }

                push(ch, &stack);
            }

            flag = 1;
            continue;
        }

        if (ch == '(') {
            push(ch, &stack);
            flag = 1;
            continue;
        }

        if (ch == ')') {
            while (top(&stack) != '(') {
                if (isEmpty(&stack)) {
                    printf("Invalid infix\n");
                    return -1;
                }

                output[l++] = pop(&stack);
                output[l++] = ' ';
            }

            pop(&stack);
            flag = 0;
            continue;
        }

        printf("Invalid expression\n");
        return -1;
    }

    while (!isEmpty(&stack)) {
      output[l++] = pop(&stack);
      output[l++] = ' ';
    }

    output[l] = '\0';
    printf("Postfix expression: %s\n", output);
    char pipe[MAX + 20];
    pipe[0] = '\0';
    strcat(pipe, "./postfix_eval ");
    strcat(pipe, output);
    system(pipe);
    delList(&stack);
    return 0;
}
