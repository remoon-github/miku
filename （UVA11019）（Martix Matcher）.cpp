#include <cstdio>
#include <cstring>
#define sid 1050
#define ssd 10005
#define ri register int
using namespace std;

char s[sid], t[sid][sid];
int n, m, x, y;
int son[ssd][28], fail[ssd], q[ssd];
int next[sid], cnt[sid][sid], row[sid], ans, tot; 

inline void Init() {
    memset(son[0], 0, sizeof(son[0]));
    memset(cnt, 0, sizeof(cnt));
    memset(next, 0, sizeof(next));
    memset(fail, 0, sizeof(fail));
    tot = 0; row[0] = -1; ans = 0;
}

inline void Trie(int row_num) {
    int e = 0;
    scanf("%s", s);
    for(ri i = 0; i < y; i ++) {
        int opt = s[i] - 'a' + 1;
        if(son[e][opt]) e = son[e][opt];
        else {
            ++ tot;
            memset(son[tot], 0, sizeof(son[tot]));
            row[tot] = -1; e = son[e][opt] = tot;
        }
    }
    next[row_num] = row[e]; row[e] = row_num;
}

inline void Fail() {
    int fr = 1, to = 0;
    for(ri i = 1; i <= 26; i ++) 
    if(son[0][i]) q[++ to] = son[0][i];
    while(fr <= to) {
        int e = q[fr ++];
        for(ri i = 1; i <= 26; i ++)
        if(son[e][i]) q[++ to] = son[e][i], fail[son[e][i]] = son[fail[e]][i];
        else son[e][i] = son[fail[e]][i];
    }
}

inline void Match(int j) {
    int e = 0;
    for(ri i = 0; i < m; i ++) {
        int opt = t[j][i] - 'a' + 1;
        e = son[e][opt];
        if(row[e] != -1)
        for(int k = row[e]; ~k; k = next[k])
        if(j >= k) cnt[j - k][i - y + 1] ++;
    }
}

int main() {
    int Tt;
    scanf("%d", &Tt);
    while(Tt --) {
        Init();
        scanf("%d%d", &n, &m);
        for(ri i = 0; i < n; i ++) scanf("%s", t[i]);
        scanf("%d%d", &x, &y);
        for(ri i = 0; i < x; i ++) Trie(i);
        Fail();
        for(ri i = 0; i < n; i ++) Match(i);
        for(ri i = 0; i < n; i ++)
        for(ri j = 0; j < m; j ++)
        if(cnt[i][j] == x) ans ++;
        printf("%d\n", ans);
    }
    return 0;
}
