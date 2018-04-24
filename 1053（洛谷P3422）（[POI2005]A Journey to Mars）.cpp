// luogu-judger-enable-o2
#include <cstdio>
#include <bitset>
#include <iostream>
#define sid 2005000
#define ll long long
#define ri register int
using namespace std;

#define getchar() *S ++
char RR[50000005], *S = RR;
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

bitset <sid> flag;
int n;
int d[sid], p[sid], q[sid];
ll res[sid];

inline void Solve(int mk) {
    int n2 = n << 1;
    for(ri i = 1; i <= n2; i ++)
    res[i] = res[i - 1] + p[i - 1] - d[i + mk - 1];
    int fr = 1, to = 0;
    for(ri i = 2; i <= n + 1; i ++) {
        while(fr <= to && res[q[to]] >= res[i]) to --;
        q[++ to] = i;
    }
    for(ri i = 1; i <= n; i ++) {
        while(fr <= to && q[fr] <= i) fr ++;
        if(res[q[fr]] >= res[i]) flag[(mk) ? n - i + 1:  i] = 1;
        while(fr <= to && res[q[to]] >= res[i + n + 1]) to --;
        q[++ to] = i + n + 1;
    }
}

int main() {
    fread(RR, 1, sizeof(RR), stdin);
    n = read();
    for(ri i = 1; i <= n; i ++) {
        p[i + n] = p[i] = read(); 
        d[i + n] = d[i] = read();
    }
    Solve(0);
    for(ri i = 1; i <= n; i ++) {
        swap(p[i], p[(n << 1) - i + 1]);
        swap(d[i], d[(n << 1) - i + 1]);
    }
    Solve(1);
    for(ri i = 1; i <= n; i ++)
    if(flag[i]) puts("TAK");
    else puts("NIE");
    return 0;
}