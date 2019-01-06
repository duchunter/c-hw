#include <stdio.h>
#include <stdlib.h>

#define MAX 30
#define MOD 1000000007

int n, b;
int val[MAX];
int count = 0;

long long addMod(long long a, long long b, long long mod) {
  a = a % mod;
  b = b % mod;
  int result = a + b;
  if (result > mod) {
    result %= mod;
  }
  return result;
}

long long subMod(long long a, long long b, long long mod) {
  a = a % mod;
  b = b % mod;
  int result = a - b;
  if (result > mod) {
    result %= mod;
  }
  return result;
}

long long mulmod(long long a, long long b, long long mod) {
  long long res = 0;
  a = a % mod;
  while (b > 0) {
    if (b % 2 == 1) {
      res = (res + a) % mod;
    }
    
    a = (a * 2) % mod;
    b /= 2;
  }
  return res % mod;
}

void eval(int sum, int index) {
  if (index == n) {
    if (sum == 0) count += 1;
    return;
  }

  eval(sum + val[index], index + 1);
  eval(sum - val[index], index + 1);
}

int main(int argc, char const *argv[]) {
  scanf("%d %d", &n, &b);

  int x;
  for (x = 0; x < n; x++) {
    scanf("%d", &val[x]);
  }

  b -= val[0];
  eval(b, 1);

  printf("Count: %d\n", count % MOD);
  return 0;
}
