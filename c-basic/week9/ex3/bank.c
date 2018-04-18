#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int tables, lastEnter = 0, waiting = 0, totalWaitTime = 0;
doublelist *arr;
char *currentTime = "Morning";

void wait() {
  printf("\nEnter anything to return to menu: ");
  getchar();
}

void init() {
  printf("Enter number of tables: ");
  tables = mustBeInt();
  arr = (doublelist *) malloc(tables * sizeof(doublelist));
}

int parseTime(char *str) {
  int now = 0;
  char *ch = strchr(str, ':');
  if (ch == NULL) {
    printf("Invalid time string\n");
    return -1;
  }

  strcpy(currentTime, str);
  now += atoi(ch + 1);
  ch = '\0';
  now += atoi(str) * 60;
  return now;
}

void applyTimeChange(int now) {
  int change = now - lastEnter;
  lastEnter = now;
  for (int x = 0; x < tables; x++) {
    if (!isEmpty(arr[x])) {
      for (node *temp = arr[x]->root; temp != NULL; temp = temp->next) {
        temp->data.wait -= change;
        if (temp->data.wait <= 0) {
          if (temp->next != NULL) {
            waiting -= 1;
            totalWaitTime -= temp->data.wait + change;
          }

          dequeue(arr[x]);
        } else {
          totalWaitTime -= change;
        }
      }
    }
  }
}

void arrangeCustomer() {
  int min = 0;
  for (int x = 0; x < tables; x++) {
    if (isEmpty(arr[x])) {
      enqueue(newElement(0), arr[x]);
      return;
    }

    if (tail(arr[x]).wait < tail(arr[min]).wait) {
      min = x;
    }
  }

  int wait = tail(arr[min]).wait;
  enqueue(newElement(wait), arr[min]);
  waiting += 1;
  totalWaitTime += wait;
}

int main(int argc, char const *argv[]) {
  init();
  int choice, now;
  char current[10];
  do {
    system("clear");
    printf("\t\tBank simulator - Current time: %s\n\n", currentTime);
    printf(
      "Waiting: %d customer(s)\tTotal wait time: %d min(s)\n",
      waiting, totalWaitTime
    );
    if (waiting != 0) {
      printf(
        "Average: %.1f mins / customer\n",
        (float) totalWaitTime / waiting
      );
    }

    printf("\n1. New action\n\n0. Exit\n\nEnter your choice: ");
    choice = mustBeInt();
    if (choice == 1) {
      printf("Enter time (hh/mm): ");
      scanf("%[^\n]", current);
      getchar();
    }
  } while(choice != 0);

  for (int x = 0; x < tables; x++) {
    deleteList(arr[x]);
  }

  free(arr);
  return 0;
}
