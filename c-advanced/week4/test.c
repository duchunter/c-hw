/*
n customers, customer i has coordinate (xi, yi) and require number of
package di. Storage has coordinate (x0, y0)
Build a program with the following function:
- Create a route start from storage, deliver package to customers and return
0 - 1 - 2 - ... - n - 0
- Split route:
  + Input: 1 route, 2 point i, j
  + Output: 2 routes 0 -> i - 1 -> j + 1 -> ... -> n -> 0 and
0 -> i -> ... -> j -> 0
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "doublelist.h"

double getDistance(element a, element b) {
  double x = a.x - b.x;
  double y = a.y - b.y;
  return sqrt(x * x + y * y);
}

int main(int argc, char const *argv[]) {
  element storage;
  storage.id = 0;
  storage.x = 0;
  storage.y = 0;
  storage.load = 0;
  storage.distance = 0;

  doublelist list;
  list.root = list.now = list.tail = NULL;
  FILE *f = fopen("route.txt", "r");
  if (f == NULL) {
    printf("Cannot open data file\n");
    return -1;
  }

  int id, x, y, load, num;
  element temp;
  fscanf(f, "%d", &num);
  fscanf(f, "%d", &id);
  fscanf(f, "%d", &id);
  fscanf(f, "%d", &id);

  insertAtHead(newNode(storage), &list);

  for (int i = 0; i < num; i++) {
    fscanf(f, "%d", &temp.id);
    fscanf(f, "%d", &temp.x);
    fscanf(f, "%d", &temp.y);
    fscanf(f, "%d", &temp.load);
    temp.distance = getDistance(storage, temp);
    insertAfter(newNode(temp), &list);
  }

  insertAtTail(newNode(storage), &list);

  printList(&list);

  fclose(f);
  return 0;
}
