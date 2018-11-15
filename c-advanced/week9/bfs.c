#include <stdio.h>
#include <stdlib.h>

#define MAX 8000

int adjNode[MAX];
int adjList[MAX][MAX];
int visited[MAX];
int level = 0;

typedef struct {
  int val;
  int level;
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
    if (isEmpty(q)) return 0;
    int a = q.front;
    int b = q.rear;
    if (b == MAX - 1) {
        return a == 0;
    } else {
        return b + 1 == a;
    }
}

Node enqueue(int val, int level) {
    Node newNode;
    if (isFull(q)) {
        //printf("Max cap reached\n");
        return newNode;
    }

    newNode.val = val;
    newNode.level = level;

    if (isEmpty(q)) {
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
    if (isEmpty(q)) {
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

void bfs(int des) {
  int x;
  Node node = dequeue();
  if (!node.val) {
    printf("-1\n");
    return;
  }

  if (node.val == des) {
    printf("%d\n", node.level);
    return;
  }

  for (x = 0; x < adjNode[node.val]; x++) {
    int next = adjList[node.val][x];
    if (!visited[next]) {
      enqueue(next, node.level + 1);
      visited[next] = 1;
    }
  }

  bfs(des);

  return;
}

int main(int argc, char const *argv[]) {
  // Create queue
  initialize();

  // Get number of nodes and list
  int nodes, edges, x, a, b;
  scanf("%d %d", &nodes, &edges);

  // Init adjNode
  for (x = 1; x < nodes; x++) {
    adjNode[x] = 0;
    visited[x] = 0;
  }

  // Add value to adj list
  for (x = 0; x < edges; x++) {
    scanf("%d %d", &a, &b);
    adjList[a][adjNode[a]] = b;
    adjList[b][adjNode[b]] = a;
    adjNode[a] += 1;
    adjNode[b] += 1;
  }

  // Add root to queue
  enqueue(1, 0);
  visited[1] = 1;

  // Search
  bfs(7);

  return 0;
}
