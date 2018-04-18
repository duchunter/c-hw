#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define SERVINGTIME 15

int tables, lastEnter = 0, waiting = 0, totalWaitTime = 0;
doublelist *arr;
char currentTime[10];

void wait() {
  printf("\nEnter anything to return to menu: ");
  getchar();
}

void init() {
  currentTime[0] = '\0';
  strcpy(currentTime, "Morning");
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
    if (!isEmpty(arr + x)) {
      for (node *temp = (arr + x)->root; temp != NULL; temp = temp->next) {
        temp->data.wait -= change;
        if (temp->data.wait <= 0) {
          if (temp->next != NULL) {
            waiting -= 1;
            totalWaitTime -= temp->data.wait + change;
          }

          dequeue(arr + x);
        } else {
          totalWaitTime -= change;
        }
      }
    }
  }
}

void arrangeCustomer(int num) {
  int min = 0;
  for (int x = 0; x < tables; x++) {
    if (isEmpty(arr + x)) {
      enqueue(newElement(SERVINGTIME), arr + x);
      printf("Customer %d goes to table %d and wait: 0 min\n", num, x + 1);
      return;
    }

    if (tail(arr + x).wait < tail(arr + min).wait) {
      min = x;
    }
  }

  int wait = tail(arr + min).wait;
  enqueue(newElement(wait + SERVINGTIME), arr + min);
  printf(
    "Customer %d goes to table %d and wait: %d mins\n",
    num, min + 1, wait
  );
  waiting += 1;
  totalWaitTime += wait;
}

void printStatus() {
  int occupied = 0;
  for (int x = 0; x < tables; x++) {
    occupied += !isEmpty(arr + x);
  }

  printf("\tBank simulator - Current time: %s\n\n", currentTime);
  printf("Tables:\t\t\t%d/%d\n", occupied, tables);
  printf(
    "Waiting:\t\t%d customers\nTotal wait time:\t%d mins\n",
    waiting, totalWaitTime
  );
  if (waiting != 0) {
    printf(
      "Average:\t\t%.1f mins / customer\n",
      (float) totalWaitTime / waiting
    );
  }
}

int main(int argc, char const *argv[]) {
  init();
  int x, choice, now, customer;
  char current[10];
  do {
    system("clear");
    printStatus();
    printf("\n1. New action\n\n0. Exit\n\nEnter your choice: ");
    choice = mustBeInt();
    if (choice == 1) {
      printf("Enter time (hh/mm): ");
      scanf("%[^\n]", current);
      getchar();
      now = parseTime(current);
      if (now != -1) {
        applyTimeChange(now);
        printf("Customers: ");
        customer = mustBeInt();
        for (x = 0; x < customer; x++) {
          arrangeCustomer(x + 1);
        }

        printf("Done\n");
      }

      wait();
    }
  } while(choice != 0);

  for (x = 0; x < tables; x++) {
    deleteList(arr + x);
  }

  free(arr);
  return 0;
}
