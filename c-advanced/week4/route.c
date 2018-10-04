#include <stdio.h>

typedef struct Node{
    int id;
    int x;
    int y;
    double distance;
    int load;

    struct Node* next;
    struct Node* prev;
};
/*
    each route is represented by a linked-list, the id of the first and end element is the same and equal to 0

*/
typedef struct RoutePlan{
    struct Node** starts;// array of pointers, each pointer points the the first element of a route
    int size;           // number of routes
};

void printRoute(struct Node* start){

}

void printPlan(struct RoutePlan* rp){

}

struct RoutePlan* split(struct Node* start, int id1, int id2){
    // split the route start
}

struct Node* createSingleRoute(char* filename){
    // load data from file, create single route 0 -> 1 -> ... ->n -> 0
    // return the pointer to the first element of the route
}

int main(){
    printf("start\n");
}
