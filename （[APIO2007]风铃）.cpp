#include <cstdio>
#include <iostream>
#define sid 200050
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

int n, ans;
bool has[sid], flag;
int dep[sid], ma[sid], mi[sid];
int sz[sid], ls[sid], rs[sid];

inline void dfs(int e) {
    if(e > n) {
        ma[e] = dep[e]; mi[e] = dep[e];
        return;
    }
    dep[ls[e]] = dep[e] + 1;
    dep[rs[e]] = dep[e] + 1;
    dfs(ls[e]); dfs(rs[e]);
    sz[e] += sz[ls[e]];
    sz[e] += sz[rs[e]];
    ma[e] = max(ma[ls[e]], ma[rs[e]]);
    mi[e] = min(mi[ls[e]], mi[rs[e]]);
    if(ma[e] - mi[e] > 0) has[e] = 1;
    if(has[ls[e]] && has[rs[e]]) flag = 1;
}

inline void dfs2(int e) {
    if(e > n) return 0;
    if(sz[rs[e]] > sz[ls[e]]) ans ++;
    dfs2(ls[e]); dfs2(rs[e]);
}

int main() {
    fread(RR, 1, sizeof(RR), stdin);
    n = read(); 
    int ord = n;
    for(ri i = 1; i <= n; i ++) {
        ls[i] = read(); rs[i] = read();
        if(ls[i] == -1) ls[i] = ++ ord, sz[ls[i]] = 1;
        if(rs[i] == -1) rs[i] = ++ ord, sz[rs[i]] = 1;
    }
    dep[1] = 0;
    dfs(1);
    if(ma[1] - mi[1] > 1 || flag) {
        puts("-1"); return 0;
    } 
    dfs2(1);
    printf("%d", ans);
    return 0;
}
