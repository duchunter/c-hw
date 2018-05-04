#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liststack.c"

int eval(treeNode *root) {
    switch(root->val) {
    case '+':
        return eval(root->left) + eval(root->right);
    case '-':
        return eval(root->left) - eval(root->right);
    case '*':
        return eval(root->left) * eval(root->right);
    case '/':
        return eval(root->left) / eval(root->right);
    }

    return root->val;
}

int main(int argc, char *argv[]) {
    linkedList stack;
    stack.root = stack.prev = stack.now = NULL;
    treeNode *root = NULL;
    char exp[30];
    printf("Enter expression: ");
    scanf("%s", exp);
    getchar();
    for (int x = 0; x < strlen(exp); x++) {
        if ('0' <= exp[x] && exp[x] <= '9') {
            push(newTreeNode(exp[x] - '0'), &stack);
            continue;
        }

        switch(exp[x]) {
        case '+': case '-': case '*': case '/':
            root = newTreeNode(exp[x]);
            root->left = pop(&stack);
            root->right = pop(&stack);
            push(root, &stack);
            break;
        default:
            printf("Invalid expression\n");
            return -1;
        }
    }

    printf("Result: %d\n", eval(pop(&stack)));
    return 0;
}
