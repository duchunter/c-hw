#include <stdio.h>
#include <stdlib.h>

void quicksort(double arr[], int left, int right) {
    int i, j;
    double temp, pivot;
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

int main() {
    int n, x;
    scanf("%d", &n);
    double *arr = (double *) malloc(n * sizeof(double));

    for (x = 0; x < n; x++) {
        scanf("%lf", &arr[x]);
    }

    quicksort(arr, 0, n - 1);

    for (x = 0; x < n; x++) {
        printf("%.2lf  ", arr[x]);
    }

    free(arr);
    return 0;
}
