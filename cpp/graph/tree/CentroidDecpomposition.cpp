//木の重心分解
//search(重心探すpart)だけ再帰
//CF321 Ciel the Commanderで最速

vector<char> ans(100000 + 5);


struct TCD {
  int ret;//ans
  vector<vector<int>> g;
  int n;//g.size()
  int centroid;
  vector<bool> dead;
  vector<int> par, sub;

  TCD(int n)
  : n(n),
    g(n),
    ret(0),
    par(n),
    centroid(-1),
    dead(n),
    sub(n)
    {}

  void add_edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
  }

  void calc_sub(int r) {
    stack<pii> st;
    par[r] = -1;
    st.emplace(r, 0);
    while (!st.empty()) {
      int now = st.top().first;
      int &i = st.top().second;
      if (i < g[now].size()) {
        int nx = g[now][i++];
        if (nx == par[now] || dead[nx]) continue;
        par[nx] = now;
        st.emplace(nx, 0);
      }
      else {
        st.pop();
        sub[now] = 1;
        for (auto nx : g[now]) {
          if (nx == par[now] || dead[nx]) continue;
          sub[now] += sub[nx];
        }
      }
    }
  }

  int search(int now, int par, int m) {
    for (auto nx : g[now]) {
      if (nx == par || dead[nx]) continue;
      if (sub[nx] > m / 2) {
        return search(nx, now, m);
      }
    }
    return centroid = now;
  }

  void get_centroid(int root) {
    calc_sub(root);
    int m = sub[root];
    search(root, -1, m);
  }

  void via_centroid(int depth) {
    ans[centroid] = 'A' + depth;
  }

  int divide_conquer(int root, int depth) {
    get_centroid(root);
    dead[centroid] = true;
    //重心を経由(重心が端点も含む)して複数の部分木同士の計算
    via_centroid(depth);
    //個別の部分木に対してそれぞれ計算(より小さいサイズで同じ計算)
    for (auto nx : g[centroid]) {
      if (dead[nx]) continue;
      divide_conquer(nx, depth + 1);
    }

    dead[centroid] = false;
    return ret;
  }
};


signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  TCD tr(n);
  rep(i, n - 1) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    tr.add_edge(a, b);
  }
  tr.divide_conquer(0, 0);
  rep(i, n) cout << ans[i] << " ";
  cout << endl;
}


-----------------------------------------------------------------------
//非再帰ver
vector<char> ans(100000 + 5);


struct TCD {
  int ret;//ans
  vector<vector<int>> g;
  int n;//g.size()
  int centroid;
  vector<bool> dead;
  vector<int> par, sub;

  TCD(int n)
  : n(n),
    g(n),
    ret(0),
    par(n),
    centroid(-1),
    dead(n),
    sub(n)
    {}

  void add_edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
  }

  void calc_sub(int r) {
    stack<pii> st;
    par[r] = -1;
    st.emplace(r, 0);
    while (!st.empty()) {
      int now = st.top().first;
      int &i = st.top().second;
      if (i < g[now].size()) {
        int nx = g[now][i++];
        if (nx == par[now] || dead[nx]) continue;
        par[nx] = now;
        st.emplace(nx, 0);
      }
      else {
        st.pop();
        sub[now] = 1;
        for (auto nx : g[now]) {
          if (nx == par[now] || dead[nx]) continue;
          sub[now] += sub[nx];
        }
      }
    }
  }

  void search(int r, int m) {
    int now = r;
    while (true) {
      bool is_centroid = true;
      for (auto nx : g[now]) {
        if (nx == par[now] || dead[nx]) continue;
        if (sub[nx] > m / 2) {
          now = nx;
          is_centroid = false;
          break;
        }
      }
      if (is_centroid) {
        centroid = now;
        return;
      }
    }
  }

  void get_centroid(int root) {
    calc_sub(root);
    int m = sub[root];
    search(root, m);
  }

  void via_centroid(int depth) {
    ans[centroid] = 'A' + depth;
  }

  int divide_conquer(int root, int depth) {
    get_centroid(root);
    dead[centroid] = true;
    //重心を経由(重心が端点も含む)して複数の部分木同士の計算
    via_centroid(depth);
    //個別の部分木に対してそれぞれ計算(より小さいサイズで同じ計算)
    for (auto nx : g[centroid]) {
      if (dead[nx]) continue;
      divide_conquer(nx, depth + 1);
    }

    dead[centroid] = false;
    return ret;
  }
};


signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  TCD tr(n);
  rep(i, n - 1) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    tr.add_edge(a, b);
  }
  tr.divide_conquer(0, 0);
  rep(i, n) cout << ans[i] << " ";
  cout << endl;
}

--------------------------------------------------
CSA Path Inversion

int n, k;
vector<int> cnt(100000 + 5);


struct TCD {
  int ret;//ans
  vector<vector<int>> g;
  int n;//g.size()
  int centroid;
  vector<bool> dead;
  vector<int> par, sub;

  TCD(int n)
  : n(n),
    g(n),
    ret(0),
    par(n),
    centroid(-1),
    dead(n),
    sub(n)
    {}

  void add_edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
  }

  void calc_sub(int r) {
    stack<pii> st;
    par[r] = -1;
    st.emplace(r, 0);
    while (!st.empty()) {
      int now = st.top().first;
      int &i = st.top().second;
      if (i < g[now].size()) {
        int nx = g[now][i++];
        if (nx == par[now] || dead[nx]) continue;
        par[nx] = now;
        st.emplace(nx, 0);
      }
      else {
        st.pop();
        sub[now] = 1;
        for (auto nx : g[now]) {
          if (nx == par[now] || dead[nx]) continue;
          sub[now] += sub[nx];
        }
      }
    }
  }

  int search(int now, int par, int m) {
    for (auto nx : g[now]) {
      if (nx == par || dead[nx]) continue;
      if (sub[nx] > m / 2) {
        return search(nx, now, m);
      }
    }
    return centroid = now;
  }

  void get_centroid(int root) {
    calc_sub(root);
    int m = sub[root];
    search(root, -1, m);
  }

  void dfs1(int now, int par, int d, int delta) {
    cnt[d] += delta;
    for (auto nx : g[now]) {
      if (nx == par || dead[nx]) continue;
      dfs1(nx, now, d + 1, delta);
    }
  }

  void dfs2(int now, int par, int d) {
    if (d <= k) {
      ret = (ret + cnt[k - d]) % mod;
    }
    for (auto nx : g[now]) {
      if (nx == par || dead[nx]) continue;
      dfs2(nx, now, d + 1);
    }
  }

  void via_centroid() {
    int delta = 1;
    dfs1(centroid, -1, 0, delta);
    ret = (ret + cnt[k]) % mod;
    for (auto nx : g[centroid]) {
      if (dead[nx]) continue;
      delta = -1;
      dfs1(nx, centroid, 1, delta);
      dfs2(nx, centroid, 1);
      delta = 1;
      dfs1(nx, centroid, 1, delta);
    }
    delta = -1;
    dfs1(centroid, -1, 0, delta);
  }

  int divide_conquer(int root = 0) {
    get_centroid(root);
    dead[centroid] = true;
    //重心を経由(重心が端点も含む)して複数の部分木同士の計算
    via_centroid();
    //個別の部分木に対してそれぞれ計算(より小さいサイズで同じ計算)
    for (auto nx : g[centroid]) {
      if (dead[nx]) continue;
      divide_conquer(nx);
    }

    dead[centroid] = false;
    return ret;
  }
};


long long powmod(long long n, long long k){
    if (k == 0) return 1;
    else if (k % 2 == 0){
        long long tmp = powmod(n, k / 2);
        return tmp * tmp % mod;
    }
    else return powmod(n, k - 1) * n % mod;
}

long long inverse(long long n) {
    return powmod(n, mod - 2);
}

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> k;
  TCD tr(n);
  rep(i, n - 1) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    tr.add_edge(a, b);
  }

  int inv = (k + 1) * k / 2;
  int ans = tr.divide_conquer(0);
  ans = ans * inverse(2) % mod;
  ans = ans * inv % mod;
  cout << ans << endl;
}
