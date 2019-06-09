//O[E * V^2]
//MAX_Vは制約によって変える!!
const int MAX_V = 105;

struct edge {
    int to, cap, rev;
    edge(int to, int cap, int rev) :to(to), cap(cap), rev(rev) {}
};

vector<vector<edge>> g(MAX_V);
int level[MAX_V];
int iter[MAX_V];

void add_edge(int from, int to, int cap) {
    g[from].emplace_back(to, cap, g[to].size());
    g[to].emplace_back(from, 0, g[from].size() - 1);
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int now = q.front(); q.pop();
        for (auto e : g[now]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[now] + 1;
                q.push(e.to);
            }
        }
    }
}

int dfs(int now, int t, int f) {
    if (now == t) return f;
    for (int &i = iter[now]; i < g[now].size(); i++) {
        edge &e = g[now][i];
        if (e.cap > 0 && level[now] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0) flow += f;
    }
}

int n, m;

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    rep(i, m) {
        int u, v, c;
        cin >> u >> v >> c;
        add_edge(u, v, c); 
    }
    int s = 0;
    int t = n - 1;
    cout << max_flow(s, t) << endl;
}