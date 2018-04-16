#include <cstdio>
#define sid 200050
#define ssd 3000500
#define ri register int
using namespace std;

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

inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int n, m, s, t, cnt = 1;
int lev[sid], cap[sid], cur[sid], q[sid];
int nxt[ssd], res[ssd], node[ssd], mark[sid];

inline void Unicom(int u, int v, int w) {
    nxt[++ cnt] = cap[u]; cap[u] = cnt;
    node[cnt] = v; res[cnt] = w;
    nxt[++ cnt] = cap[v]; cap[v] = cnt;
    node[cnt] = u;  res[cnt] = 0; 
}

inline void Bfs() {
    ++ mark[1];
    for(ri i = 1; i <= t; i ++) cur[i] = cap[i];
    int fr = 1, to = 2;
    q[fr] = t; lev[t] = 1;
    while(fr <= to) {
        int e = q[fr ++];
        for(ri i = cap[e]; i; i = nxt[i]) {
            int d = node[i];
            if(lev[d] || !res[i ^ 1]) continue;
            lev[d] = lev[e] + 1; ++ mark[lev[d]];
            q[++ to] = d;
        }
    }
}

inline int Dfs(int e, int ff) {
    int tmp, tt = 0;
    if(e == t) return ff;
    for(int &i = cur[e]; i; i = nxt[i]) {
        int d = node[i];
        if(lev[e] != lev[d] + 1) continue;
        tmp = Dfs(d, min(ff, res[i]));
        tt += tmp; ff -= tmp;
        res[i] -= tmp; res[i ^ 1] += tmp;
        if(!ff) return tt;
    }
    if(!(-- mark[lev[e]])) lev[s] = t + 1;
    ++ mark[++ lev[e]]; cur[e] = cap[e];
    return tt;
}

inline int ISAP() {
    Bfs();
    int ans = Dfs(s, 1e9);
    while(lev[s] <= t) ans += Dfs(s, 1e9);
    return ans;
}

int main() {
    n = read(); m = read();
    int sum = 0;
    s = n + m + 1; t = s + 1;
    for(ri i = 1; i <= n; i ++) {
        int pw = read(), pn = read();
        sum += pw; Unicom(s, i, pw);
        for(ri j = 1; j <= pn; j ++) {
            int u = read(), w = read();
            Unicom(i, u + n, w);
        }
    }
    for(ri i = 1; i <= m; i ++) Unicom(n + i, t, read());
    printf("%d\n", sum - ISAP());
    return 0;
}