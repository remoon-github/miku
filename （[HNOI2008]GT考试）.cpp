#include <cstdio>
#define sid 10050
#define ssd 40
using namespace std;

int n, m, p;
int nxt[sid];
char s[sid];

struct Remoon {
	int c[ssd][ssd];
} init, a, ans;

inline Remoon operator * (Remoon la, Remoon lb) {
	Remoon lc = init;
	for(int i = 1; i <= m; i ++)
	for(int j = 1; j <= m; j ++)
	for(int k = 1; k <= m; k ++)
	lc.c[i][j] = (lc.c[i][j] + la.c[i][k] * lb.c[k][j]) % p;
	return lc;
}
	
inline void KMP() {
	for(int i = 2, j = 0; i <= m; i ++) {
		while(j && s[j + 1] != s[i]) j = nxt[j];
		if(s[j + 1] == s[i]) j ++;
		nxt[i] = j;
	}
}

inline void Put_Fail() {
	for(int i = 1; i <= m; i ++)
	for(int j = 0; j <= 9; j ++) {
		int k = i - 1;
		while(k && s[k + 1] - '0' != j) k = nxt[k];
		if(s[k + 1] - '0' == j) k ++;
		printf("%d %d %d\n", i, j, k);
		//类比与AC自动机，这里模拟匹配
		a.c[i][k + 1] = a.c[i][k + 1] + 1;
		//推出一个点可以到哪些点
	}
}

inline void DP() {
	for(int i = 1; i <= m; i ++)
	ans.c[i][i] = 1; //单位矩阵
	while(n) {
		if(n & 1) ans = ans * a;
		a = a * a;
		n >>= 1;
	}
}

inline void Get_Ans() {
	int tmp = 0;
	for(int i = 1; i <= m; i ++)
	tmp = (tmp + ans.c[1][i]) % p;
	printf("%d\n", tmp);
}

int main() {
	scanf("%d%d%d", &n, &m, &p);
	scanf("%s", s + 1);
	KMP();
	Put_Fail();
	DP();
	Get_Ans();
	return 0;
}
