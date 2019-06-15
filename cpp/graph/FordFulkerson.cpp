//最大流
//O[FE]
//used, Gを引数にとるver
//used, Gはグラフに現れる頂点の最大数確保する

struct edge {
    int to, cap, rev;
    edge (int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};


void add_edge(int from, int to, int cap, vector<vector<edge>>& G) {
    G[from].emplace_back(to, cap, G[to].size());
    G[to].emplace_back(from, 0, G[from].size() - 1);
}

int dfs(int v, int t, int f, vector<bool>& used, vector<vector<edge>>& G) {
    if (v == t) return f;
    used[v] = true;
    for (auto &e : G[v]) {
        if (!used[e.to] && e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap), used, G);
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t, vector<bool>& used, vector<vector<edge>>& G) {
    int flow = 0;
    for(;;) {
        fill(used.begin(), used.end(), false);
        int f = dfs(s, t, INT_MAX, used, G);
        if (f == 0) return flow;
        flow += f;
    }
    return flow;
}
