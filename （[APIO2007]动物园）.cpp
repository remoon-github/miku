#include <cstdio>
#include <iostream>
#define sid 70050
#define ri register int
using namespace std;

int n, m, ans;
int dp[sid][33], f[sid][33];

int main() {
    int n, m, E, F, L, X, Y;
    scanf("%d%d", &n, &m);
    for(ri i = 1; i <= m; i ++) {
        scanf("%d%d%d", &E, &F, &L);
        int sta1 = 0, sta2 = 0;
        for(ri j = 1; j <= F; j ++) {
            scanf("%d", &X); X = (read() - E + n) % n; 
            sta1 |= (1 << X);
        }
        for(ri j = 1; j <= L; j ++) {
            scanf("%d", &Y); Y = (read() - E + n) % n; 
            sta2 |= (1 << Y);
        }
        for(ri j = 0; j < 32; j ++) 
        if((j & sta1) || (~j & sta2)) f[E][j] ++;
    }
    for(ri i = 0; i < 32; i ++) {
        for(ri j = 0; j < 32; j ++) dp[0][j] = -666666;
        dp[0][i] = 0;
        for(ri j = 1; j <= n; j ++)
        for(ri k = 0; k < 32; k ++)
        dp[j][k] = max(dp[j - 1][(k & 15) << 1], dp[j - 1][(k & 15) << 1 | 1]) + f[j][k];
        ans = max(ans, dp[n][i]);
    }
    printf("%d\n", ans);
    return 0;
}
