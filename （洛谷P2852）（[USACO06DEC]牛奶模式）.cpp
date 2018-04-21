#include <cstdio>
#include <iostream>
#define sid 2000050
#define rep(an,aa,ab,ad) for((an) = (aa); (an) <= (ab); (an) += (ad))
#define rop(an,aa,ab,ad) for((an) = (aa); (an) >= (ab); (an) -= (ad))
using namespace std;

inline int read() {
    int x;
    scanf("%d", &x);
    return x;
}

int n, kn;
int s[sid], sa[sid], rk[sid], ht[sid];
int p1[sid], p2[sid], cnt[sid];

inline void SS() {
    int *t1 = p1, *t2 = p2, m = 1000005;
    int i, j;
    rep(i, 1, n, 1) cnt[t1[i] = s[i]] ++;
    rep(i, 1, m, 1) cnt[i] += cnt[i - 1];
    rop(i, n, 1, 1) sa[cnt[t1[i]] --] = i;
    rep(j, 1, n, j) {
        int p = 0;
        rep(i, 0, m, 1) t2[i] = 0;
        rep(i, n - j + 1, n, 1) t2[++ p] = i;
        rep(i, 1, n, 1) if(sa[i] > j) t2[++ p] = sa[i] - j;
        rep(i, 0, m, 1) cnt[i] = 0;
        rep(i, 1, n, 1) cnt[t1[t2[i]]] ++;
        rep(i, 1, m, 1) cnt[i] += cnt[i - 1];
        rop(i, n, 1, 1) sa[cnt[t1[t2[i]]] --] = t2[i];
        swap(t1, t2); t1[sa[1]] = p = 1;
        rep(i, 2, n, 1) t1[sa[i]] = (t2[sa[i-1]] == t2[sa[i]] && t2[sa[i-1]+j] == t2[sa[i]+j]) ? p : ++ p;
        if(p >= n) break; m = p;
    }
}

inline void GH() {
    int i, j, k = 0;
    rep(i, 1, n, 1) rk[sa[i]] = i;
    rep(i, 1, n, 1) {
        if(k) k --;
        j = sa[rk[i] - 1];
        while(s[i + k] == s[j + k]) k ++;
        ht[rk[i]] = k;
    } 
}

inline bool Check(int mid) {
    int i, num = 1;
    rep(i, 2, n, 1) {
        if(ht[i] < mid) num = 1;
        else num ++;
        if(num >= kn) return 1;
    }
    return 0;
}

inline void Binary() {
    int l = 1, r = n + 1, ans = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(Check(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    printf("%d\n", ans);
}

int main() {
    int i;
    n = read(); kn = read();
    rep(i, 1, n, 1) s[i] = read();
    SS();
    GH();
    Binary();
    return 0;
}
