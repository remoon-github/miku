#include <cstdio>
#include <algorithm>
#define sid 400050
#define dd double
#define ri register int
#define ll long long
using namespace std;

#define gc() *S ++
char RR[50000005], *S = RR;
template <typename re>
inline void read(re &p) {
    p = 0; re w = 1; char c = gc();
    while(c > '9' || c < '0') { if(c == '-') w = -1; c = gc(); }
    while(c >= '0' && c <= '9') { p = p * 10 + c - '0'; c = gc(); }
    p *= w;
}

template <typename re>
inline void upmax(re &a, re b) { if(a < b) a = b; }

template <typename re>
inline void upmin(re &a, re b) { if(a > b) a = b; }

int n, cnt, cnt1, cnt2, root, All_son;
int nxt[sid], node[sid], cap[sid];
int fa[sid], q[sid], q2[sid];
int sz[sid], son[sid], qp[sid];
int vis[sid], dfn;
ll dis[sid], dp[sid];
ll pv[sid], qv[sid], lv[sid];

inline void Unicom(int u, int v, int w) {
    nxt[++ cnt] = cap[u]; cap[u] = cnt; node[cnt] = v;
    nxt[++ cnt] = cap[v]; cap[v] = cnt; node[cnt] = u;
}

inline void Root(int e, int fa) {
    sz[e] = 1; son[e] = 0;
    for(int i = cap[e]; i; i = nxt[i]) {
        int d = node[i];
        if(d == fa || vis[d]) continue;
        Root(d, e); sz[e] += sz[d];
        upmax(son[e], sz[d]);
    }
    upmax(son[e], All_son - sz[e]);
    if(son[e] < son[root]) root = e;
}

inline void Queue(int e, int fa) {
    qp[++ cnt1] = e;
    for(int i = cap[e]; i; i = nxt[i]) {
        int d = node[i];
        if(d == fa || vis[d]) continue;
        Queue(d, e);
    }
}

inline bool cmp1(int i, int j) {
    return dis[i] - lv[i] > dis[j] - lv[j];
}

inline dd s(int i, int j) {
    return (dd)((dd)(dp[i] - dp[j]) / (dd)(dis[i] - dis[j]));
}

inline ll tra(int i, int j) {
    ll tmp = dp[i] + pv[j] * (dis[j] - dis[i]) + qv[j];
    return tmp;
}

inline void Solve(int e) {
    vis[e] = ++ dfn;
    for(ri i = cap[e]; i; i = nxt[i]) {
        int d = node[i];
        if(d != fa[e] || vis[d]) continue;
        All_son = sz[d]; root = 0;
        Root(d, e); Solve(root);
    }
    cnt1 = cnt2 = 0; q2[++ cnt2] = e;
    for(ri i = cap[e]; i; i = nxt[i]) {
        int d = node[i];
        if(vis[d]) continue; Queue(d, e);
    }
    sort(qp + 1, qp + cnt1 + 1, cmp1);
    for(ri i = fa[e]; vis[i] > vis[e]; i = fa[i]) {
        q2[++ cnt2] = i;
        if(dis[e] - lv[e] <= dis[i]) upmin(dp[e], tra(i, e));
    }
    int fr = 200001, to = 200000, qr = 1;
    for(ri i = 1; i <= cnt2; i ++) {
        int p = q2[i];
        while(fr + 1 <= to && s(p, q[fr + 1]) > s(q[fr], q[fr + 1])) fr ++;
        q[-- fr] = p;
        while(1) {
            if(qr > cnt1) break;
            if(dis[qp[qr]] - lv[qp[qr]] > dis[p]) { qr ++; continue; }
            if(i != cnt2 && dis[qp[qr]] - lv[qp[qr]] <= dis[q2[i + 1]]) break;
            int pp = qp[qr ++];
            int l = fr, r = to;
            if(r - l <= 3)
            for(ri j = l; j <= r; j ++) upmin(dp[pp], tra(q[j], pp));
            else {
                while(r - l <= 3) {
                    int lp = l + (r - l) / 3, rp = lp + (r - l) / 3;
                    ll fl = tra(q[lp], pp), fr = tra(q[rp], pp);
                    if(fl <= fr) r = rp; else l = lp;
                }
                for(ri j = l; j <= r; j ++) upmin(dp[pp], tra(q[j], pp));
            }
        }
    }
    for(ri i = cap[e]; i; i = nxt[i]) {
        int d = node[i]; if(vis[d] || d == fa[e]) continue;
        All_son = sz[d]; root = 0;
        Root(d, e); Solve(root);
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
    Root(1, 0); Solve(root);
    for(ri i = 2; i <= n; i ++) printf("%lld\n", dp[i]);
    return 0;
}