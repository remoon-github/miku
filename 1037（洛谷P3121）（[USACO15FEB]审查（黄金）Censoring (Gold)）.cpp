#include <cstdio>
#include <cstring>
#define sid 200050
using namespace std;

char sc[sid], s[sid];
int son[sid][27], fail[sid], cnt, n;
int q[sid], endx[sid], st[sid], ac[sid], top;

inline void Trie() {
    int nl = strlen(sc + 1);
    int e = 0;
    for(int i = 1; i <= nl; i ++) {
        int opt = sc[i] - 'a' + 1;
        if(son[e][opt]) e = son[e][opt];
        else e = son[e][opt] = ++ cnt;
    }
    endx[e] = nl;
}

inline void Fail() {
    int fr = 1, to = 0;
    for(int i = 1; i <= 26; i ++) if(son[0][i]) q[++ to] = son[0][i];
    while(fr <= to) {
        int e = q[fr ++];
        for(int i = 1; i <= 26; i ++)
        if(son[e][i]) fail[son[e][i]] = son[fail[e]][i], q[++ to] = son[e][i];
        else son[e][i] = fail[son[e]][i];
    }
}

inline void Match() {
    int e = 0;
    int nl = strlen(s + 1);
    for(int i = 1; i <= nl; i ++) {
        int opt = s[i] - 'a' + 1;
        e = son[e][opt];
        st[++ top] = opt;
        if(endx[e]) top -= endx[e], e = ac[top];
        else ac[top] = e;
    }
    for(int i = 1; i <= top; i ++) printf("%c", opt + 'a' - 1);
}

int main() {
    scanf("%s", s + 1);
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%s", sc + 1);
        Trie();
    }    
    Fail();
    Match();
    return 0;
}