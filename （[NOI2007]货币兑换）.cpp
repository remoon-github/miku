#include <cstdio>
#include <iostream>
#include <algorithm>
#define dd double
#define ri register int
#define sid 200050
#define eps 1e-9
#define INF 1047483645
using namespace std;

int n, q[sid];
dd mc, dp[sid];

template <typename re>
inline re abs(re a) { return (a > 0) ? a : -a; }

template <typename re>
inline re upmax(re &a, re b) { if(a < b) a = b; } 

struct Dp {
    int id;
    dd x, y, k;
    dd a, b, rate;
    friend bool operator < (Dp a, Dp b) {
        return a.k > b.k;
    }
} f[sid], g[sid];

inline dd s(int i, int j) {
    dd dx = f[i].x - f[j].x, dy = f[i].y - f[j].y;
    if(abs(dx) < eps) return INF;
    return dy / dx;
}

inline void Solve(int l, int r) {

    if(l == r) {
        upmax(dp[l], dp[l - 1]);
        f[l].y = dp[l] / (f[l].a * f[l].rate + f[l].b);
        f[l].x = f[l].y * f[l].rate;
        return;
    }

    int mid = (l + r) >> 1;
    int h1 = l, h2 = mid + 1;
    for(ri i = l; i <= r; i ++)
    if(f[i].id <= mid) g[h1 ++] = f[i];
    else g[h2 ++] = f[i];
    for(ri i = l; i <= r; i ++) f[i] = g[i];

    Solve(l, mid);

    int to = 0;
    for(ri i = l; i <= mid; i ++) {
        while(to > 1 && s(q[to], q[to - 1]) < s(q[to - 1], i) + eps) to --;
        q[++ to] = i;
    }
    int fr = 1;
    for(ri i = mid + 1; i <= r; i ++) {
        while(fr < to && s(q[fr], q[fr + 1]) + eps > f[i].k) fr ++;
        upmax(dp[f[i].id], f[q[fr]].x * f[i].a + f[q[fr]].y * f[i].b);
    }

    Solve(mid + 1, r);

    h1 = l; h2 = mid + 1;
    ri j = l - 1;
    while(h1 <= mid && h2 <= r) {
        if(f[h1].x < f[h2].x ||(abs(f[h1].x - f[h2].x) < eps && f[h1].y < f[h2].y)) g[++ j] = f[h1 ++];
        else g[++ j] = f[h2 ++];
    }
    while(h1 <= mid) g[++ j] = f[h1 ++];
    while(h2 <= r) g[++ j] = f[h2 ++];
    for(ri i = l; i <= r; i ++) f[i] = g[i];

}

int main() {
    scanf("%d%lf", &n, &mc);
    dp[0] = mc;
    for(ri i = 1; i <= n; i ++) {
        scanf("%lf%lf%lf", &f[i].a, &f[i].b, &f[i].rate);
        f[i].k = - f[i].a / f[i].b; f[i].id = i;
    }
    sort(f + 1, f + n + 1);
    Solve(1, n);
    printf("%.3lf\n", dp[n]);
    return 0;
}
