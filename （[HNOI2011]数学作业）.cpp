#include <cstdio>
#include <cmath>
#include <iostream>
#define ll long long
using namespace std;

ll n, m, p;

template <typename re>
inline re qpow(re a, ll k) {
    re tmp(1);
    while(k) {
        if(k & 1) tmp = (tmp * a);
        a = a * a; k >>= 1;
    }
    return tmp;
}

struct Martix {
    ll dp[3][3];
    Martix() {}
    Martix (int flag, int t = 0) {
        if(flag == 0) {
            for(int i = 0; i < 3; i ++)
            for(int j = 0; j < 3; j ++)
            dp[i][j] = 0;
        } 
        if(flag == 1) {
            for(int i = 0; i < 3; i ++)
            for(int j = 0; j < 3; j ++)
            dp[i][j] = (i == j) ? 1 : 0;
        }
        if(flag == 2) {
            dp[0][0] = qpow(10LL, 1ll * t) % m; dp[0][1] = 0; dp[0][2] = 0;
            dp[1][0] = 1; dp[1][1] = 1; dp[1][2] = 0;
            dp[2][0] = 1; dp[2][1] = 1; dp[2][2] = 1;
        }
    }
    ll* operator [] (const int x) {
        return dp[x];
    }
    friend Martix operator * (Martix a, Martix b) {
        Martix c(0);
        for(int i = 0; i < 3; i ++)
        for(int j = 0; j < 3; j ++)
        for(int k = 0; k < 3; k ++)
        c[i][j] = (c[i][j] + (a[i][k] % m) * (b[k][j] % m)) % m;
        return c;
    }
};

int main() {
    cin >> n >> m;
    ll op = n; 
    while(op) op /= 10, p ++;
    Martix ans(0); ans.dp[0][2] = 1;
    for(int i = 1; i < p; i ++) 
    ans = ans * qpow(Martix(2, i), qpow(10LL, i) - qpow(10LL, i - 1));
    ans = ans * qpow(Martix(2, p), n - qpow(10LL, p - 1) + 1);
    printf("%lld\n", ans[0][0]);
    return 0;
}