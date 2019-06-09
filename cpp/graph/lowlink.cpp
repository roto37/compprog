//O[n + m]
//関節点(Points)と橋(Bridges)をvectorで求める(昇順sortしている), Bridgesは頂点のpairで管理
//関節点:ある点とそこから出ている辺を削除したとき連結成分が増えるような点
//橋:ある辺を削除したとき連結成分が増えるような辺

/*
verify
Briges : http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=2594184#1
Articulation Points : http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=2594186#1
*/

int n, m;
vector<vector<int>> g(100000 + 6);

int ord[1000000 + 6], low[1000000 + 6];
bool visited[1000000 + 6];

vector<pair<int, int>> Bridges;
vector<int> Points;

void dfs(int now, int par, int &cnt) {
    visited[now] = true;
    ord[now] = cnt++;
    low[now] = ord[now];
    bool check = false;
    int outdeg = 0;
    for (auto nx : g[now]) {
        if (nx == par) continue;
        if (!visited[nx]) {
            outdeg++;
            dfs(nx, now, cnt);
            low[now] = min(low[now], low[nx]);
            //橋かどうか
            if (ord[now] < low[nx]) {
                Bridges.push_back({min(now, nx), max(now, nx)});
            }
            //関節点かどうか
            if (par != -1 && !check && ord[now] <= low[nx]) {
                check = true;
                Points.push_back(now);
            }
        }
        else {
            low[now] = min(low[now], ord[nx]);
        }
    }
    //根については特別に関節点となるか判定
    if (par == -1 && outdeg >= 2) {
        Points.push_back(now);
    }
    return;
}

void lowlink (int n, vector<vector<int>>& g) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, -1, cnt);
        }
    }
    sort(all(Bridges));
    sort(all(Points));
    return;
}

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    lowlink(n, g);
    /*
    rep(i, Bridges.size()) {
        cout << Bridges[i].fi << " " << Bridges[i].se << endl;
    }
    */
    /*
    rep(i, Points.size()) {
        cout << Points[i] << endl;
    }
    */
}