#include <stdio.h>
#include <stdlib.h>

# define MAX 100000
# define MOD 1000000007

int n;
int operand[MAX];

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

long long mulMod(long long a, long long b, long long mod) {
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

int compute(int a, int b, int operator) {
  switch (operator) {
    case 0:
      return subMod(a, b, MOD);
    case 1:
      return addMod(a, b, MOD);
    case 2:
      return mulMod(a, b, MOD);
    default:
      return 0;
  }
}

int main(int argc, char const *argv[]) {
  scanf("%d", &n);

  int x, b;
  for (x = 0; x < n; x++) {
    scanf("%d", &operand[x]);
  }

  int first = operand[0];
  int operator = -1;
  int last = -1;
  int count = 1;
  for (x = 0; x < n - 1; x++) {
    scanf("%d", &b);
    switch (b) {
      // Minus + Add
      case 0: case 1: {
        if (operator != -1) {
          first = compute(first, last, operator);
        }

        operator = b;
        last = operand[count];
        count += 1;
        break;
      }

      // Mul
      case 2: {
        if (operator == -1) {
          first = compute(first, operand[count], 2);
        } else {
          last = compute(last, operand[count], 2);
        }

        count += 1;
        break;
      }

      default: {
        break;
      }
    }
  }

  if (operator != -1) {
    first = compute(first, last, operator);
  }

  printf("Result: %d\n", first);
  return 0;
}
