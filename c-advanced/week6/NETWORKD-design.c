#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node{
    int id;
    struct Node* leftMostChild;
    struct Node* rightSibling;
    struct Node* parent;
} TNode;

TNode* root = NULL;
int sumH;
int sumD;

TNode* makeNode(int id) {
    TNode* p = (TNode*)malloc(sizeof(TNode));
    p->id = id;
    p->leftMostChild = NULL;
    p->rightSibling = NULL;
    p->parent = NULL;
    return p;
}

TNode* findNode(TNode* r, int id) {
    if(r == NULL) return NULL;
    if(r->id == id) return r;
    TNode* p = r->leftMostChild;
    while(p != NULL){
        TNode* q = findNode(p,id);
        if(q != NULL) return q;
        p = p->rightSibling;
    }
    return NULL;
}
void addChild(TNode* p, int v){
    // add a node having id v at last position of the children list of p
    // (the new node will be the rightMostChild of p)
    TNode* cur = p->leftMostChild;
    TNode* temp = makeNode(v);
    temp->parent = p;
    if (cur == NULL) {
      p->leftMostChild = temp;
      return;
    }

    while (cur->rightSibling != NULL) {
      cur = cur->rightSibling;
    }

    cur->rightSibling = temp;
    return;
}

void addChildFromID(int id, int v){
    TNode* p = findNode(root,v);
    if(p != NULL) addChild(p,id);
    return;
}

void write2File(FILE* f, TNode* p){
    if(p == NULL) return;
    if(p->leftMostChild == NULL) return;
    fprintf(f,"%d ",p->id);
    int sz = 0;
    TNode* q = p->leftMostChild;
    while(q != NULL){
        sz++;
        q = q->rightSibling;
    }
    fprintf(f,"%d ",sz);
    q = p->leftMostChild;
    while(q != NULL){
        fprintf(f,"%d ",q->id);
        q = q->rightSibling;
    }
    fprintf(f,"\n");
    q = p->leftMostChild;
    while(q != NULL){
        write2File(f,q);
        q = q->rightSibling;
    }

    return;
}

void printTree(TNode* r){
    if(r == NULL) return;
    printf("%d: ",r->id);
    TNode* p = r->leftMostChild;
    while(p != NULL){
        printf("%d, ",p->id);
        p = p->rightSibling;
    }
    printf("\n");
    p = r->leftMostChild;
    while(p != NULL){
        printTree(p);
        p = p->rightSibling;
    }
    return;
}

void buildRandomTree(int n,char* filename){
    root = makeNode(1);
    srand(time(NULL));
    int i;
    for(i = 2; i <= n; i++){
        int v = rand()%(i-1)+1;
        addChildFromID(i,v);
        printf("addChild(%d,%d) -> OK\n",i,v);
    }
    FILE* f = fopen(filename,"w");
    write2File(f,root);
    fprintf(f,"-1");
    fclose(f);
    return;
}
void buildTree(char* filename){
    FILE* f = fopen(filename,"r");
    while(1){
        int id;
        fscanf(f,"%d",&id);
        if(id == -1) break;
        TNode* p = findNode(root,id);
        if(p == NULL){
            p = makeNode(id);
            //printf("findNode(%d) NULL -> init root\n",id);
            root = p;
        }
        int k;
        fscanf(f,"%d",&k);
        int i;
        for(i = 1; i <= k; i++){
            int v;
            fscanf(f,"%d",&v);
            //printf("START addChild(%d)\n",v);
            addChild(p,v);
        }
        //printTree(root);
        //printf("------------------------\n");
    }
    fclose(f);
    return;
}

void buildTreeFromSTDIN(){
    while(1){
        int id;
        scanf("%d",&id);
        if(id == -1) break;
        TNode* p = findNode(root,id);
        if(p == NULL){
            p = makeNode(id);
            //printf("findNode(%d) NULL -> init root\n",id);
            root = p;
        }
        int k;
        scanf("%d",&k);
        int i;
        for(i = 1; i <= k; i++){
            int v;
            scanf("%d",&v);
            //printf("START addChild(%d)\n",v);
            addChild(p,v);
        }
        //printTree(root);
        //printf("------------------------\n");
    }
    return;
}

int height(TNode* r){
  if (r == NULL) return 0;
  int max = 0;
  int cur = 0;
  TNode* child = r->leftMostChild;
  if (child == NULL) return 1;
  while (child != NULL) {
    cur = 1 + height(child);
    if (cur > max) {
      max = cur;
    }
    child = child->rightSibling;
  }

  return max;
}

int depth(TNode* p){
  if (p == NULL) return 0;
  if (root == NULL) return 0;
  if (root == p) return 1;
  TNode *dad = p->parent;
  int d = 1;
  while (dad != NULL) {
    d += 1;
    dad = dad->parent;
  }

  return d;
}

int sumHeight(TNode* p){
  if (p == NULL) return 0;
  int sum = height(p);
  //printf("%d - %d\n", p->id, sum);
  TNode* child = p->leftMostChild;
  while (child != NULL) {
    sum += sumHeight(child);
    child = child->rightSibling;
  }

  return sum;
}

int sumDepth(TNode* p){
  if (p == NULL) return 0;
  int sum = depth(p);
  //printf("%d - %d\n", p->id, sum);
  TNode* child = p->leftMostChild;
  while (child != NULL) {
    sum += sumDepth(child);
    child = child->rightSibling;
  }

  return sum;
}

void solve() {
  buildTreeFromSTDIN();
  //printf("%d", sumDepth(root));
  printf("%d", sumHeight(root));
  //printTree(root);
  return;
}

int main(){
    solve();
    //solveD("Test09/NETWORKD.INP",
    //       "Test09/NETWORKD.OUT");

    //buildRandomTree(10,"NETWORKD.INP");

    //buildTree("NETWORKD.INP");
    //sumH = sumHeight(root);
    //sumD = sumDepth(root);
    //printf("sumH = %d, sumD = %d\n",sumH,sumD);
    //printTree(root);
    //TNode* p = findNode(root,10);
    //printf("%d, %d",height(p), depth(p));

    return 0;
}
