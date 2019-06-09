//O[n + m]
//強連結成分:頂点u, vにおいてu->v, v->uのpathが存在するような最大頂点集合(部分グラフ)
//SCC後はDAGとなる
/*
n, m:頂点数、辺数
g, rg:与えられる有向辺、逆辺
vs:帰りがけ順での頂点番号を記録
cmp[i]:i番目(0-indexed)の頂点の属する強連結成分の番号(0-indexed) 
*/


int n, m;
vector<vector<int>> g(1000000 + 6), rg(1000000 + 6);
vector<int> vs;
bool visited[1000000 + 6];
int cmp[1000000 + 6];

void add_edge(int from , int to) {
    g[from].push_back(to);
    rg[to].push_back(from);
}

void dfs(int now) {
    visited[now] = true;
    for (auto nx : g[now]) {
        if (!visited[nx]) {
            dfs(nx);
        }
    }
    vs.push_back(now);
    return; 
}

void rdfs(int now, int cnt) {
    visited[now] = true;
    cmp[now] = cnt;
    for (auto nx : rg[now]) {
        if (!visited[nx]) {
            rdfs(nx, cnt);
        }
    }
    return;
}

int SCC(int n) {
    fill(visited, visited + n, false);
    vs.clear();
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    fill(visited, visited + n, false);
    int cnt = 0;
    vector<int> comp(n, -1);
    for (int i = vs.size() - 1; i >= 0; i--) {
        if (!visited[vs[i]]) {
            rdfs(vs[i], cnt++);
        }
    }
    return cnt;
}

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    rep(i, m) {
        int s, t;
        cin >> s >> t;
        add_edge(s, t);
    }

    int cnt = scc(n);

    int q;
    cin >> q;
    rep(i, q) {
        int u, v;
        cin >> u >> v;
        cout << (cmp[u] == cmp[v] ? '1' : '0') << endl; 
    }
}