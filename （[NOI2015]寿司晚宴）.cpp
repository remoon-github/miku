#include <cstdio>
#define sid 260
#define ll long long
using namespace std;

int n, pr[20] = { 0, 2, 3, 5, 7, 11, 13, 17, 19 };
int deal[505], bit[sid];
int sta[505], maxp[505], go[sid][sid], tot[sid];
ll mod, ans, dp[sid][sid], f[2][sid][sid];

inline void up(ll &a, ll b) {
    a += b; if(a > mod) a -= mod;
}

inline void Pre() {
    for(int i = 0; i <= 30; i ++) bit[i] = 1 << i;
    for(int i = 2; i <= n; i ++) {
        int tmp = i;
        for(int j = 1; j <= 8; j ++) {
            if(x % pr[j] != 0) continue;
            sta[i] |= bit[j - 1];
            while(x % pr[j] == 0) x /= pr[j];
        }
        maxp[i] = tmp;
    }
    for(int i = bit[8] - 1; i >= 0; i --)
    for(int j = bit[8] - 1; j >= 0; j --)
    if((i & j) == 0) go[i][++ tot[i]] = j;
}

inline void DP() {
    dp[0][0] = 1;
    for(int i = 2; i <= n; i ++) 
    for(int j = bit[8] - 1; j >= 0; j --)
    for(int k = 1; k <= tot[j]; k ++) {
        int d = go[j][k];
        if(!(sta[i] & d)) up(dp[sta[i] | j][d], dp[j][d]);
        if(!(sta[i] & j)) up(dp[j][sta[i] | d], dp[j][d]);  
    }
    deal[1] = 1;
    for(int i = 2; i <= n; i ++)
    if(!deal[maxp[i]]) {
        memcpy(f[0], dp, sizeof(dp));
        memcpy(f[1], dp, sizeof(dp));
        for(int j = i; j <= n; j += i) {
            for(int l = bit[8] - 1; l >= 0; l --)
            for(int r = 1; r <= tot[l]; r ++) {
                int d = go[l][r];
                if(!(sta[j] & d)) up(dp[sta[j] | l][d], dp[l][d]);
                if(!(sta[j] & l)) up(dp[l][sta[j] | d], dp[l][d]); 
            }
        }
        for(int l = bit[8] - 1; l >= 0; l --)
        for(int r = 1; r <= tot[l]; r ++) {
            int d = go[l][r];
            dp[l][d] = f[0][l][d] + f[1][l][d] - dp[l][d];
        }
        deal[maxp[i]] = 1;
    }
    for(int i = bit[8] - 1; i >= 0; i --)
    for(int j = 1; j <= tot[i]; j ++)
    up(ans, dp[i][go[i][j]]);
    printf("%lld\n", ans);
}

int main() {
    scanf("%d%d", &n, &mod);
    Pre();
    DP();
    return 0;
}
