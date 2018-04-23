#include <stdio.h>

#define MAX 100

int recursiveBinSearch(int arr[], int target, int low, int high) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (arr[mid] == target) return mid;
    if (target > arr[mid])
        return recursiveBinSearch(arr, target, mid + 1, high);
    if (target < arr[mid])
        return recursiveBinSearch(arr, target, low, mid - 1);
}

int binSearch(int arr[], int target, int size) {
    int mid, low = 0, high = size - 1;
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

int main(int argc, char *argv[]){
    int arr[MAX];
    for (int x = 0; x < MAX; x++) {
        arr[x] = x;
    }

    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Search %d return %d\n", num, binSearch(arr, num, MAX));
    printf(
        "Recursive search %d return %d\n",
        num,
        recursiveBinSearch(arr, num, 0, MAX)
    );
}
