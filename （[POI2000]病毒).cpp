#include <cstdio>
#include <cstring>
#define sid 50050
using namespace std;

int n, tot;
int son[sid][2], fail[sid];
int q[sid * 3];
char s[sid];
bool vis[sid], endx[sid], flag;
int ok[sid];

inline void Build_Tire() {
	scanf("%s", s + 1);
	int e = 0;
	int len = strlen(s + 1);
	for(int i = 1; i <= len; i ++) {
		int opt = s[i] - '0';
		if(son[e][opt]) e = son[e][opt];
		else e = son[e][opt] = ++ tot;
	}
	endx[e] = 1;
}

inline void Build_AC() {
	int fr = 1, to = 0;
	for(int i = 0; i <= 1; i ++)
	if(son[0][i]) fail[son[0][i]] = 0, q[++ to] = son[0][i];
	while(fr <= to) {
		int e = q[fr ++];
		for(int i = 0; i <= 1; i ++)
		if(son[e][i]) fail[son[e][i]] = son[fail[e]][i], q[++ to] = son[e][i];
		else son[e][i] = son[fail[e]][i];
	}
}

inline void BFS(int e) {
	for(int i = 0; i <= 1; i ++) {
		int d = son[e][i];
		if(ok[d] == 1) continue;
		if(ok[d] != 2) {
			for(int j = d; j; j = fail[j])
			if(endx[j]) {
				ok[d] = 1;
				break;
			}
			if(ok[d] == 1) continue;
			ok[d] = 2;
		}
		if(vis[d] == 1) {
			flag = 1;
			return;
		}
		vis[d] = 1;
		BFS(d);
		if(flag) return;
		vis[d] = 0;
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
	Build_Tire();
	Build_AC();
	vis[0] = 1;
	BFS(0);
	if(flag) printf("TAK");
	else printf("NIE");
	return 0;
}
