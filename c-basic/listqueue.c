#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
} element;

typedef struct node {
    element data;
    struct node *prev;
    struct node *next;
} node;

typedef struct {
    node *root;
    node *now;
} doublelist;

int isEmpty(doublelist *list) {
    return list->root == NULL;
}

void movePtrByIndex(int index, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;

    if (index < 0) {
        printf("Index must be greater than 0");
        return;
    }

    *now = *root;
    for (int x = 0; x < index; x++) {
        *now = (*now)->next;
        if ((*now)->next == NULL) break;
    }
}

element newElement() {
    element data;
    printf("Value: ");
    scanf("%d", &data.val);
    getchar();
    return data;
}

node *newNode(element data) {
    node *new = (node *) malloc(sizeof(node));
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

void insertAtTail(node *new, doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;

    if (*root == NULL) {
        *root = new;
        *now = *root;
    } else {
        node *temp;
        for (temp = *root; temp->next != NULL; temp = temp->next);
        temp->next = new;
        new->prev = temp;
    }
}

void deleteNode(doublelist *list) {
    node **root = &list->root;
    node **now = &list->now;

    if (*now == *root) {
        *root = (*root)->next;
        free(*now);
    } else {
        (*now)->prev->next = (*now)->next;
        if ((*now)->next != NULL) (*now)->next->prev = (*now)->prev;
        free(*now);
    }

    *now = *root;
}

element deleteFirst(doublelist *list) {
    movePtrByIndex(0, list);
    element data = list->now->data;
    deleteNode(list);
    return data;
}

void deleteList(doublelist *list) {
    node **root = &list->root;
    while (*root != NULL) {
        deleteFirst(list);
    }
}

void enqueue(int x, doublelist *q) {
    element data;
    data.val = x;
    insertAtTail(newNode(data), q);
}

int dequeue(doublelist *q) {
    return deleteFirst(q).val;
}

int main(int argc, char *argv[]) {
    doublelist queue;
    queue.now = queue.root = NULL;

    int x;
    for (x = 0; x < 10; x++) {
        printf("Enqueue: %d\n", x);
        enqueue(x, &queue);
    }

    while (!isEmpty(&queue)) {
        printf("Dequeue: %d\n", dequeue(&queue));
    }

    return 0;
}
