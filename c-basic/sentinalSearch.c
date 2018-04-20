#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublelist.h"

int main(int argc, char *argv[]){
    doublelist list;
    list.root = list.now = list.tail = NULL;
    importDatList("phoneDB.dat", &list);
    element sentinal;
    sentinal.memory = -1;
    printf("Enter model: ");
    scanf("%[^\n]", sentinal.model);
    getchar();
    insertAtTail(newNode(sentinal), &list);
    node *cur = list.root;
    while (strcmp(cur->data.model, sentinal.model) != 0) {
        cur = cur->next;
    }

    if (cur->data.memory == -1) {
        printf("Not found\n");
    } else {
        printNode(cur);
    }

    deleteList(&list);
    return 0;
}
