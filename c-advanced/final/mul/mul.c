// PAIR

#include <stdio.h>
#include <stdlib.h>

# define MOD 1000000007
# define MAX 1000000

int n, m;
int arr[MAX];
int sum = 0;

long long addMod(long long a, long long b, long long mod) {
  a = a % mod;
  b = b % mod;
  int result = a + b;
  if (result > mod) {
    result %= mod;
  }
  return result;
}

void quicksort(int arr[], int left, int right) {
    int i, j;
    int temp, pivot;
    if (left < right) {
        i = left;
        j = right + 1;
        pivot = arr[left];
        do {
            do {
                i++;
            } while (arr[i] < pivot);

            do {
                j--;
            } while (arr[j] > pivot);

            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        } while (i < j);

        temp = arr[left];
        arr[left] = arr[j];
        arr[j] = temp;
        quicksort(arr, left, j - 1);
        quicksort(arr, j + 1, right);
    }

    return;
}

int binSearch(int arr[], int target, int start, int stop) {
    int mid, low = start, high = stop - 1;
    if (arr[high] <= target) {
      return high;
    }

    if (arr[low] >= target) {
      return -1;
    }
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == target || (arr[mid] < target && arr[mid + 1] > target)) {
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

int main() {
  scanf("%d %d", &n, &m);
  int x, index, target, i;
  for (x = 0; x < n; x++) {
    scanf("%d", &arr[x]);
  }

  quicksort(arr, 0, n - 1);

  if (arr[0] > m) {
    printf("0\n");
    return 0;
  }

  index = binSearch(arr, m, 0, n);

  for (x = 0; x < index; x++) {
    target = m - arr[x];
    i = binSearch(arr, target, x, index + 1);
    if (i != -1) {
      sum = addMod(i - x, sum, MOD);
    }
  }

  printf("%d\n", sum);
  return 0;
}
