#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adjNode[MAX];
int adjList[MAX][MAX];
int visited[MAX];

void visit(int node) {
  int x, next;
  visited[node] = 1;
  for (x = 0; x < adjNode[node]; x++) {
    next = adjList[node][x];
    if (!visited[next]) {
      visit(next);
    }
  }

  return;
}

int allVisited(int length) {
  for (int x = 1; x < length; x++) {
    if (!visited[x]) return x;
  }

  return -1;
}


int main(int argc, char const *argv[]) {
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

  // Count
  int count = 1;
  visit(1);
  int x = allVisited(nodes);
  while (x != -1) {
    count += 1;
    visit(x);
    x = allVisited(nodes);
  }

  // Result
  printf("%d\n", count);

  return 0;
}
