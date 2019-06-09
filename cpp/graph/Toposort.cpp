//辞書順最小(数字の小さい順)(大きい順は下)
//hpは空のリスト[]で初期化
//nはノード数
//計算量はかかってもO[nlogn](おそらくもっと小さい)
//順序性が必要なければO[n](priority_queue -> queue)でできる

vector<int> TopoSort(int n, vector<vector<int>>& g) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) pq.push(i);
    vector<int> ret;
    while (!pq.empty()) {
        int now = pq.top(); pq.pop();
        for (auto nx: g[now]) {
            indeg[nx]--;
            if (indeg[nx] == 0) pq.push(nx);
        }
        ret.push_back(now);
    }
    return ret;
}
--------------------------------------------------------------------
//大きい順
vector<int> TopoSort(int n, vector<vector<int>>& g) {
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) pq.push(i);
    vector<int> ret;
    while (!pq.empty()) {
        int now = pq.top(); pq.pop();
        for (auto nx: g[now]) {
            indeg[nx]--;
            if (indeg[nx] == 0) pq.push(nx);
        }
        ret.push_back(now);
    }
    return ret;
}
