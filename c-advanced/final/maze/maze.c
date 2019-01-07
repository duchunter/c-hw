#include <stdio.h>
#include <stdlib.h>

#define MAX 501

int visited[MAX][MAX];
int level = 0;
int n, r, c;

typedef struct {
  int x;
  int y;
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
    if (isEmpty()) return 0;
    int a = q.front;
    int b = q.rear;
    if (b == MAX - 1) {
        return a == 0;
    } else {
        return b + 1 == a;
    }
}

Node enqueue(int x, int y, int level) {
    Node newNode;
    if (isFull()) {
        //printf("Max cap reached\n");
        return newNode;
    }

    newNode.x = x;
    newNode.y = y;
    newNode.level = level;

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

void bfs() {
  int x, a, b;
  Node node = dequeue();
  if (!node.x || !node.y) {
    printf("-1\n");
    return;
  }

  if (node.x == 1 || node.x == n || node.y == 1 || node.y == n) {
    printf("%d\n", node.level + 1);
    return;
  }

  for (x = 0; x < 8; x++) {
    switch (x) {
      case 0: {
        a = node.x - 1;
        b = node.y;
        break;
      }

      case 1: {
        b = node.y + 1;
        a = node.x - 1;
        break;
      }

      case 2: {
        b = node.y + 1;
        a = node.x;
        break;
      }

      case 3: {
        b = node.y + 1;
        a = node.x + 1;
        break;
      }

      case 4: {
        b = node.y;
        a = node.x + 1;
        break;
      }

      case 5: {
        b = node.y - 1;
        a = node.x + 1;
        break;
      }

      case 6: {
        b = node.y - 1;
        a = node.x;
        break;
      }

      case 7: {
        b = node.y - 1;
        a = node.x - 1;
        break;
      }
    }

    if (1 <= a && a <= 8 && 1 <= b && b <= 8 && !visited[a][b]) {
      enqueue(a, b, node.level + 1);
      visited[a][b] = 1;
    }
  }

  bfs();

  return;
}

int main(int argc, char const *argv[]) {
  initialize();
  int x, y;
  scanf("%d %d %d", &n, &r, &c);

  for (x = 1; x <= n; x++) {
    for (y = 1; y <= n; y++) {
      scanf("%d", &visited[x][y]);
    }
  }

  visited[r][c] = 1;
  enqueue(r, c, 0);

  bfs();

  return 0;
}
