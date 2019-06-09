//costがlong long型のdijkstra
//コメント部分は経路復元
//O[ElogV](E:辺数, V:頂点数)

int n, m;
struct edge{int to, cost;};
vector<vector<edge>> g(100000 + 5);

vector<ll> dijkstra(int s, int n, vector<vector<edge>>& g){
    priority_queue<plli, vector<plli>, greater<plli>> pque;
    vector<ll> d(n, INFLL);
    d[s] = 0;
    pque.push(plli(0, s));

    while (!pque.empty()){
        plli p = pque.top(); pque.pop();
        int fr = p.second;
        if (d[fr] < p.first) continue;
        for (edge e: g[fr]){
            if (d[e.to] > d[fr] + e.cost){
                d[e.to] = d[fr] + e.cost;
                pque.push(plli(d[e.to], e.to));
            }
        }
    }
    return d;
}

---------------------------------------------------------------------------------
//頂点Sから各点iへの最短経路の本数もdijkstra中に数え上げる
//dp[i] := Sからiへの最短経路の数
//距離の短いものから更新(足し合わせ)していく
//(真に短い経路が見つかったらリセットするので注意)

vector<ll> dijkstra(int s, int n, vector<vector<edge>>& g, vector<int>& dp){
    priority_queue<plli, vector<plli>, greater<plli>> pque;
    vector<ll> d(n, INFLL);
    d[s] = 0;
    dp[s] = 1;
    pque.push(plli(0, s));

    while (!pque.empty()){
        plli p = pque.top(); pque.pop();
        int fr = p.second;
        if (d[fr] < p.first) continue;
        for (edge e: g[fr]){
            if (d[e.to] > d[fr] + e.cost){
                d[e.to] = d[fr] + e.cost;
                dp[e.to] = dp[fr];//(リセット)
                pque.push(plli(d[e.to], e.to));
            }
            else if (d[e.to] == d[fr] + e.cost) {
              dp[e.to] += dp[fr];
            }
        }
    }
    return d;
}


------------------------------------------------------------------------
//二次元拡張dijkstra
//d[pre][now] := pre -> now の距離(cost)
//O[E*VlogV](E:元のグラフでの辺数, V:元のグラフでの頂点数)


vector<vector<ll>> dijkstra(int s, int n, vector<vector<edge>>& g){
    priority_queue<plpll, vector<plpll>, greater<plpll>> que;
    vector<vector<ll>> d(n, vector<ll> (n, INFLL)); d[s][s] = 0;
    que.push({0, {s, s}});

    while (!que.empty()){
        plpll p = que.top(); que.pop();
        int pre = p.se.fi;
        int now = p.se.se;
        if (d[pre][now] < p.fi) continue;
        for (edge e: g[now]){
            if (d[now][e.to] > d[pre][now] + e.cost) {
                d[now][e.to] = d[pre][now] + e.cost;
                que.push({d[now][e.to], {now, e.to}});
            }
        }
    }
    return d;
}

//最短距離の求め方が1次元だとdist[n - 1]のようにしてかけたが拡張dijkstraでのdistは
//ちょっと求め方が異なるので注意
/*もし始点が0で終点が n - 1であったら
0 -> nまでの最短経路は以下のansとなる。

    vector<vector<long long>> dist = dijkstra(0, n, g)
    long long ans = LLONG_MAX / 10;
    rep(i, n) {
        if (i == n - 1) contiue;
        ans = min(ans, dist[i][n - 1]);
    }
    cout << ans << endl;
*/

--------------------------------------------------------------------
//経路復元ver
int n, m;
struct edge{int to, cost;};
vector<vector<edge>> g(100000 + 5);
vector<ll> pv(100000 + 5, -1);

vector<ll> dijkstra(int s, int n, vector<vector<edge>>& g){
    priority_queue<plli, vector<plli>, greater<plli>> que;
    vector<ll> d(n, INFLL); d[s] = 0;
    que.push(plli(0, s));

    while (!que.empty()){
        plli p = que.top();que.pop();
        int fr = p.second;
        if (d[fr] < p.first) continue;
        for (edge e: g[fr]){
            if (d[e.to] > d[fr] + e.cost){
                d[e.to] = d[fr] + e.cost;
                pv[e.to] = fr;
                que.push(plli(d[e.to], e.to));
            }
        }
    }
    return d;
}
//頂点tまでの最短経路path
//O[V]

vector<ll> get_path(ll t){
    vector<ll> path;
    for(; t! = -1; t = pv[t]) path.push_back(t);
    reverse(path.begin(),path.end());
    return path;
}

-------------------------------------------------------------------
//costがdouble型のdijkstra
struct edge{int to; double cost;}; // <------------!! 問題に合わせて変える
vector<vector<edge>> g(100000+5); // <------------!! 問題に合わせて変える

vector<double> dijkstra(int s, int n, vector<vector<edge>>& g){
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> que;
    vector<double> d(n, INFLL); d[s] = 0.0;
    que.push(plli(0.0, s));

    while (!que.empty()){
        plli p = que.top();que.pop();
        int fr = p.second;
        if (d[fr] < p.first) continue;
        for (edge e: g[fr]){
            if (d[e.to] > d[fr] + e.cost){
                d[e.to] = d[fr] + e.cost;
                que.push(make_pair(d[e.to], e.to));
            }
        }
    }
    return d;
}
---------------------------------------------------------------------

int V,E,r;
struct edge{ int to, cost; };
vector<edge> g[100000+5];
int d[100000+5];

void dijkstra(int s){
    priority_queue<pii, vector<pii>, greater<pii>> que;
    fill(d, d+V, INF);
    d[s] = 0;
    que.push(pii(0, s));

    while (!que.empty()){
        pii p = que.top();que.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (int i = 0; i < g[v].size(); i++){
            edge e = g[v][i];
            if (d[e.to] > d[v] + e.cost){
                d[e.to] = d[v] + e.cost;
                que.push(pii(d[e.to], e.to));
            }
        }
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> V >> E >> r;
    rep(i,E){
        int s,t,d;
        cin >> s >> t >> d;
        g[s].pb(edge{t,d});
    }
    dijkstra(r);
    rep(i,V){
        if(d[i]==INFLL) cout << "INF" << endl;
        else cout << d[i] << endl;
    }
    return 0;
}
