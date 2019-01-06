#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define BIG 99999

// Global var
int n, m;
int table[MAX][MAX];
int max = 0;

void printTable() {
  int x, y;
  for (x = 1; x <= n; x++) {
    for (y = 1; y <= n; y++) {
      printf("%d\t", table[x][y]);
    }
    printf("\n");
  }
}

int main(int argc, char const *argv[]) {
  // Init var
  int x, y, z, a, b;

  // Get number of node and edge
  scanf("%d %d", &n, &m);

  for (x = 1; x <= n; x++) {
    for (y = 1; y <= n; y++) {
      table[x][y] = (x == y) ? 0 : BIG;
    }
  }

  // Process edges
  for (x = 1; x <= m; x++) {
    scanf("%d %d", &a, &b);
    table[a][b] = 1;
    table[b][a] = 1;
  }

  // Fill table
  for (x = 1; x <= n; x++) {
    for (y = 1; y <= n; y++) {
      for (z = 1; z <= n; z++) {
        if (table[y][z] > table[y][x] + table[x][z]) {
          table[y][z] = table[y][x] + table[x][z];
          //table[z][y] = table[y][x] + table[x][z];
        }
      }
    }
  }

  printTable();

  // Final result
  printf("Diameter: %d\n", max);
  return 0;
}
