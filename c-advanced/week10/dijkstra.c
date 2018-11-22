#include <stdio.h>
#include <stdlib.h>

#define MAX 10001
#define MAX_WEIGHT 10000001

int map[MAX][MAX];
int prev[MAX];
int nonFixed[MAX];
int fixed[MAX];
int final[MAX];

int main(int argc, char const *argv[]) {
  // Get number of nodes and paths
  int nodes, paths, x, y;
  scanf("%d %d", &nodes, &paths);

  for (x = 0; x <= nodes; x++) {
    for (y = 0; y <= nodes; y++) {
      map[x][y] = 101;
    }
  }

  // Put paths to map
  int a, b, val;
  for (x = 0; x < paths; x++) {
    scanf("%d %d %d", &a, &b, &val);
    map[a][b] = val;
  }

  // Get start and stop
  int start, stop;
  scanf("%d %d", &start, &stop);
  if (start == stop) {
    printf("0\n");
    return 0;
  }

  // Set fixed and non fixed list and final list
  for (x = 1; x <= nodes; x++) {
    nonFixed[x] = 1;
    final[x] = MAX_WEIGHT;
    prev[x] = start;
  }

  // Start
  nonFixed[start] = 0;
  fixed[start] = 1;
  final[start] = 0;

  // Loop until no nodes left
  int minVal, minNode;
  while (!fixed[stop]) {
    // Find min
    minVal = MAX_WEIGHT;
    minNode = 0;
    for (x = 1; x <= nodes; x++) {
      if (nonFixed[x]) {
        if (map[prev[x]][x] && map[prev[x]][x] < minVal) {
          minVal = map[prev[x]][x];
          minNode = x;
        }
      }
    }

    nonFixed[minNode] = 0;
    fixed[minNode] = 1;
    final[minNode] = final[prev[minNode]] + minVal;

    // Scan other
    for (x = 1; x <= nodes; x++) {
      if (nonFixed[x]) {
        if (map[minNode][x]) {
          if (final[x] > final[minNode] + map[minNode][x]) {
            final[x] = final[minNode] + map[minNode][x];
            prev[x] = minNode;
          }
        }
      }
    }
  }

  if (final[stop] == MAX_WEIGHT) {
    printf("-1");
  } else {
    printf("%d", final[stop]);
  }

  return 0;
}
