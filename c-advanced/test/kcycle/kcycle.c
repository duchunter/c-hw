#include <stdio.h>
#include <stdlib.h>

#define MAX 200
#define BIG 9999999

int n, m, k;
int map[MAX][MAX] = { 0 };
int adj[MAX][MAX];
int countAdj[MAX] = { 0 };
int marked[MAX] = { 0 };
int min = BIG;

void dfs(int start, int node, int sum, int count) {
  marked[node] = 1;
  int x, nextNode;

  if (count == k) {
    marked[node] = 0;
    if (map[node][start]) {
      sum += map[node][start];
      if (sum < min) {
        min = sum;
      }
    }
  }

  for (x = 0; x < countAdj[node]; x++) {
    nextNode = adj[node][x];
    if (marked[nextNode] == 0) {
      if (sum + map[node][nextNode] < min) {
        dfs(start, nextNode, sum + map[node][nextNode], count + 1);
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  int x, a, b, c;

  scanf("%d %d %d", &n, &m, &k);

  for (x = 0; x < m; x++) {
    scanf("%d %d %d", &a, &b, &c);
    map[a][b] = c;
    map[b][a] = c;
    adj[a][countAdj[a]] = b;
    adj[b][countAdj[b]] = a;
    countAdj[a] += 1;
    countAdj[b] += 1;
  }

  for (x = 1; x <= n; x++) {
    dfs(x, x, 0, 1);
  }

  printf("Min: %d\n", min);
  return 0;
}
