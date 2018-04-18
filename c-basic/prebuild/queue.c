#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int data[MAX];
    int front;
    int rear;
} queue;

void initialize(queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(queue *q) {
    return q->front == -1 && q->rear == -1;
}

int isFull(queue *q) {
    if (isEmpty(q)) return 0;
    int a = q->front;
    int b = q->rear;
    if (b == MAX - 1) {
        return a == 0;
    } else {
        return b + 1 == a;
    }
}

int enqueue(int data, queue *q) {
    if (isFull(q)) {
        printf("Max cap reached\n");
        return -1;
    }

    if (isEmpty(q)) {
        q->front = q->rear = 0;
        q->data[0] = data;
    } else {
        if (q->rear == MAX - 1) {
            q->rear = 0;
        } else {
            q->rear += 1;
        }
        q->data[q->rear] = data;
    }

    return data;
}

int dequeue(queue *q) {
    int data;
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }

    if (q->front == q->rear) {
        data = q->data[q->rear];
        q->front = q->rear = -1;
        return data;
    }

    data = q->data[q->front];
    if (q->front == MAX - 1) {
        q->front = 0;
    } else {
        q->front += 1;
    }

    return data;
}

int main(int argc, char *argv[]) {
    queue q;
    initialize(&q);
    int x;
    printf("isEmpty return: %d\n", isEmpty(&q));
    printf("isFull return: %d\n\n", isFull(&q));

    for (x = 0; x < 10; x++) {
        printf("Enqueue: %d\n", enqueue(x, &q));
    }

    printf("isEmpty return: %d\n", isEmpty(&q));
    printf("isFull return: %d\n\n", isFull(&q));

    for (x = 0; x < 10; x++) {
        printf("Dequeue: %d\n", dequeue(&q));
    }

    printf("\nisEmpty return: %d\n", isEmpty(&q));
    printf("isFull return: %d\n", isFull(&q));

    return 0;
}
