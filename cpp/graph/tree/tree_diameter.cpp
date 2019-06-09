//木の直径とその端点を返す
//O(n)
//{直径, {端点1, 端点2}}を返す
//verify:ARC022 C-ロミオとジュリエット
----------------------------------------------------------------------
// https://beta.atcoder.jp/contests/arc022/submissions/3651639

int n;
struct edge {int to, cost;};
vector<vector<edge>> g(100000 + 5);//変える!!!

pair<int, int> dfs(int now, int par, vector<vector<edge>> &g) {
  int v = now;
  int dist = 0;
  for (auto u : g[now]) {
    int nx = u.to;
    int cost = u.cost;
    if (nx == par) continue;
    pair<int, int> p = dfs(nx, now, g);
    if (dist < cost + p.se) {
      dist = cost + p.se;
      v = p.fi;
    }
  }
  return {v, dist};
}

pair<int, pair<int, int>> tree_diameter(vector<vector<edge>> &g) {
  pair<int, int> l = dfs(0, -1, g);
  pair<int, int> r = dfs(l.fi, -1, g);
  return {r.se, {l.fi, r.fi}};
}

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  rep(i, n - 1) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    g[a].push_back(edge{b, 1});
    g[b].push_back(edge{a, 1});
  }
  pair<int, pair<int, int>> ans = tree_diameter(g);
  //cout << ans.fi << endl;
  cout << ans.se.fi + 1 << " " << ans.se.se + 1 << endl;
}
