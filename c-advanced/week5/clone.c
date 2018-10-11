#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 2000

typedef struct Node {
  int id;
  struct Node* next;
  struct Node* prev;
} TNode;

typedef struct Route {
  struct Node* start;
  struct Node* end;
  int distance;
} TRoute;

int c[MAX][MAX];
int n;
int opt;

int distance(int id1, int id2) {
  return c[id1][id2];
}

void genData(char* filename, int n) {
    FILE* f = fopen(filename, "w");
    srand(time(NULL));
    fprintf(f,"%d\n",n);
    int i,j;
    for(i = 0; i <= n; i++)
        for(j = 0; j <= n; j++)
            c[i][j] = 0;
    int b[100000];
    for(i = 0; i < MAX; i++) b[i] = 0;
    for(i = 0; i <= n; i++){
        for(j = 0; j <= n; j++){
            int x;
            do{
                x = rand()%100000;
            }while(b[x] == 1);
            b[x] = 1;
            fprintf(f,"%d ",x);
            printf("%d/%d\n",i,j);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

void updateDistance(TRoute* r){
    //TODO
}

TRoute* twoOpt(TRoute* r, TNode* x, TNode* y){
    // remove (x, next[x])
    // remove (y, next[y])
    // add (x, y)
    // add (next[x], next[y])

    // TODO

}

TNode* find(TRoute* r, int id){
    TNode* p = r->start;
    while(p != NULL){
        if(p->id == id) return p;
        p = p->next;
    }
    return NULL;
}

TNode* makeNode(int id){
    struct Node* p = (TNode*)malloc(sizeof(TNode));
    p->id = id;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void printRoute(TRoute* r){
    struct Node* x;
    for(x = r->start; x != r->end; x = x->next){
        printf("%d ",x->id);
    }
    printf("%d\n",r->end->id);
}

void printRouteReverse(TRoute* r){
    TNode* x;
    for(x = r->end; x != r->start; x = x->prev){
        printf("%d ",x->id);
    }
    printf("%d\n",r->start->id);
}

TRoute* addLast(struct Route* r, int id) {
    // create a new node having (id, x, y), insert this node to the end of r
    // TODO
}

void deleteRoute(TRoute* r){
    // free memory
    TNode* p = r->start;
    while(p != NULL){
        TNode* pp = p->next;
        int id = p->id;
        free(p);
        p = pp;
    }
    free(r);
    //printf("free(r)\n");
}

void readData(char*filename){
    FILE* f = fopen(filename,"r");
    fscanf(f,"%d",&n);
    int i,j;
    for(i = 0; i <= n; i++)
        for(j =0; j <= n; j++)
            fscanf(f,"%d",&c[i][j]);
    fclose(f);
}

void input(){
    scanf("%d",&n);
    int i,j;
    for(i = 0; i <= n; i++)
        for(j =0; j <= n; j++)
            scanf("%d",&c[i][j]);

}

TRoute* greedyInit(){
    // create a route by greedy insertion
    readData("route.txt");
    struct Route* r = NULL;
    r = addLast(r, 0);
    printRoute(r);
    int b[MAX];
    int i;
    for(i = 1; i <= n; i++) b[i] = 0;
   // printf("while START...\n");
    while(1){
        int minDis = 10000000;
        int sel_i = -1;
        for(i = 1; i <= n ;i++)if(b[i] == 0){
            int d = distance(r->end->id,i);
            if(d < minDis){
                minDis = d;
                sel_i = i;
            }
        }
        if(sel_i == -1) break;
        else{
            printf("addLast %d, minDis = %d\n",sel_i,minDis);
            r = addLast(r,sel_i);
            b[sel_i] = 1;
            printRoute(r);
        }
    }
    r = addLast(r,0);
    updateDistance(r);
    return r;
}

TRoute* twoOptImprove(TRoute* r){
    //printf("init twoOpt, distance = %d\n",r->distance);
    while(1){
        struct Node* x;
        struct Node* y;
        TNode* sel_x = NULL;
        TNode* sel_y = NULL;
        int minDistance = 1000000;
        struct Route* sel_r = NULL;
        for(x = r->start; x->next != r->end; x = x->next){
            for(y = x->next; y != r->end; y = y->next){
                if(x->next == y) continue;
                TNode* nx = x->next;
                struct Route* tmp = twoOpt(r, x, y);
                if(tmp->distance < minDistance){
                    minDistance = tmp->distance;
                    sel_x = x;
                    sel_y = y;
                }else{
                }
                r = twoOpt(r,x,nx);
            }
        }
        if(minDistance < r->distance){
            r = twoOpt(r,sel_x,sel_y);
            opt = r->distance;
            //printf("move sel_x = %d, sel_y = %d, distance = %d\n",sel_x->id,sel_y->id,r->distance);
        }else{
           // printf("local-optimum -> BREAK\n");
            break;
        }
    }
    return r;
}

void solve(char* fi, char* fo){
    readData(fi);
    TRoute* r = greedyInit();
    opt = r->distance;
    r = twoOptImprove(r);
    FILE* f = fopen(fo,"w");
    fprintf(f,"%d",opt);
    fclose(f);
}

void run(){
    input();
    TRoute* r = greedyInit();
    r = twoOptImprove(r);
    printf("%d",r->distance);
    deleteRoute(r);
}

int main(){
  //run();
  genData('route.txt', 100);
}
