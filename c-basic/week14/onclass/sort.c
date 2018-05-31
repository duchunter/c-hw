#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Insertion sort
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

// Selection sort
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

// Bubble sort
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

// Heap sort
void adjustArr(int arr[], int root, int l) {
    // element temp;
    int child, temp;
    temp = arr[root - 1];
    child = (root) * 2 - 1;
    while (child <= l - 1) {
        if ((child < l - 1) && (arr[child] < arr[child + 1])) {
            child++;
        }

        if (temp > arr[child]) break;
        else {
            arr[(child + 1) / 2 - 1] = arr[child];
            child = (child + 1) * 2 - 1;
        }
    }

    arr[(child + 1) / 2 - 1] = temp;
}

void heapSort(int arr[], int l) {
    l -= 1;
    // element temp;
    int x, temp;
    for (x = l / 2; x > 0; x--) {
        adjustArr(arr, x, l);
    }

    for (x = l; x > 0; x--) {
        temp = arr[0];
        arr[0] = arr[x];
        arr[x] = temp;
        adjustArr(arr, 1, x);
    }
}

// Quick sort
void quickSort(int arr[], int left, int right) {
    int pivot, i, j;
    int temp;
    // element temp;
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
        quickSort(arr, left, j - 1);
        quickSort(arr, j + 1, right);
    }
}

// Merge sort
void merge(int arr[], int left, int mid, int right) {
    int l, i = left, j = mid + 1;
    int *temp = (int *) malloc((right - left + 1) * sizeof(int));
    if (temp == NULL) {
      printf("Memory allocation failed\n");
      return;
    }

    for (l = 0; l < right - left + 1; l++) {
      if (i > mid) {
        temp[l] = arr[j];
        j++;
      } else if (j > right) {
        temp[l] = arr[i];
        i++;
      } else {
        if (arr[i] < arr[j]) {
          temp[l] = arr[i];
          i++;
        } else {
          temp[l] = arr[j];
          j++;
        }
      }
    }

    for (int x = 0; x < l; x++) {
      arr[x + left] = temp[x];
    }

    free(temp);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
      int mid = (left + right) / 2;
      mergeSort(arr, left, mid);
      mergeSort(arr, mid + 1, right);
      merge(arr, left, mid, right);
    }
}

// Supporting function
void wait () {
  printf("\nEnter anything to return to menu: ");
  while(getchar() != '\n');
  getchar();
}

void printArr(int arr[], int l) {
    for (int x = 0; x < l; x++) {
        printf("%d ", arr[x]);
    }

    printf("\n");
}

void createArr(int arr[], int temp[], int l) {
    for (int x = 0; x < l; x++) {
        arr[x] = rand() % (l + 1);
        temp[x] = arr[x];
    }
}

void copyArr(int arr1[], int arr2[], int l) {
  for (int x = 0; x < l; x++) {
    arr1[x] = arr2[x];
  }
}

// MAIN PROGRAM
int main(int argc, char *argv[]) {
    srand((unsigned)time(NULL));
    clock_t start;
    clock_t stop;
    int choice, l = 0;
    int *source = (int *) malloc(sizeof(int));
    int *temp = (int *) malloc(sizeof(int));
    do {
      system("clear");
      printf("Current array length: %d\n\n", l);
      printf("1. Create array\n");
      printf("2. Insertion sort\n");
      printf("3. Selection sort\n");
      printf("4. Bubble sort\n");
      printf("5. Heap sort\n");
      printf("6. Quick sort\n");
      printf("7. Merge sort\n");
      printf("\n0. Exit\n\nYour choice: ");
      scanf("%d", &choice);
      switch (choice) {
        // Create array
        case 1:
          system("clear");
          printf("Enter number of element: ");
          scanf("%d", &l);
          source = (int *) realloc(source, l * sizeof(int));
          temp = (int *) realloc(temp, l * sizeof(int));
          if (!source || !temp) {
            printf("Memory alloction failed\n");
            return -1;
          }

          createArr(source, temp, l);
          printf("Done\n");
          wait();
          break;

        // Insertion sort
        case 2:
          system("clear");
          printf("Insertion sort, processing...\n");
          start = clock();
          insertionSort(temp, l);
          stop = clock();
          printf(
            "Done! Execution time: %.6f seconds\n",
            (double) (stop - start) / CLOCKS_PER_SEC
          );
          copyArr(temp, source, l);
          wait();
          break;

        // Selection sort
        case 3:
          system("clear");
          printf("Selection sort, processing...\n");
          start = clock();
          selectionSort(temp, l);
          stop = clock();
          printf(
            "Done! Execution time: %.6f seconds\n",
            (double) (stop - start) / CLOCKS_PER_SEC
          );
          copyArr(temp, source, l);
          wait();
          break;

        // Bubble sort
        case 4:
          system("clear");
          printf("Bubble sort, processing...\n");
          start = clock();
          bubbleSort(temp, l);
          stop = clock();
          printf(
            "Done! Execution time: %.6f seconds\n",
            (double) (stop - start) / CLOCKS_PER_SEC
          );
          copyArr(temp, source, l);
          wait();
          break;

        // Heap sort
        case 5:
          system("clear");
          printf("Heap sort, processing...\n");
          start = clock();
          heapSort(temp, l);
          stop = clock();
          printf(
            "Done! Execution time: %.6f seconds\n",
            (double) (stop - start) / CLOCKS_PER_SEC
          );
          copyArr(temp, source, l);
          wait();
          break;

        // Quick sort
        case 6:
            system("clear");
            printf("Quick sort, processing...\n");
            start = clock();
            quickSort(temp, 0, l);
            stop = clock();
            //printArr(temp, l);
            printf(
                   "Done! Execution time: %.6f seconds\n",
                   (double) (stop - start) / CLOCKS_PER_SEC
                   );
            copyArr(temp, source, l);
            wait();
            break;

        // Merge sort
        case 7:
            system("clear");
            printf("Merge sort, processing...\n");
            start = clock();
            mergeSort(temp, 0, l - 1);
            stop = clock();
            printArr(temp, l);
            printf(
                   "Done! Execution time: %.6f seconds\n",
                   (double) (stop - start) / CLOCKS_PER_SEC
                   );
            copyArr(temp, source, l);
            wait();
            break;
      }
    } while (choice != 0);

    // End
    free(source);
    free(temp);
    return 0;
}
