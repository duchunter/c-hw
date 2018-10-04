#include <stdio.h>
#define MAX 20
#define oo 1000000

int C[MAX][MAX], x[MAX], bestSolution[MAX], VISITED[MAX];   //VISITED[i] = 1 if VISITED,
                                                            //VISITED[i] = 0 otherwise
int n, m, sum, best;
char si[] = "TSP.INP";

void input(){
    FILE *fi;
    int i, j, k;
    fi = fopen(si, "r");
    if (fi == NULL){
        printf("\nCannot open file %s\n", si);
        return;
    }
    rewind(fi);
    fscanf(fi, "%d", &n);
    printf("n = %d\n", n);
    fscanf(fi, "%d", &m);
    printf("m = %d\n", m);

    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++){
            if (i == j) C[i][j] = 0;
            else C[i][j] = oo;
        }

    int a,b,c;
    for (i=1; i<=m; i++){
        fscanf(fi, "%d %d %d\n", &a, &b, &c);
        C[a][b] = c;
    }

    for (i=1; i<=n; i++){
        printf("\n");
        for (j=1; j<=n; j++){
                printf("%10d", C[i][j]);
        }
    }

    printf("\n");
    fclose(fi);
}

void input_stdin(){
    int i, j, k;
    scanf("%d", &n);
    //printf("n = %d\n", n);
    scanf("%d", &m);
    //printf("m = %d\n", m);

    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++) C[i][j] = oo;

    int a,b,c;
    for (i=1; i<=m; i++){
        scanf("%d %d %d\n", &a, &b, &c);
        C[a][b] = c;
    }
    /*
    for (i=1; i<=n; i++){
        printf("\n");
        for (j=1; j<=n; j++){
                printf("%10d", C[i][j]);
        }
    }
    */
}

void init(){
    for (int i=1; i<=n; i++) VISITED[i] = 0;
    VISITED[1] = 1;
    x[1] = 1;
    best = oo;
    //sum = 0;
}

void update(){
    if (sum + C[x[n]][x[1]] < best){
        best = sum + C[x[n]][x[1]];
        for (int i=1; i<=n; i++) bestSolution[i] = x[i];
    }
}

void branchBound (int i){
    int j;
    if (sum >= best) return;
    for (j=1; j<=n; j++){
        if (VISITED[j] == 0){
            x[i] = j;
            VISITED[j] = 1;
            sum = sum + C[x[i-1]][j];
            if (i == n) update();
            else branchBound(i+1);
            sum = sum - C[x[i-1]][j];
            VISITED[j] = 0;
        }
    }
}

void output(){
    /*
    printf("\nTravelling Salesman Problem distance = %d\n", best);
    for (int i=1; i<=n; i++) printf("%d --> ", bestSolution[i]);
    printf("%d\n", bestSolution[1]);
    */
    printf("%d", best);
}

int main(){
    //input();
    input_stdin();
    init();
    branchBound(2);
    output();
    return 0;
}
