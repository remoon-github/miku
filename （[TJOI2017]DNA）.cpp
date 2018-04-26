#include <cstdio>
#include <iostream>
#include <cstring>
#define ri register int
#define sid 200050
using namespace std;

char s[sid];
int n, sn;
int cnt[sid], sa[sid], p1[sid], p2[sid];
int rk[sid], st[sid][20], lg[sid], bit[50]; 

inline void Suffix(int n) {
    int m = 128;
    int *t1 = p1, *t2 = p2;
    for(ri i = 0; i <= m; i ++) cnt[i] = 0;
    for(ri i = 1; i <= n; i ++) cnt[t1[i] = s[i]] ++;
    for(ri i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
    for(ri i = n; i >= 1; i --) sa[cnt[t1[i]] --] = i;
    for(ri k = 1; k <= n; k <<= 1) {
        int p = 0;
        for(ri i = 0; i <= m; i ++) t2[i] = 0;
        for(ri i = n - k + 1; i <= n; i ++) t2[++ p] = i;
        for(ri i = 1; i <= n; i ++) if(sa[i] > k) t2[++ p] = sa[i] - k;
        for(ri i = 0; i <= m; i ++) cnt[i] = 0;
        for(ri i = 1; i <= n; i ++) cnt[t1[t2[i]]] ++;
        for(ri i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
        for(ri i = n; i >= 1; i --) sa[cnt[t1[t2[i]]] --] = t2[i];
        swap(t1, t2); t1[sa[1]] = p = 1;
        for(ri i = 2; i <= n; i ++) t1[sa[i]] = (t2[sa[i - 1]] == t2[sa[i]] && t2[sa[i - 1] + k] == t2[sa[i] + k]) ? p : ++ p;
        if(p >= n) break; m = p; 
    }
    for(ri i = 1; i <= n; i ++) rk[sa[i]] = i;
    ri k = 0;
    for(ri i = 1; i <= n; i ++) {
        if(k) k --;
        int j = sa[rk[i] - 1];
        while(s[i + k] == s[j + k]) k ++;
        st[rk[i]][0] = k;
    }
}
inline void Pre_ST(int n) {
    for(ri j = 1; j <= 17; j ++)
    for(ri i = 1; i <= n; i ++)
    st[i][j] = min(st[i][j - 1], st[i + bit[j - 1]][j - 1]);
}

inline int lcp(int i, int j) {
    int a = rk[i], b = rk[j];
    if(a > b) swap(a, b); a ++;
    int p = lg[b - a + 1];
    return min(st[a][p], st[b - bit[p] + 1][p]);
}

int main() {
    int Tt;
    for(ri i = 2; i <= 200000; i ++) lg[i] = lg[i >> 1] + 1;
    for(ri i = 0; i <= 30; i ++) bit[i] = 1 << i;
    scanf("%d", &Tt);
    int ans, an;
    while(Tt --) {
        ans = 0;
        scanf("%s", s + 1); n = strlen(s + 1);
        s[n + 1] = '&';
        scanf("%s", s + n + 2); sn = strlen(s + n + 2);
        an = n + sn + 1;
        Suffix(an); Pre_ST(an);
        int lim = n - sn + 1;
        for(ri i = 1; i <= lim; i ++) {
            int tim = 0;
            for(ri j = 1; j <= sn && tim <= 3; )
            if(s[i + j - 1] != s[n + j + 1]) tim ++, j ++;
            else j += lcp(i + j - 1, n + j + 1);
            if(tim <= 3) ans ++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
