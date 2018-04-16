

inline void Build(int n) {
    M = 1;
    while(M <= n) M <<= 1;
    M --; t[0] = INF; 
}

inline void Modify(int p, int w) {
    for(int i = p + M; dis[t[i]] > w; i >>= 1) t[i] = p;
    dis[p] = w;
}

inline void Delete(int p) {
    t[p += M] = 0; 
    p >>= 1;
    while(p) {
        if(dis[t[p << 1]] < dis[t[p << 1 | 1]]) t[p] = t[p << 1];
        else t[p] = t[p << 1 | 1];
        p >>= 1;
    }
}

inline void Dijkstra() {
    memset(dis, 56, sizeof(dis));
    Modify(s, 0);
    for(int i = 1; i <= n; i ++) {
        int e = t[1];
        Delete(e);
        for(int i = cap[e]; i; i = nxt[i]) {
            int d = node[i];
            if(dis[d] > dis[e] + w[i])
            Modify(d, dis[e] + w[i]);
        }
    }
}