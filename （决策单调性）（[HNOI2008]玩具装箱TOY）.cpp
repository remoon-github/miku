#include <cstdio>
#include <iostream>
#define sid 100050
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

int n, top, L;
int lp[sid], go[sid], c[sid];
ll dp[sid], pre[sid];


inline ll Dp(int i, int j) {
    ll tmp = pre[j] - pre[i] - L - 1;
    return dp[i] + tmp * tmp;
}

inline int Binary(int run) {
    int l = lp[top], r = n;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(Dp(run, mid) < Dp(go[top], mid)) r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

inline void DP() {
    int tra = top = 1;
    lp[1] = 1; go[1] = 0;
    for(ri i = 1; i <=  n; i ++) {
        if(i == lp[tra + 1]) tra ++;
        dp[i] = Dp(go[tra], i);
        while(Dp(i, lp[top]) < Dp(go[top], lp[top])) top --;
        int tmp = Binary(i);
        if(tmp <= n) lp[++ top] = tmp, go[top] = i;
    }
}

int main() {
    fread(RR, 1, sizeof(RR), stdin);
    n = read(); L = read();
    for(ri i = 1; i <= n; i ++) c[i] = read();
    for(ri i = 1; i <= n; i ++) pre[i] = pre[i - 1] + c[i];
    for(ri i = 1; i <= n; i ++) pre[i] += i;
    DP();
    printf("%lld\n", dp[n]);
    return 0;
}
