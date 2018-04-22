#include <cstdio>
#define sid 100050
#define dd double
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

int q[sid], c[sid], n;
ll dp[sid], pre[sid], L;

#define x(g) (pre[g])
#define y(g) (dp[g] + pre[g] * pre[g] + L * L + 2 * L * pre[g])
#define s(g, h) (dd)((y(g) - y(h)) / (x(g) - x(h)))

int main() {
    fread(RR, 1, sizeof(RR), stdin);
    n = read(); L = read() + 1;
    for(ri i = 1; i <= n; i ++) c[i] = read();
    for(ri i = 1; i <= n; i ++) pre[i] = pre[i - 1] + c[i];
    for(ri i = 1; i <= n; i ++) pre[i] += i;
    int fr = 1, to = 1;
    for(ri i = 1; i <= n; i ++) {
        while(fr < to && 2 * pre[i] > s(q[fr], q[fr + 1])) fr ++;
        ll tmp = pre[i] - pre[q[fr]] - L; dp[i] = dp[q[fr]] + tmp * tmp;
        while(fr < to && s(i, q[to - 1]) < s(q[to], q[to - 1])) to --;
        q[++ to] = i;
    }
    printf("%lld\n", dp[n]);
    return 0;
}
