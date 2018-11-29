#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
  int val;
  int key;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct {
    Node data[MAX];
    int front;
    int rear;
} queue;

queue q;

void initialize() {
    q.front = -1;
    q.rear = -1;
}

int isEmpty() {
    return q.front == -1 && q.rear == -1;
}

int isFull() {
    if (isEmpty()) return 0;
    int a = q.front;
    int b = q.rear;
    if (b == MAX - 1) {
        return a == 0;
    } else {
        return b + 1 == a;
    }
}

Node enqueue(int val, int key) {
    Node newNode;
    if (isFull()) {
        //printf("Max cap reached\n");
        return newNode;
    }

    newNode.val = val;
    newNode.key = key;

    if (isEmpty()) {
        q.front = q.rear = 0;
        q.data[0] = newNode;
    } else {
        if (q.rear == MAX - 1) {
            q.rear = 0;
        } else {
            q.rear += 1;
        }
        q.data[q.rear] = newNode;
    }

    return newNode;
}

Node dequeue() {
    Node data;
    if (isEmpty()) {
        //printf("Queue is empty\n");
        return data;
    }

    if (q.front == q.rear) {
        data = q.data[q.rear];
        q.front = q.rear = -1;
        return data;
    }

    data = q.data[q.front];
    if (q.front == MAX - 1) {
        q.front = 0;
    } else {
        q.front += 1;
    }

    return data;
}

Node *root = NULL;
int size = 0;

Node *newNode(int val) {
  Node *node = (Node *) malloc(sizeof(Node));
  node->val = val;
  return node;
}

void insert(Node *node, int val) {
  if (node == NULL) {
    node = newNode(val);
  }

  else if (node->left == NULL) {
    node->left = newNode(val);
  }

  else if (node->right == NULL) {
    node->right = newNode(val);
  }
}
