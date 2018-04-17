#include <queue>
#include <cstdio>
#include <cstring>
#define ssd (100050)
#define sid (1000500)
using namespace std;

int cnt, ioi, poi, n;
int endx[ssd], sta[ssd], p[ssd];
int son[ssd][28], fail[ssd], pre[sid];
char let[sid], s[ssd], sc[ssd];
bool vis[605][(1 << 12) + 100];
struct P {
    int ac, sta;
    P() {}
    P(int _a, int _s) { ac = _a; sta = _s; }
};
queue <P> q;

inline void Insert() {
    int e = 0;
    scanf("%s", s + 1);
    int nl = strlen(s + 1);
    for(int i = 1; i <= nl; i ++) {
        int opt = s[i] - 'A' + 1;
        if(son[e][opt]) e = son[e][opt];
        else e = son[e][opt] = ++ cnt;
    }
    endx[e] |= (1 << (++ poi - 1));
}

inline void AC() {
    int fr = 1, to = 0;
    for(int i = 1; i <= 26; i ++) if(son[0][i]) p[++ to] = son[0][i];
    while(fr <= to) {
        int e = p[fr ++];
        for(int i = 1; i <= 26; i ++)
        if(son[e][i]) fail[son[e][i]] = son[fail[e]][i], p[++ to] = son[e][i];
        else son[e][i] = son[fail[e]][i];
    }
}

inline void Fail() {
    for(int i = 1; i <= cnt; i ++)
    for(int j = i; j; j = fail[j]) if(endx[j]) sta[i] |= endx[j];
}

inline void Bfs() {
    int fr = 0, to = 0;
    q.push(P(0, 0));
    pre[0] = 0; let[0] = 0;
    vis[0][0] = 1;
    while(fr <= to) {
        P tmp = q.front();
        int e = tmp.ac, s = tmp.sta;
        for(int i = 1; i <= 26; i ++)
        if(son[e][i]) {
            int d = son[e][i];
            int pd = s | sta[d]; P ret(d, pd);
            if(vis[d][pd] == 1) continue;
            pre[++ to] = fr; let[to] = i + 'A' - 1; vis[d][pd] = 1;
            if((pd & ((1 << n) - 1)) == ((1 << n) - 1)) {
                for(int i = to; i; i = pre[i]) sc[++ ioi] = let[i];
                return;
            }
            q.push(ret);
        }
        q.pop(); fr ++;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) Insert();
    AC(); Fail(); Bfs();
    for(int i = ioi; i; i --) printf("%c", sc[i]);
    return 0;
}