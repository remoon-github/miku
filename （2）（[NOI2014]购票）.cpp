#include <cstdio>
#include <algorithm>
#define sid 400050
#define dd double
#define ri register int
#define ll long long
using namespace std;

#define getchar() *S ++
char RR[50000005], *S = RR;
template <typename re>
inline void read(re &p) {
    p = 0; re w = 1;
    char c = getchar();
    while(c > '9' || c < '0') {
        if(c == '-') w = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
        p = p * 10 + c - '0';
        c = getchar();
    }
    p *= w;
}

template <typename re>
inline void upmax(re &a, re b) { if(a < b) a = b; }

template <typename re>
inline void upmin(re &a, re b) { if(a > b) a = b; }

int n, cnt, cnt1, cnt2, root, All_son;
int nxt[sid], node[sid], cap[sid];
ll pv[sid], qv[sid], lv[sid];
int fa[sid], q[sid], q2[sid];
int sz[sid], son[sid], qp[sid];
int vis[sid], dfn;
ll dis[sid], dp[sid], mk[sid];

inline void Unicom(int u, int v, int w) {
    nxt[++ cnt] = cap[u]; cap[u] = cnt; node[cnt] = v;
    nxt[++ cnt] = cap[v]; cap[v] = cnt; node[cnt] = u;
}

inline void GR(int e, int fa) {
    sz[e] = 1; son[e] = 0;
    for(int i = cap[e]; i; i = nxt[i]) {
        int d = node[i];
        if(d == fa || vis[d]) continue;
        GR(d, e); sz[e] += sz[d];
        upmax(son[e], sz[d]);
    }
    upmax(son[e], All_son - sz[e]);
    if(son[e] < son[root]) root = e;
}

inline void QD(int e, int fa) {
    qp[++ cnt1] = e;
    for(int i = cap[e]; i; i = nxt[i]) {
        int d = node[i];
        if(d == fa || vis[d]) continue;
        QD(d, e);
    }
}

inline bool cmp1(int i, int j) {
    return dis[i] - lv[i] < dis[j] - lv[j];
}

inline bool cmp2(int i, int j) {
    if(mk[i] != mk[j]) return mk[i] > mk[j];
    return pv[i] < pv[j];
}

inline dd s(int i, int j) {
    return (dd)(dp[i] - dp[j]) / (dis[i] - dis[j]);
}

inline void PS(int e) {
    vis[e] = ++ dfn;
    for(ri i = cap[e]; i; i = nxt[i]) {
        int d = node[i];
        if(d != fa[e] || vis[d]) continue;
        All_son = sz[d]; root = 0;
        GR(d, e); PS(root);
    }
    cnt1 = cnt2 = 0; 
    q2[++ cnt2] = e;
    for(ri i = cap[e]; i; i = nxt[i]) {
        int d = node[i];
        if(vis[d]) continue; QD(d, e);
    }
    sort(qp + 1, qp + cnt1 + 1, cmp1);
    int qr = 1;
    for(ri i = fa[e]; vis[i] > vis[e]; i = fa[i]) {
        q2[++ cnt2] = i;
        if(dis[e] - lv[e] <= dis[i]) upmin(dp[e], dp[i] + pv[e] * (dis[e] - dis[i]) + qv[e]);
    }
    for(ri i = cnt2; i >= 1; i --)
    while(dis[qp[qr]] - lv[qp[qr]] <= dis[q2[i]] && qr <= cnt1)  mk[qp[qr ++]] = dis[q2[i]];
    for(ri i = qr; i <= cnt1; i ++) mk[qp[i]] = -1;
    sort(qp + 1, qp + cnt1 + 1, cmp2);
    ri fr = 200001, to = 200000; qr = 1;
    for(ri i = 1; i <= cnt2; i ++) {
        int eq = q2[i];
        while(fr <= to - 1 && s(eq, q[fr + 1]) > s(q[fr], q[fr + 1]) + 1e-8) fr ++;
        q[-- fr] = eq; int bfr = fr;
        while(mk[qp[qr]] == dis[eq] && qr <= cnt1) {
            int p = qp[qr];
            while(fr + 1 <= to && s(q[fr], q[fr + 1]) < pv[p]) fr ++;
            upmin(dp[p], dp[q[fr]] + pv[p] * (dis[p] - dis[q[fr]]) + qv[p]);
            qr ++;
        }
        fr = bfr;
    }
    for(ri i = cap[e]; i; i = nxt[i]) {
        int d = node[i]; if(vis[d] || d == fa[e]) continue;
        All_son = sz[d]; root = 0;
        GR(d, e); PS(root);
    }
}

int main() {
    fread(RR, 1, sizeof(RR), stdin);
    read(n); int t; read(t);
    for(ri i = 2; i <= n; i ++) {
        int f, w;
        read(f); read(w);
        fa[i] = f; dis[i] = dis[f] + w;
        read(pv[i]); read(qv[i]); read(lv[i]);
        Unicom(f, i, w); dp[i] = (1LL << 55);
    }
    vis[0] = 1;
    son[0] = n; All_son = n;
    GR(1, 0); PS(root);
    for(ri i = 2; i <= n; i ++) printf("%lld\n", dp[i]);
    return 0;
}
