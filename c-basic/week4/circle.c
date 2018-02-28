#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

enum { MAX_X = 10, MAX_Y = 10, MAX_R = 10 };

void flush() {
  while (getchar() != '\n');
}

typedef struct {
  double x;
  double y;
} point;

typedef struct {
  point center;
  double radius;
  int intersection;
} circle;

int isIntersect(circle a, circle b) {
  double distant = sqrt(
    pow(a.center.x - b.center.x, 2) + pow(a.center.y - b.center.y, 2)
  );
  return distant <= a.radius + b.radius;
}

void checkIntersect(int *table[], circle *arr, int current) {
  for (int i = 0; i < current; i++) {
    if(isIntersect(arr[i], arr[current])) {
      table[current][i] = 1;
      arr[i].intersection += 1;
      arr[current].intersection += 1;
    }
  }
}

circle autoCreate() {
  circle c;
  c.center.x = (float)rand() / (float)(RAND_MAX) * MAX_X;
  c.center.y = (float)rand() / (float)(RAND_MAX) * MAX_Y;
  c.radius = (float)rand() / (float)(RAND_MAX) * MAX_R;
  c.intersection = 0;

  return c;
}

int main(int argc, char const *argv[]) {
  srand((unsigned) time(NULL));

  int n, i, flag = 0;
  printf("How many circles do you want to add?: ");
  scanf("%d", &n);
  getchar();

  // Allocating memory for an array and a check intersection table
  circle *arr = (circle *) malloc(n * sizeof(circle));
  int **table = (int **) malloc(n * sizeof(int *));
  if (arr = NULL || table == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  for (i = 0; i < n; i++) {
    table[i] = (int *) malloc((i + 1) * sizeof(int));
    if (table[i] == NULL) {
      printf("Memory allocation failed\n");
      return 1;
    }
  }

  // Generate circles and chek intersection with all previous circles
  char ch;
  printf("Do you want to generate circles automatically?(Y/y/N/n): ");
  while (flag == 0) {
    ch = getchar();
    flush();
    switch (ch) {
      case 'Y': case 'y':
        for (i = 0; i < n; i++) {
          arr[i] = autoCreate();
          checkIntersect(table, arr, i);
        }

        flag = 1;
        break;

      case 'N': case 'n':
        for (i = 0; i < n; i++) {
          printf("Circle %d\n", i + 1);
          printf("- Center x: ");
          scanf("%lf", &arr[i].center.x);
          printf("- Center y: ");
          scanf("%lf", &arr[i].center.y);
          printf("- Radius: ");
          scanf("%lf", &arr[i].radius);
          flush();
          arr[i].intersection = 0;
          checkIntersect(table, arr, i);
        }

        flag = 1;
        break;

      default:
        printf("Invalid, try again: ");
    }
  }

  // Display all circles and choose the circle with the most intersection
  int max = 0;
  printf("\nAll circles:\n");
  for (i = 0; i < n; i++) {
    printf(
      "- Circle %d: (%.2f, %.2f), R = %.2f\n",
      i + 1,
      arr[i].center.x,
      arr[i].center.y,
      arr[i].radius,
    );
    if (arr[i].intersection > arr[max].intersection) max = i;
  }

  // If there is no intersection
  if (arr[max].intersection == 0) {
    printf("None of them intersect with other circle\n");
  } else {
    // Display that circle and cirles it intersects with
    printf("\nThe circle with the most intersection is circle %d: ", max + 1);
    printf(
      "\n(%.2f, %.2f), R = %.2f\n",
      arr[max].center.x,
      arr[max].center.y,
      arr[max].radius
    );
    printf("\nIt intersects with:\n");
    for (i = 0; i < n; i++) {
      if (table[i][max] || table[max][i]) printf("- Circle %d\n", i + 1);
    }
  }

  free(arr);
  for (i = 0; i < n; i++) free(table[i]);
  free(table);
  return 0;
}
