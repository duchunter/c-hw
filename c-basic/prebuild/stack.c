#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int data[MAX];
    int top;
} stack;

void initialize(stack *s) {
    s->top = 0;
}

int isEmpty(stack *s) {
    return s->top == 0;
}

int isFull(stack *s) {
    return s->top == MAX;
}

int push(int data, stack *s) {
    if (isFull(s)) {
        printf("Max cap reached\n");
        return -1;
    }

    //int top = s->top;
    s->data[s->top++] = data;
    //s->top += 1;
    return data;
}

int pop(stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }

    //int top = s->top;
    int data = s->data[--s->top];
    //s->top -= 1;
    return data;
}

int top(stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }

    return s->data[s->top - 1];
}

int main(int argc, char *argv[]) {
    stack s;
    initialize(&s);
    int x;
    printf("isEmpty return: %d\n", isEmpty(&s));
    printf("isFull return: %d\n\n", isFull(&s));

    for (x = 0; x < 10; x++) {
        printf("Push: %d\n", push(x, &s));
    }

    printf("\nCap: %d\n", s.top);
    printf("Top: %d\n", top(&s));
    printf("isEmpty return: %d\n", isEmpty(&s));
    printf("isFull return: %d\n\n", isFull(&s));

    for (x = 0; x < 10; x++) {
        printf("Pop: %d\n", pop(&s));
    }

    printf("\nisEmpty return: %d\n", isEmpty(&s));
    printf("isFull return: %d\n", isFull(&s));

    return 0;
}