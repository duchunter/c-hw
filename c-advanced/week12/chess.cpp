#include<stdio.h>
#define MAX 20
#define MAX_2 400
int n;
int start_i;
int start_j;
int count;
int di[] = {-2,-1,1,2,2,1,-1,-2};
int dj[] = {-1,-2,-2,-1,1,2,2,1};
bool visited[MAX][MAX];
int x_si[MAX_2];
int x_sj[MAX_2];

void init() {
    int i,j;
    for (i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            visited[i][j] = false;
}

bool check (int i, int j) {
    if (i < 1 || i > n || j < 1 || j > n) return false;
    if (visited[i][j]) return false;
    return true;
}

void solution() {
    int k;
    count++;
    printf("%d: ",count);
    for (k = 1; k <= n * n; k++) printf("(%d,%d) ",x_si[k],x_sj[k]);
    printf("\n");
}

void TRY (int k) {
    int t,i,j;
    for (t = 0; t <= 7; t++) {
        i = x_si[k-1] + di[t];
        j = x_sj[k-1] + dj[t];
        if (check(i,j)) {
            x_si[k] = i;
            x_sj[k] = j;
            visited[i][j] = true;
            if (k == n * n) {
                solution();
            } else {
                TRY(k+1);
            }
            visited[i][j] = false;
        }
    }
}

void solve() {
    init();
    x_si[1] = start_i;
    x_sj[1] = start_j;
    visited[start_i][start_j] = true;
    count = 0;
    TRY(2);
}

void input() {
    scanf("%d%d%d", &n,&start_i,&start_j);
}

int main() {
    input();
    solve();
    return 0;
}
