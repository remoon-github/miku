#include <cstdio>
#include <cstring>
#define sid 40005
#define ll long long
#define ri register int
using namespace std;

#define getchar() *S ++
char RR[30000005], *S = RR;
inline int read() {
    int p = 0, w = 1;
    char c = getchar();
    while(c > '9' || c < '0') {
        if(c == '-') w = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
        p = p * 10 + c - '0';
        c = getchar();
    }
    return p * w;
}

ll dp[100][41][41];
ll a[sid], b[sid], c[sid];
int s[sid], t[sid], n;
int trk[sid], dfn[sid], top, cnt;

template <typename re>
inline re min(re a, re b) {
    return (a > b) ? b : a;
}

inline void dfs(int e) {
    dfn[e] = top ? trk[top --] : ++ cnt;
    int now = dfn[e];
    if(!s[e]) {
        for(int i = 0; i <= 40; i ++)
        for(int j = 0; j <= 40; j ++)
        dp[now][i][j] = c[e] * (a[e] + i) * (b[e] + j);
        return;
    }
    dfs(s[e]); 
    dfs(t[e]);
    int ls = dfn[s[e]], rs = dfn[t[e]];
    for(int i = 0; i <= 40; i ++)
    for(int j = 0; j <= 40; j ++)
    dp[now][i][j] = min(dp[ls][i + 1][j] + dp[rs][i][j], dp[ls][i][j] + dp[rs][i][j + 1]);
    trk[++ top] = ls;
    trk[++ top] = rs;
}

int main() {
    fread(RR, 1, sizeof(RR), stdin);
    memset(dp, 127, sizeof(dp));
    n = read();
    for(ri i = 1; i < n; i ++) { 
        s[i] = read(); t[i] = read(); 
        if(s[i] <= 0) s[i] = n - s[i] - 1;
        if(t[i] <= 0) t[i] = n - t[i] - 1;
    }
    for(ri i = 0; i < n; i ++) { 
        a[i + n] = read(); b[i + n] = read(); c[i + n] = read(); 
    }
    dfs(1);
    printf("%lld\n", dp[dfn[1]][0][0]);
    return 0;
}