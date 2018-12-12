#include<stdio.h>
#include<queue>
#define MAX 100
using namespace std;


int n;
int start_i,start_j;
bool visited[MAX][MAX];
int A[MAX][MAX];
int di[4] = {1,-1,0,0};
int dj[4] = {0,0,1,-1};

void init() {
    int i,j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <=n ; j++) visited[i][j] = false;
}

bool check (int i1, int j1) {
    return A[i1][j1] == 0 && !visited[i1][j1];
}

void solve(){
    init();
    queue<int> Q;
    Q.push(start_i); Q.push(start_j); Q.push(0);
    visited[start_i][start_j] = true;
    while (!Q.empty()) {
        int i,j,d,t;
        i = Q.front(); Q.pop();
        j = Q.front(); Q.pop();
        d = Q.front(); Q.pop();
        for (t = 0; t <= 3; t++) {
            int i1,j1,d1;
            i1 = i + di[t];
            j1 = j + dj[t];
            d1 = d + 1;
            if (i1 < 1 || i1 > n || j1 < 1 || j1 > n) {
                printf("%d",d1);
                return;
            }
            if(check(i1,j1)) {
                Q.push(i1); Q.push(j1); Q.push(d1);
                visited[i1][j1] = true;
            }
        }
    }
}

void input()
{
    scanf("%d%d%d",&n,&start_i,&start_j);
    int i,j;
    for (i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            scanf("%d", &A[i][j]);
}

int main(){
    input();
    solve();
    return 0;
}
