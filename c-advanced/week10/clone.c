#include <stdio.h>
#include <stdlib.h>

#define P 999999999
#define MAX 10001

int z[MAX];
int A[MAX][MAX];
int w[MAX][MAX];
int NonFixed[MAX];
int Fixed[MAX];
int d[MAX];
int pred[MAX];

int n, e;
int s, t;

void input() {
    scanf("%d %d\n", &n, &e);
    int i;
    int v, u, d;
    for(i = 1; i <= e; i++) {
        scanf("%d %d %d\n", &v, &u, &d);
        A[v][z[v]++] = u;
        w[v][u] = d;
    }

    scanf("%d %d\n", &s, &t);
}

void initw() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (w[i][j] == 0) {
              w[i][j] = P;
            }
        }
    }
}

int checkNonFixed() {
    int count = 0;
    for (int i = 1; i <= n; i++) {
      if (NonFixed[i] == 1) {
        return 1;
      }
    }

    return 0;
  }

int mind() {
    int v;
    int min = P;
    for (int i = 1; i <= n; i++) {
        if (NonFixed[i] == 0) {
            if (d[i] < min) {
                min = d[i];
                v = i;
            }
        }
    }
    return v;
}

void dijkstra(int s) {
    initw();
    int x;
    for (x = 1; x <= n; x++) {
        d[x] = w[s][x];
        pred[x] = s;
    }

    NonFixed[s] = 1;
    Fixed[s] = 1;
    while (checkNonFixed() != 0){
        int v = mind();
        NonFixed[v] = 1;
        Fixed[v] = 1;
        for (x = 1; x <= n; x++) {
            if (NonFixed[x] == 0) {
                if (d[x] > d[v] + w[v][x]){
                    d[x] = d[v] + w[v][x];
                    pred[x] = v;
                }
            }
        }
    }
}

int main(){
    input();
    dijkstra(s);
    printf("%d\n", d[t]);

    return 0;
}
