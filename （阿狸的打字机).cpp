#include <cstdio>
#include <cstring>
#include <algorithm>
#define sid 150050
#define ri register int
using namespace std;

int m, n, len, all, root, cnt, tmp, pp, tt;
int y[sid], fa[sid], edgenum, anc[sid];
int t[sid], dfn[sid], sz[sid];
int cap[sid], node[sid], nxt[sid], tot;
int son[sid][27], fail[sid];
int ans[sid], sc[sid];
char s[sid];

struct reply {
	int x, y, id;
	friend bool operator < (reply a, reply b) {
		return a.y < b.y;
	}
} q[sid];

inline void modify(int p, int w) {
	for(int i = p; i <= cnt; i += i & (-i))
	t[i] += w;
}

inline int query(int p) {
	int tmp = 0;
	for(int i = p; i; i -= i & (-i))
	tmp += t[i];
	return tmp;
}

inline void Build_Tire() {
	int e = 0;
	for(ri i = 1; i <= n; i ++) {
		if(s[i] == 'B') e = anc[e];
		else if(s[i] == 'P') sc[++ tt] = e;
		else {
			int opt = s[i] - 'a';
			if(!son[e][opt]) {
				son[e][opt] = ++ tot;
				anc[tot] = e;
			}
			e = son[e][opt];
		}
	}
}

inline void Build_AC() {
	int e = 0;
	int fr = 1, to = 0;
	for(ri i = 0; i <= 25; i ++)
	if(son[e][i]) y[++ to] = son[e][i];
	while(fr <= to) {
		e = y[fr ++];
		for(ri i = 0; i <= 25; i ++)
		if(son[e][i]) y[++ to] = son[e][i], fail[son[e][i]] = son[fail[e]][i];
		else son[e][i] = son[fail[e]][i];
	}
}

inline void unicom(int u, int v) {
	int o = ++ edgenum;
	nxt[o] = cap[u]; cap[u] = o; node[o] = v;
}

inline void Build_fail() {
	for(ri i = 1; i <= tot; i ++)
	unicom(fail[i], i);
}

inline void dfs(int e) {
 	dfn[e] = ++ cnt;
	sz[e] ++;
	for(int i = cap[e]; i; i = nxt[i]) {
		int d = node[i];
		dfs(d);
		sz[e] += sz[d];
	}
}

inline void Solve() {
	len = 0; tot = 0;
	int e = 0; pp = 1;
	for(ri i = 1; i <= n; i ++) {
		if(s[i] == 'B') {
			modify(dfn[e], -1);
			e = anc[e];
		}
		else if(s[i] == 'P') {
			++ tmp;
			while(tmp == q[pp].y && tmp <= m) {
				int kk = sc[q[pp].x];
				ans[q[pp].id] = query(dfn[kk] + sz[kk] - 1) - query(dfn[kk] - 1);
				pp ++;
			}
		}
		else e = son[e][s[i] - 'a'], modify(dfn[e], 1);
	}
}

inline void Print_ans() {
	for(ri i = 1; i <= m; i ++) printf("%d\n", ans[i]);
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	Build_Tire();
	Build_AC();
	Build_fail();
	dfs(0);
	scanf("%d", &m);
	for(ri i = 1; i <= m; i ++) {
		scanf("%d%d", &q[i].x, &q[i].y);
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);
	Solve();
	Print_ans();
	return 0;
}
