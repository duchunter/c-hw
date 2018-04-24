#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "doublelist.h"

#define PAGE 25
#define MAX_LINE 80
#define DIV '|'

int main(int argc, char *argv[]) {
    doublelist list;
    list.root = list.now = list.tail = NULL;
    int choice, i;
    char model[30];
    element tempData;
    do {
        system("clear");
        printf("\tChoose your action:\n\n");
        printf("1. Check empty\n2. Insert after\n3. Insert before\n");
        printf("4. Insert at head\n5. Insert at tail\n6. Insert at index\n");
        printf("7. Delete first\n8. Delete current\n9. Delete list\n");
        printf("10. Print list\n11. Import from text\n");
        printf("12. Self organization search\n13. Sort by search count\n");
        printf("\n0. Exit\n\nYour choice: \n");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
        case 1:
            system("clear");
            printf("Empty: %s\n", isEmpty(&list) ? "true" : "false");
            wait();
            break;
        case 2:
            system("clear");
            insertAfter(newNode(newElement(), 0), &list);
            wait();
            break;
        case 3:
            system("clear");
            insertBefore(newNode(newElement(), 0), &list);
            wait();
            break;
        case 4:
            system("clear");
            insertAtHead(newNode(newElement(), 0), &list);
            wait();
            break;
        case 5:
            system("clear");
            insertAtTail(newNode(newElement(), 0), &list);
            wait();
            break;
        case 6:
            system("clear");
            insertByIndex(&list);
            wait();
            break;
        case 7:
            system("clear");
            deleteFirst(&list);
            wait();
            break;
        case 8:
            system("clear");
            deleteNode(&list);
            wait();
            break;
        case 9:
            system("clear");
            deleteList(&list);
            wait();
            break;
        case 10:
            system("clear");
            printListFromRoot(&list);
            wait();
            break;
        case 11:
            system("clear");
            deleteList(&list);
            importTextList("phone.txt", &list);
            wait();
            break;
        case 12:
            system("clear");
            printf("Enter model: ");
            scanf("%[^\n]", model);
            getchar();
            movePtrByData(model, &list);
            if (list.now == NULL) {
                printf("No model found\n");
                list.now = list.root;
            } else {
                printf("Model found, what's next?\n");
                printf("1. Move to front\n2. Transpose\n3. Search count\n");
                scanf("%d", &choice);
                getchar();
                tempData = list.now->data;
                tempData.count += 1;
                switch (choice) {
                  case 1:
                      deleteNode(&list);
                      insertAtHead(
                        newNode(tempData, tempData.count),
                        &list
                      );
                      printf("Done\n");
                      break;
                  case 2:
                      list.now->data = list.now->prev->data;
                      list.now->prev->data = tempData;
                      printf("Done\n");
                      break;
                  case 3:
                      sortByCount(&list);
                      break;
                }
            }
            wait();
            break;
        case 13:
            system("clear");
            sortByCount(&list);
            wait();
            break;
        }
    } while (choice != 0);

    system("clear");
    deleteList(&list);
    return 0;
}
