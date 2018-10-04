#include <stdio.h>

long long P = 1000000007;
long long m[1000][1000];

int addmod(long long a, long long b) {
  a = a % P;
  b = b % P;
  long long tmp = P - b;
  return (a >= tmp) ? a - tmp : a + b;
}

void init() {
  int i, j;
  for (i = 0; i < 1000; i++) {
    for (j = 0; j < 1000; j++) {
      m[i][j] = -1;
    }
  }
}

long long c(int k, int n) {
  if (k == 0 || k == n) {
    m[k][n] = 1;
  } else {
    if (m[k][n] == -1) {
      int a = c(k - 1, n - 1);
      int b = c(k, n - 1);
      m[k][n] = addmod(a, b);
    }
  }

  return m[k][n];
}

int main(int argc, char const *argv[]) {
  int k, n;
  scanf("%d", &k);
  scanf("%d", &n);
  init();
  printf("%lld", c(k, n));

  return 0;
}
