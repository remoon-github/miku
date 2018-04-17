#include <cstdio>
#include <cstring>
#include <iostream>
#define dd double
#define sid 505
#define ssd 70
using namespace std;

char s[sid];
dd p[ssd], dp[sid][105];
int yp, cnt;
int q[sid], no[sid], son[sid][ssd], fail[sid];

inline int Opt(char c) {
    if(c >= '0' && c <= '9') return c - '0' + 1;
    if(c >= 'a' && c <= 'z') return c - 'a' + 11;
    if(c >= 'A' && c <= 'Z') return c - 'A' + 37;
    return 0;
}

inline void Init() {
    memset(dp, 0, sizeof(dp));
    memset(son, 0, sizeof(son));
    memset(fail, 0, sizeof(fail));
    memset(q, 0, sizeof(q));
    memset(p, 0, sizeof(p));
    memset(no, 0, sizeof(no));
    cnt = 0;
}

inline void AC() {
    int n;
    scanf("%d", &n);
    while(n --) {
        scanf("%s", s + 1);
        int e = 0;
        int nl = strlen(s + 1);
        for(int i = 1; i <= nl; i ++) {
            int opt = Opt(s[i]);
            if(son[e][opt]) e = son[e][opt];
            else e = son[e][opt] = ++ cnt;
        }
        no[e] = 1;
    }
}

inline void Fail() {
    int fr = 1, to = 0;
    for(int i = 1; i <= 62; i ++) 
    if(son[0][i]) q[++ to] = son[0][i];
    while(fr <= to) {
        int e = q[fr ++];
        for(int i = 1; i <= 62; i ++)
        if(son[e][i]) {
            int d = son[e][i];
            fail[d] = son[fail[e]][i];
            no[d] |= no[fail[d]];
            q[++ to] = d;
        }
        else son[e][i] = son[fail[e]][i];
    }
}

inline void DP() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        char a; cin >> a;
        int opt = Opt(a);
        scanf("%lf", &p[opt]);
    }
    scanf("%d", &n);
    dp[0][0] = 1;
    for(int i = 1; i <= n; i ++)
    for(int j = 0; j <= cnt; j ++)
    if(dp[j][i - 1] > 0)
    for(int k = 1; k <= 65; k ++)
    if(!no[son[j][k]]) {
        int d = son[j][k];
        dp[d][i] += dp[j][i - 1] * p[k];
    }
    dd ans = 0;
    for(int i = 0; i <= cnt; i ++) ans += dp[i][n];
    printf("Case #%d: %.6lf\n", yp, ans);
}

int main() {
    int Tt;
    scanf("%d", &Tt);
    while(Tt --) {
        yp ++;
        Init(); AC();
        Fail(); DP();
    }
    return 0;
}
