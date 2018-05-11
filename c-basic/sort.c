#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

void insertionSort(int arr[], int l) {
    int temp, x, y;
    for (x = 1; x < l; x++) {
        temp = arr[x];
        for (y = x - 1; y >= 0; y--) {
            if (temp >= arr[y]) break;
            arr[y + 1] = arr[y];
        }

        arr[y + 1] = temp;
    }
}

void selectionSort(int arr[], int l) {
    int temp, x, y, min;
    for (x = 0; x < l; x++) {
        min = x;
        for (y = x + 1; y < l; y++) {
            if (arr[y] < arr[min]) {
                min = y;
            }
        }

        temp = arr[x];
        arr[x] = arr[min];
        arr[min] = temp;
    }
}

void bubbleSort(int arr[], int l) {
    int flag, temp, x, y;
    for (x = 0; x < l; x++) {
        flag = 1;
        for (y = 0; y < l - x - 1; y++) {
            if (arr[y] > arr[y + 1]) {
                temp = arr[y];
                arr[y] = arr[y + 1];
                arr[y + 1] = temp;
                flag = 0;
            }
        }

        if (flag == 1) break;
    }
}

void adjustArr(int arr[], int root, int l) {
    int child, temp;
    temp = arr[root];
    child = (root) * 2;
    while (child <= l) {
        if ((child < l) && (arr[child] < arr[child + 1])) {
            child++;
        }

        if (temp > arr[child]) break;
        else {
            arr[child / 2] = arr[child];
            child *= 2;
        }
    }

    arr[child / 2] = temp;
}

void heapSort(int arr[], int l) {
    int x, temp;
    for (x = l / 2; x > 0; x--) {
        adjustArr(arr, x, l);
    }

    for (x = l - 1; x > 0; x--) {
        temp = arr[1];
        arr[1] = arr[x + 1];
        arr[x + 1] = temp;
        adjustArr(arr, 1, x);
    }
}


void printArr(int arr[], int l) {
    for (int x = 0; x < l; x++) {
        printf("%d ", arr[x]);
    }
}

void createArr(int arr[], int l) {
    for (int x = 0; x < l; x++) {
        arr[x] = rand() % (MAX + 1);
    }
}

int main(int argc, char *argv[]) {
    srand((unsigned)time(NULL));
    int arr[MAX + 1];
    createArr(arr, MAX);
    printArr(arr, MAX);
    printf("\n");
    clock_t start = clock();
    //insertionSort(arr, MAX);
    //selectionSort(arr, MAX);
    //bubbleSort(arr, MAX);
    heapSort(arr, MAX - 1);
    clock_t stop = clock();
    printArr(arr, MAX);
    printf("\n");
    printf(
           "Execution time: %.6f seconds\n",
           (double) (stop - start) / CLOCKS_PER_SEC
    );
}
