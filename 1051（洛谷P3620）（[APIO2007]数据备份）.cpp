#include <cstdio>
#define sid 300050
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

struct Data() {
    int v, id;
    Data() {}
    Data(int _id, int _v) { v = _v; id = _id; }
    friend bool operator < (Data a, Data b) {
        return a.v > b.v;
    }
};

int a[sid], val[sid], n, k, ans;
int pre[sid], nxt[sid];
bool cho[sid];
priority_queue <Data, vector <Data> > q;

int main() {
    fread(RR, 1, sizeof(RR), stdin);
    n = read(); k = read();
    for(ri i = 1; i <= n; i ++) a[i] = read();
    for(ri i = 1; i < n; i ++) {
        val[i] = a[i + 1] - a[i];
        pre[i] = i - 1; nxt[i] = i + 1;
        q.push(Data(i, val[i]));
    }
    val[0] = val[n] = 1047483647;
    for(ri i = 1; i <= k; i ++) {
        while(1) {
            Data tmp = q.top(); q.pop();
            int id = tmp.id;
            if(!cho[id]) break;
        }
        ans += val[id];
        int pr = pre[id], nx = nxt[id];
        val[id] = val[pr] + val[nx] - val[id];
        cho[pr] = cho[nx] = 1;
        nxt[pre[pr]] = nxt[pr]; pre[nxt[pr]] = pre[pr];
        nxt[pre[nx]] = nxt[nx]; pre[nxt[nx]] = pre[nx];
        pre[pr] = nxt[pr] = pre[nx] = nxt[nx] = 0;
        q.push(Data(id, val[id]));
    }
    printf("%d\n", ans);
    return 0;
}