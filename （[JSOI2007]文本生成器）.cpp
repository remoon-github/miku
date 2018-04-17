#include <cstdio>
#include <cstring>
#define sid 30050
using namespace std;

char s[sid];
int mod = 10007;
int son[sid][30], tot, cnt;
int cap[sid], nxt[sid], node[sid];
int fail[sid], q[sid];
int dp[105][sid];
int n, m;
bool mark[sid];

inline void unicom(int u, int v) {
	nxt[++ cnt] = cap[u];
	cap[u] = cnt; node[cnt] = v;
}

inline void Insert(int tim) {
	int e = 0;
	scanf("%s", s + 1);
	int l = strlen(s + 1);
	for(int i = 1; i <= l; i ++) {
		int opt = s[i] - 'A';
		if(son[e][opt]) e = son[e][opt];
		else e = son[e][opt] = ++ tot;
	}
	mark[e] = 1;
}

inline void Build_AC() {
	int fr = 1, to = 0;
	for(int i = 0; i <= 25; i ++)
	if(son[0][i]) q[++ to] = son[0][i];
	while(fr <= to) {
		int e = q[fr ++];
		for(int i = 0; i <= 25; i ++)
		if(son[e][i]) fail[son[e][i]] = son[fail[e]][i], q[++ to] = son[e][i];
		else son[e][i] = son[fail[e]][i];
	}
}

inline void Puts_Fail() {
	for(int i = 1; i <= tot; i ++)
	unicom(fail[i], i);
	int fr = 1, to = 1; q[1] = 0;
	while(fr <= to) {
		int e = q[fr ++];
		if(!mark[e] || !e)
		for(int i = cap[e]; i; i = nxt[i]) {
			int d = node[i]; q[++ to] = d;
		}
		else for(int i = cap[e]; i; i = nxt[i]) {
			int d = node[i]; mark[d] = 1;
			q[++ to] = d;
		}
	}
}

inline void AC_DP() {
	dp[0][0] = 1;
	for(int i = 0; i <= m - 1; i ++)
	for(int j = 0; j <= tot; j ++) {
		if(mark[j]) continue;
		for(int k = 0; k <= 25; k ++) {
			int d = son[j][k];
			if(mark[d]) continue;
			dp[i + 1][d] = (dp[i + 1][d] + dp[i][j]) % mod;
		}
	}
}

inline int qmod(int a, int k) {
	int tmp = 1;
	while(k) {
		if(k & 1) tmp = (tmp * a) % mod;
		a = (a * a) % mod;
		k >>= 1;
	}
	return tmp;
}

inline void Get_ans() {
	int all = qmod(26, m);
	for(int i = 0; i <= tot; i ++)
	all = (all - dp[m][i] + mod) % mod;
	printf("%d", all);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) Insert(i);
	Build_AC();
	Puts_Fail();
	AC_DP();
	Get_ans();
	return 0;
}
