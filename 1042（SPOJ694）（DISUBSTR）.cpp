#include <cstdio>
#include <iostream>
#include <cstring>
#define sid 5050
#define ll long long
using namespace std;

ll ans;
char s[sid];
int n;
int p1[sid], p2[sid], cnt[sid];
int sa[sid], rk[sid], ht[sid];

inline void Init() {
    memset(cnt, 0, sizeof(cnt));
    memset(p1, 0, sizeof(p1));
    memset(p2, 0, sizeof(p2));
    memset(sa, 0, sizeof(sa));
    memset(rk, 0, sizeof(rk));
    memset(ht, 0, sizeof(ht));
}

inline void SS() {
    int *t1 = p1, *t2 = p2;
    int m = 130;
    for(int i = 1; i <= n; i ++) cnt[t1[i] = s[i]] ++;
    for(int i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
    for(int i = n; i >= 1; i --) sa[cnt[t1[i]] --] = i;
    for(int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for(int i = 0; i <= m; i ++) t2[i] = 0;
        for(int i = n - k + 1; i <= n; i ++) t2[++ p] = i;
        for(int i = 1; i <= n; i ++) if(sa[i] > k) t2[++ p] = sa[i] - k;
        for(int i = 0; i <= m; i ++) cnt[i] = 0;
        for(int i = 1; i <= n; i ++) cnt[t1[t2[i]]] ++;
        for(int i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
        for(int i = n; i >= 1; i --) sa[cnt[t1[t2[i]]] --] = t2[i];
        swap(t1, t2); t1[sa[1]] = p = 1;
        for(int i = 2; i <= n; i ++)
        t1[sa[i]] = (t2[sa[i - 1]] == t2[sa[i]] && t2[sa[i - 1] + k] == t2[sa[i] + k]) ?  p : ++ p;
        if(p >= n) break; m = p;
    }
}

inline void GH() {
    for(int i = 1; i <= n; i ++) rk[sa[i]] = i;
    int p = 0, j;
    for(int i = 1; i <= n; i ++) {
        if(p) p --;
        j = sa[rk[i] - 1];
        while(s[i + p] == s[j + p]) p ++;
        ht[rk[i]] = p;
    }
}

int main() {
    int Tt;
    scanf("%d", &Tt);
    while(Tt --) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        Init();
        SS();
        GH();
        ans = n * (n + 1) / 2;
        for(int i = 1; i <= n; i ++) ans -= ht[i];
        printf("%lld\n", ans);
    }
    return 0;
}