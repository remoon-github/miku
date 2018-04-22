#include <cstdio>
#include <cstring>
#define sid 105
#define dd long double
using namespace std;

char s[sid];
int n, L, sz;
int q[sid], fail[sid], son[sid][27], tot;
bool no[sid], vis[sid];

struct Martix {
    dd dp[sid][sid];
    Martix() {}
    Martix(int flag) {
        for(int i = 0; i <= tot; i ++)
        for(int j = 0; j <= tot; j ++)
        dp[i][j] = (i == j) ? ((flag) ? (dd)1.0 : (dd)0.0) : (dd)0.0;
    }
    dd* operator [] (const int x) {
        return dp[x];
    }
    friend Martix operator * (Martix a, Martix b) {
        Martix c(0);
        for(int i = 0; i <= tot; i ++)
        for(int j = 0; j <= tot; j ++)
        for(int k = 0; k <= tot; k ++)
        c[i][j] += a[i][k] * b[k][j];
        return c;
    }
} ans, arv;

inline void Trie() {
    scanf("%s", s + 1);
    int nl = strlen(s + 1);
    int e = 0;
    for(int i = 1; i <= nl; i ++) {
        int opt = s[i] - 'a' + 1;
        if(son[e][opt]) e = son[e][opt];
        else e = son[e][opt] = ++ tot;
    }
    no[e] = 1;
}

inline void Fail() {
    int fr = 1, to = 0;
    for(int i = 1; i <= sz; i ++)
    if(son[0][i]) q[++ to] = son[0][i];
    while(fr <= to) {
        int e = q[fr ++];
        for(int i = 1; i <= sz; i ++)
        if(son[e][i]) {
            int d = son[e][i];
            fail[d] = son[fail[e]][i];
            no[d] |= no[fail[d]];
            q[++ to] = d;
        }
        else son[e][i] = son[fail[e]][i];
    }
}

inline void Create() {
    int fr = 1, to = 1;
    q[1] = 0; vis[0] = 1;
    dd p = (dd)1.0 / sz;
    while(fr <= to) {
        int e = q[fr ++];
        for(int i = 1; i <= sz; i ++) {
            int d = son[e][i];
            if(!vis[d]) vis[d] = 1, q[++ to] = d;
            if(no[d]) arv[e][tot] += p, arv[e][0] += p;
            else arv[e][d] += p;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &L, &sz);
    for(int i = 1; i <= n; i ++) Trie();
    Fail();
    tot ++; Create();
    arv[tot][tot] = (dd)1.0;
    ans = Martix(1);
    while(L) {
        if(L & 1) ans = ans * arv;
        arv = arv * arv;
        L >>= 1; 
    }
    printf("%.7Lf\n", ans[0][tot]);
    return 0;
}
