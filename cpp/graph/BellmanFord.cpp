//Bellman-Ford法
//O[n * m](n:頂点数, m:辺数)

//shortpathはsから各頂点への最短経路(d)を求め、負閉路の検出も行う。
//shortpathは負閉路を含むならtrue, そうでないときfalse
//esにすべての情報を突っ込んでいくので少し他のグラフの表現と異なる。

//find_negative_loopは最短経路上のパスに負閉路が含まれるような頂点集合をもとめる。
//negative[i] = true -> 頂点iへの最短経路パスに負閉路が含まれる。

struct edge {int from, to, cost;};
vector<edge> es;
ll d[1005];                     //最短経路距離
int n, m;

bool shortpath(int s, int n) {
    for (int i = 0; i < n; i++) {
        d[i] = INFLL;
    }
    d[s] = 0;
    int cnt = 0;
    while (true) {
        bool update = false;
        for (auto e : es) {
            if (d[e.from] != INFLL && d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                update = true;
            }
        }
        if (!update) break;
        cnt++;
        if (cnt == n) break;
    }
    if (cnt == n) return true;
    else return false;
}

vector<bool> find_negative_loop(int s, int n) {
    vector<bool> negative(n);
    for (int i = 0; i < n; i++) {
        for (auto e : es) {
            if (d[e.from] != INFLL && d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                negative[e.to] = true;
            }
            //if (negative[e.from]) negative[e.to] = true;
        }
    }
    return negative;
}

int main() {
    cin > n >> m;
    rep(i, m) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        es.push({u, v, c});
    }
}