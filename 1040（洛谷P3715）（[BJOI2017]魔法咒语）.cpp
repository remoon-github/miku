#include <cstdio>
#include <cstring>
#define sid 205
#define mod (1000000007)
#define ri register int
using namespace std;

inline void up(int &x, int y) {
    x += y;
    if(x > mod) x -= mod;
}

int n, m, cnt, L;
bool no[sid];
char go[sid][sid], s[sid];
int q[sid], son[sid][27], fail[sid];
int tra[sid][sid], len[sid];

inline void Trie() {
    scanf("%s", s + 1);
    int nl = strlen(s + 1);
    int e = 0;
    for(ri i = 1; i <= nl; i ++) {
        int opt = s[i] - 'a' + 1;
        if(son[e][opt]) e = son[e][opt];
        else e = son[e][opt] = ++ cnt;
    }
    no[e] = 1;
}

inline void Fail() {
    int fr = 1, to = 0;
    for(ri i = 1; i <= 26; i ++)
    if(son[0][i]) q[++ to] = son[0][i];
    while(fr <= to) {
        int e = q[fr ++];
        for(ri i = 1; i <= 26; i ++)
        if(son[e][i]) {
            int d = son[e][i];
            fail[d] = son[fail[e]][i];
            no[d] |= no[fail[d]];
            q[++ to] = d;
        }
        else son[e][i] = son[fail[e]][i];
    }
}

inline void Pre() {
    for(ri i = 0; i <= cnt; i ++)
    for(ri j = 1; j <= n; j ++) {
        int e = i;
        for(ri k = 1; k <= len[j]; k ++) {
            int opt = go[j][k] - 'a' + 1;
            if(no[e]) break;
            e = son[e][opt];
        }
        if(!no[e]) tra[i][j] = e;
        else tra[i][j] = -1;
    }
}

int f[sid][sid];

inline void DP() {
    f[0][0] = 1;
    for(ri i = 0; i < L; i ++)
    for(ri j = 0; j <= cnt; j ++)
    for(ri k = 1; k <= n; k ++)
    if(tra[j][k] != -1)
    up(f[i + len[k]][tra[j][k]], f[i][j]);
    int ans = 0;
    for(ri i = 0; i <= cnt; i ++) up(ans, f[L][i]);
    printf("%d\n", ans);
}

int cp;

struct Martix {
    int dp[sid][sid];
    Martix() {}
    Martix(int flag) {
        for(ri i = 0; i < cp; i ++)
        for(ri j = 0; j < cp; j ++)
        dp[i][j] = (i == j) ? flag : 0;
    }
    int* operator [] (const int x) {
        return dp[x];
    }
    friend Martix operator * (Martix a, Martix b) {
        Martix c(0);
        for(ri i = 0; i < cp; i ++)
        for(ri j = 0; j < cp; j ++)
        for(ri k = 0; k < cp; k ++)
        if(a[i][k] || b[k][j]) //加速
        c[i][j] = (c[i][j] + (1ll * a[i][k] * b[k][j]) % mod) % mod;
        return c;
    }
} ans, arv;

inline void Martix_DP() { 
    cp = ((cnt + 1) << 1) - 1;
    
    ans = Martix(1);

    for(ri i = 0; i <= cnt; i ++) 
    arv[i + cnt + 1][i] ++;

    for(ri i = 0; i <= cnt; i ++)
    for(ri j = 1; j <= n; j ++)
    if(tra[i][j] != -1) 
    if(len[j] == 1) arv[tra[i][j]][i] ++;
    else arv[tra[i][j]][i + cnt + 1] ++;

    int k = L;
    while(k) {
        if(k & 1) ans = arv * ans;
        arv = arv * arv;
        k >>= 1;
    }
    
    int sum = 0;
    for(ri i = 0; i <= cnt; i ++) up(sum, ans[i][0]);
    printf("%d\n", sum);
}

int main() {
    scanf("%d%d%d", &n, &m, &L);
    for(ri i = 1; i <= n; i ++) 
    scanf("%s", go[i] + 1), len[i] = strlen(go[i] + 1); 
    for(ri i = 1; i <= m; i ++) Trie();
    Fail();
    Pre();
    if(L <= 10000) DP();
    else Martix_DP();
    return 0;
}