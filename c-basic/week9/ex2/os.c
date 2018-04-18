#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int maxProcess, maxMemory, totalMemory, runningProcess;
element *os, dummy;

void wait () {
  printf("\nEnter anything to return to menu: ");
  getchar();
}

void init() {
  printf("Enter number of parallel process: ");
  maxProcess = mustBeInt();
  printf("Enter memory capacity: ");
  maxMemory = mustBeInt();
  totalMemory = 0;
  runningProcess = 0;
  os = (element *) malloc(maxProcess * sizeof(element));
  for (int x = 0; x < maxProcess; x++) {
    os[x] = dummy;
  }
}

void checkQueue(doublelist *queue) {
  element temp;
  while (!isEmpty(queue)) {
    temp = head(queue);
    if (temp.memory + totalMemory <= maxMemory && runningProcess < maxProcess) {
      dequeue(queue);
      for (int x = 0; x < maxProcess; x++) {
        if (os[x].id == -1) {
          os[x] = temp;
          totalMemory += temp.memory;
          runningProcess += 1;
          break;
        }
      }
    } else break;
  }
}

void createNewProgram(doublelist *queue) {
  element new = newElement();
  if (new.memory > maxMemory) {
    printf("Not enough memory for this program\n");
    return;
  }

  enqueue(new, queue);
  checkQueue(queue);
}

void killProgram(doublelist *queue) {
  printf("Enter id: ");
  int id = mustBeInt();
  for (int x = 0; x < maxProcess; x++) {
    if (os[x].id == id) {
      runningProcess -= 1;
      totalMemory -= os[x].memory;
      os[x] = dummy;
      checkQueue(queue);
      printf("Done\n");
      return;
    }
  }

  printf("ID not found\n");
}

void displayStatus(doublelist *queue){
  printf(
    "Process: %d/%d\tMemory: %d/%d\n",
    runningProcess, maxProcess, totalMemory, maxMemory
  );

  if (runningProcess > 0) {
    printf("\nCurrently running:\n");
    for (int x = 0; x < maxProcess; x++) {
      if (os[x].id != -1) {
        printf("ID: %d\tMemory: %d\n", os[x].id, os[x].memory);
      }
    }
  } else {
    printf("\nThere's no running process\n");
  }

  if (!isEmpty(queue)) {
    printf("\nPending:\n");
    for (node *temp = queue->root; temp != NULL; temp = temp->next) {
      printf("ID: %d\tMemory: %d\n", temp->data.id, temp->data.memory);
    }
  } else {
    printf("\nThere's no pending process\n");
  }
}

int main(int argc, char const *argv[]) {
  dummy.id = -1;
  dummy.memory = 0;
  int choice;
  doublelist queue;
  queue.root = queue.tail = queue.now = NULL;
  init();
  do {
    system("clear");
    printf("1. Create new program\n2. Kill a program\n3. Display status\n");
    printf("\n\n0 .Exit\n\nEnter your choice: ");
    choice = mustBeInt();
    switch (choice) {
      case 1:
        system("clear");
        createNewProgram(&queue);
        wait();
        break;
      case 2:
        system("clear");
        killProgram(&queue);
        wait();
        break;
      case 3:
        system("clear");
        displayStatus(&queue);
        wait();
        break;
    }
  } while(choice != 0);

  deleteList(&queue);
  return 0;
}
