//#include <bits/stdc++.h>

#include <iostream>
#include <algorithm>

#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <deque>
#include <cstring>
#include <string>
#include <utility>
#include <array>
#include <complex>
#include <valarray>

#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <chrono>
#include <random>
#include <numeric>


using namespace std;
#define int long long

typedef long long ll;
typedef unsigned long long ull;
//typedef unsigned __int128 HASH;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef pair<ull, ull> pullull;
typedef pair<ll,int> plli;
typedef pair<double,int> pdi;
typedef pair<long double, int> pdbi;
typedef pair<int,pii> pipii;
typedef pair<ll,pll> plpll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<pii> vpii;
typedef vector<vector<int>> mat;

#define rep(i,n) for (int i=0;i<(n);i++)
#define rep2(i,a,b) for (int i=(a);i<(b);i++)
#define rrep(i,n) for (int i=(n);i>0;i--)
#define rrep2(i,a,b) for (int i=(a);i>b;i--)
#define pb push_back
#define fi first
#define se second
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()

const ll hmod1 = 999999937;
const ll hmod2 = 1000000000 + 9;
const int INF = 1<<30;
const ll INFLL = 1LL<<62;
const long double EPS = 1e-12;
const ll mod = 1000000000 + 7;
const int dx4[4] = {1, 0, -1, 0};
const int dy4[4] = {0, 1, 0, -1};
const int dx8[8] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dy8[8] = {0, 1, -1, 1, -1, 0, 1, -1};
const long double pi = 3.141592653589793;

#define addm(X, Y) (X) = ((X) + ((Y) % mod) + mod) % mod
#define inside(y, x, h, w) (0 <= (y) && (y) < (h) && 0 <= (x) && (x) < (w)) ? true : false

//debug
#define DEBUG

#define DUMPOUT cout

#ifdef DEBUG
#define dump(...) DUMPOUT<<#__VA_ARGS__<<" :["<<__FUNCTION__<<":"<<__LINE__<<"]"<<endl; DUMPOUT<<"    "; dump_func(__VA_ARGS__)
#else
#define dump(...)
#endif

void dump_func() {DUMPOUT << endl;};

template <class Head, class... Tail> void dump_func(Head&& head, Tail&&... tail) {
    DUMPOUT << head;
    if (sizeof...(Tail) == 0) DUMPOUT << " ";
    else DUMPOUT << ", ";
    dump_func(std::move(tail)...);
}

//ostream
template<typename T> ostream& operator << (ostream& os, vector<T>& vec) {
    os << "["; for (int i = 0; i<vec.size(); i++) os << vec[i] << (i + 1 == vec.size() ? "" : ", "); os << "]";
    return os;
}

template<typename T, typename U> ostream& operator << (ostream& os, pair<T, U>& pair_var) {
    os << "(" << pair_var.first << ", " << pair_var.second << ")";
    return os;
}

template<typename T, typename U> ostream& operator << (ostream& os, map<T, U>& map_var) {
    os << "[";
    for (auto itr = map_var.begin(); itr != map_var.end(); itr++) {
        os << "(" << itr->first << ", " << itr->second << ")"; itr++;  if(itr != map_var.end()) os << ", "; itr--;
    }
    os << "]";
    return os;
}

template<typename T> ostream& operator << (ostream& os, set<T>& set_var) {
    os << "[";
    for (auto itr = set_var.begin(); itr != set_var.end(); itr++) {
        os << *itr; ++itr; if(itr != set_var.end()) os << ", "; itr--;
    }
    os << "]";
    return os;
}

/*
template <typename T>
struct edge {
    int from, to;
    T cost;
    edge(int t) : to(t) {}
    edge(int t, T d) : to(t), cost(d) {}
    edge(int a, int b, T d) : from(a), to(b), cost(d) {}

    bool operator<(const edge &e) const {
        return cost < e.cost;
    }
    bool operator>(const edge &e) const {
        return cost > e.cost;
    }
};
*/

struct HLD {
  int n, new_id;
  vector<vector<int>> g;
  vector<int> par, sub, dep, hev, head, aft_id, bef_id, tree_idx;

  HLD(int n)
  : n(n),
    new_id(0),
    g(n),
    par(n, -1),
    sub(n, 1),
    dep(n, 0),
    hev(n, -1),
    head(n, -1),
    aft_id(n, -1),
    bef_id(n, -1),
    tree_idx(n, -1)
    {};

  void add_edge(int a, int b) {
    g[a].emplace_back(b);
    g[b].emplace_back(a);
  }

  void build(vector<int> rs = {0}) {
    int c = 0;
    for (auto r : rs) {
      calc_sub(r);
      bfs(r, c++);
    }
  }

  void calc_sub(int r) {
    stack<pii> st;
    st.emplace(r, 0);
    par[r] = -1;
    dep[r] = 0;
    while (!st.empty()) {
      int now = st.top().first;
      int &i = st.top().second;
      if (i < g[now].size()) {
        int nx = g[now][i++];
        if (nx ==  par[now]) continue;
        par[nx] = now;
        dep[nx] = dep[now] + 1;
        st.emplace(nx, 0);
      }
      else {
        st.pop();
        int mx_sub = 0;
        for (auto nx : g[now]) {
          if (nx == par[now]) continue;
          sub[now] += sub[nx];
          if (mx_sub < sub[nx]) {
            mx_sub = sub[nx];
            hev[now] = nx;
          }
        }
      }
    }
  }

  void bfs(int r, int c) {
    queue<int> q({r});
    while(!q.empty()) {
      int chain_head = q.front(); q.pop();
      for (int now = chain_head; now != -1; now = hev[now]) {
        head[now] = chain_head;
        aft_id[now] = new_id;
        bef_id[new_id] = now;
        tree_idx[now] = c;
        new_id++;
        for (auto nx : g[now]) {
          if (nx != par[now] && nx != hev[now]) {
            q.push(nx);
          }
        }
      }
    }
  }

  //[l, r]
  void f(int l, int r) {
    //bit, segtreeの各種操作
    return ;
  }

  //[u, v]
  void for_each_v(int u, int v) {
    while (1) {
      if (aft_id[u] > aft_id[v]) swap(u, v);
      f(max(aft_id[head[v]], aft_id[u]), aft_id[v]);
      if (head[u] != head[v]) v = par[head[v]];
      else break;
    }
  }

  //[u, v]
  void for_each_e(int u, int v) {
    while (1) {
      if (aft_id[u] > aft_id[v]) swap(u, v);
      if (head[u] != head[v]) {
        f(aft_id[head[v]], aft_id[v]);
        v = par[head[v]];
      }
      else {
        if (u != v) f(aft_id[u] + 1, aft_id[v]);
        break;
      }
    }
  }

  int lca(int u, int v) {
    while (1) {
      if (aft_id[u] > aft_id[v]) swap(u, v);
      if (head[u] == head[v]) return u;
      v = par[head[v]];
    }
  }

  int dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
  }

};



signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
}
