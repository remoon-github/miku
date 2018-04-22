#include <cstdio>
#include <iostream>
#include <cstring>
#define sid 100050
#define ll long double
#define ri register int
using namespace std;

char s[sid][35];
int n, P, L;
int lp[sid], go[sid], top;
int c[sid], pre[sid], lst[sid];
ll dp[sid];

template <typename re>
inline re abs(re a) { return (a > 0) ? a : -a; }

inline ll qpow(ll a, int k) {
    ll tmp = (ll)1.0;
    while(k) {
        if(k & 1) tmp *= a;
        a *= a; k >>= 1;
    }
    return tmp;
}

inline ll Dp(int i, int j) {
    ll tmp = abs((ll)(pre[j] - pre[i] - L + j - i - 1));;
    return dp[i] + qpow(tmp, P);
}

inline int Binary(int rg) {
    int l = lp[top], r = n;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(Dp(rg, mid) < Dp(go[top], mid)) r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

inline void DP() {
    int tra = top = 1;
    lp[1] = 1; go[1] = 0;
    for(ri i = 1; i <= n; i ++) {
        if(i == lp[tra + 1]) tra ++;
        dp[i] = Dp(go[tra], i); lst[i] = go[tra];
        while(Dp(i, lp[top]) < Dp(go[top], lp[top])) top --;
        int tmp = Binary(i);
        if(tmp <= n) lp[++ top] = tmp, go[top] = i;
    }
}

inline void Print(int e) {
    if(lst[e]) Print(lst[e]);
    for(ri i = lst[e] + 1; i < e; i ++) printf("%s ", s[i] + 1);
    printf("%s", s[e] + 1); printf("\n");
}

int main() {
    int Tt;
    scanf("%d", &Tt);
    while(Tt --) {
        scanf("%d%d%d", &n, &L, &P);
        for(ri i = 1; i <= n; i ++) {
            scanf("%s", s[i] + 1);
            c[i] = strlen(s[i] + 1);
            pre[i] = pre[i - 1] + c[i];
        }
        memset(lp, 0, sizeof(lp));
        DP();
        if(dp[n] <= 1e18) {
            printf("%.0Lf\n", dp[n]);
            Print(n);
        }
        else printf("Too hard to arrange\n");
        printf("--------------------\n");
    }
    return 0;
}