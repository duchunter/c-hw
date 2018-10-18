#include <stdio.h>
#include <time.h>
typedef struct Node{
    int id;
    struct Node* leftMostChild;
    struct Node* rightSibling;
    struct Node* parent;
}TNode;

TNode* root = NULL;
int sumH;
int sumD;

TNode* makeNode(int id){

}
TNode* findNode(TNode* r, int id){

}
void addChild(TNode* p, int v){
    // add a node having id v at last position of the children list of p
    // (the new node will be the rightMostChild of p)
}
void addChildFromID(int id, int v){
    TNode* p = findNode(root,v);
    if(p != NULL)
        addChild(p,id);
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
}
int height(TNode* r){

}

int depth(TNode* p){

}
void sumHeight(TNode* p){

}
void sumDepth(TNode* p){

}

int computeSumH(){
}
void solve(){
    buildTreeFromSTDIN();
    printf("%d",computeSumH());
}
int main(){
    solve();
    //solveH("Test09/NETWORKH.INP",
    //       "Test09/NETWORKH.OUT");

    //buildRandomTree(1000,"Test07/NETWORKH.INP");
    //return 1;

    //buildTree("Test01/NETWORK.INP");
    //sumH = 0;
    //sumD = 0;
    //sumHeight(root);
    //sumDepth(root);
    //printf("sumH = %d, sumD = %d\n",sumH,sumD);
    //printTree(root);
    //TNode* p = findNode(root,7);
    //printf("%d, %d",height(p), depth(p));
}
