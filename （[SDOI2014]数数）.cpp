#include <cstdio>
#include <cstring>
#define sid 200050
#define mod 1e9 + 7
#define ri register int
#define ch son[j][k]
using namespace std;

char s[sid], sc[sid];
bool no[sid];
int q[sid], son[sid][11], fail[sid], cnt;
int dp[2][1300][2000], ans, n;

inline void up(int &x, int y) {
    x += y;
    if(x > mod) x -= mod;
}

inline void Insert() {
    int e = 0;
    int nl = strlen(s + 1);
    for(ri i = 1; i <= nl; i ++) {
        int opt = s[i] - '0' + 1;
        if(son[e][opt]) e = son[e][opt];
        else e = son[e][opt] = ++ cnt;
    }
    no[e] = 1;
}

inline void Build() {
    int fr = 1, to = 0;
    int e = 0;
    for(ri i = 1; i <= 10; i ++) 
    if(son[e][i]) q[++ to] = son[e][i];
    while(fr <= to) {
        e = q[fr ++];
        for(ri i = 1; i <= 10; i ++) {
            int &d = son[e][i], v = son[fail[e]][i];
            if(!d) { d = v; continue; }
            q[++ to] = d; fail[d] = v; no[d] |= no[v];
        }
    }
}

inline void DP() {
    int nl = strlen(sc + 1);
    for(ri i = 0; i < nl; i ++)
    for(ri j = 0; j <= cnt; j ++) {
        int opt = sc[i + 1] - '0' + 1;
        int p1 = dp[0][i][j], p2 = dp[1][i][j];
        if(p1) {
            for(ri k = 1; k <= 10; k ++)
            if(!no[ch]) up(dp[0][i + 1][ch], p1);
        }
        if(p2) {
            for(ri k = 1; k < opt; k ++)
            if(!no[ch]) up(dp[0][i + 1][ch], p2);
            if(!no[son[j][opt]]) up(dp[1][i + 1][son[j][opt]], p2);
        }
        if(j == 0) {
            if(i == 0) {
                for(ri k = 2; k < opt; k ++)
                if(!no[ch]) up(dp[0][i + 1][ch], 1);
                if(!no[son[j][opt]]) up(dp[1][i + 1][son[j][opt]], 1);
            }
            else  {
                for(ri k = 2; k <= 10; k ++)
                if(!no[ch]) up(dp[0][i + 1][ch], 1);
            }
        }
    }
    for(ri i = 0; i <= cnt; i ++)
    up(ans, dp[0][nl][i]), up(ans, dp[1][nl][i]);
    printf("%d\n", ans);
}

int main() {
    scanf("%s", sc + 1);
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%s", s + 1);
        Insert();
    }
    Build();
    DP();
    return 0;
}