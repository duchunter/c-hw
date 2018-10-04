#include <stdio.h>
#include <stdlib.h>

int *arr = NULL;

int sol(int n, int result) {
  if (result == 0 && n == 0) return 1;
  if (result < 0) return 0;
  if (n == 0) return 0;
  int solutions = 0;
  for (int i = 1; i <= result; i++) {
    solutions += sol(n - 1, result - arr[n - 1] * i);
  }

  return solutions;
}

int main(int argc, char const *argv[]) {
  int n, result;
  scanf("%d", &n);
  scanf("%d", &result);

  arr = (int *) malloc(n * sizeof(int));
  for (int x = 0; x < n; x++) {
    scanf("%d", arr + x);
  }

  printf("%d", sol(n, result));

  free(arr);
  return 0;
}
