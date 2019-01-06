#include <stdio.h>
#include <stdlib.h>

#define MAX 4000

int n, m;
int num[MAX] = { 0 };
int friends[MAX][MAX];
int total = 0;

int binSearch(int arr[], int target, int start, int stop) {
    int mid, low = start, high = stop - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == target) {
            return mid;
        }

        if (target < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

int specialBinSearch(int arr[], int target, int size) {
    int mid, low = 0, high = size - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] > target && (mid == 0 || target > arr[mid - 1])) {
            return mid;
        }

        if (target < arr[mid] && target < arr[mid - 1]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

void count(int target) {
  int end = num[target];
  if (end == 0) return;
  int start = specialBinSearch(friends[target], target, end);
  if (start == -1) return;
  int check, a, b;

  for (int x = start; x < end; x++) {
    for (int y = x + 1; y <= end; y++) {
      a = friends[target][x];
      b = friends[target][y];
      check = binSearch(friends[a], b, 0, num[a]);
      if (check != -1) total += 1;
    }
  }
}

int main(int argc, char const *argv[]) {
  int x, a, b;

  scanf("%d %d", &n, &m);

  for (x = 0; x < m; x++) {
    scanf("%d %d", &a, &b);
    friends[a][num[a]] = b;
    friends[b][num[b]] = a;
    num[a] += 1;
    num[b] += 1;
  }

  for (x = 1; x <= n; x++) {
    count(x);
  }

  printf("Total: %d\n", total);
  return 0;
}
