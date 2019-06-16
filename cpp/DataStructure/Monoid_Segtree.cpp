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

#include<memory>


using namespace std;
//#define int long long

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
//const ll mod = 998244353;
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


namespace Monoid {
  /*
      T : 要素の集合, (a, b ∈ T)
      E : Tへの作用素の集合, (c, d ∈ E)
      G : Eへの作用素の集合
      f : T×T → T  f(a, b)
      g : T×E → T  g(a, c)
      h : E×E → E  h(c, d)
      o : G×E → E
      p : T×T → G  p(a, b)
      identity_T : Tの単位元
      identity_E : Eの単位元
  */
  /*
      条件
      g(f(a, b), c) = f(g(a, c), g(b, c)) (遅延評価が可能か)
      g(f(a, b), o(p(a, b), c)) = f(g(a, o(a, c)), g(b, o(b, c))) (遅延評価が可能か)
      g(a, h(c, d)) = g(g(a, c), d) (遅延評価の値をため込めるか)
      g(a, e) = a (eは単位元, e∈E) (伝播flagの役割だが, do_propが代わりをするのであまり重要ではない)
      f, g, h は 高速 (O(n)はダメ)
  */

  // Sum, Update
  template <typename T, typename E> struct RSUQ {
    using value_type_T = T;
    using value_type_E = E;
    inline static T f(const T& a, const T& b) {return a + b;}
    inline static T g(const T& a, const E& c) {return c;}
    inline static E h(const E& c, const E& d) {return d;}
    inline static T identity_T() {return T(0);}
    inline static E identity_E() {return E(0);}
  };
  // Min, Update
  template <typename T, typename E> struct RMNUQ {
    using value_type_T = T;
    using value_type_E = E;
    inline static T f(const T& a, const T& b) {return (a < b) ? a : b;}
    inline static T g(const T& a, const E& c) {return c;}
    inline static E h(const E& c, const E& d) {return d;}
    inline static T identity_T() {return std::numeric_limits<T>::max();}
    inline static E identity_E() {return std::numeric_limits<E>::max();}
  };
  // Max, Update
  template <typename T, typename E> struct RMXUQ {
    using value_type_T = T;
    using value_type_E = E;
    inline static T f(const T& a, const T& b) {return (a > b) ? a : b;}
    inline static T g(const T& a, const E& c) {return c;}
    inline static E h(const E& c, const E& d) {return d;}
    inline static T identity_T() {return std::numeric_limits<T>::lowest();}
    inline static E identity_E() {return std::numeric_limits<E>::lowest();}
  };
  // Sum, Add, これは未完成
  template <typename T, typename E> struct RSAQ {
    using value_type_T = T;
    using value_type_E = E;
    inline static T f(const T& a, const T& b) {return a + b;}
    inline static T g(const T& a, const E& c) {return a + c;}
    inline static E h(const E& c, const E& d) {return c + d;}
    inline static T identity_T() {return T(0);}
    inline static E identity_E() {return E(0);}
  };
  // Min, Add
  template <typename T, typename E> struct RMNAQ {
    using value_type_T = T;
    using value_type_E = E;
    inline static T f(const T& a, const T& b) {return (a < b) ? a : b;}
    inline static T g(const T& a, const E& c) {return a + c;}
    inline static E h(const E& c, const E& d) {return c + d;}
    inline static T identity_T() {return std::numeric_limits<T>::max();}
    inline static E identity_E() {return std::numeric_limits<E>::max();}
  };
  // Max, add
  template <typename T, typename E> struct RMXAQ {
    using value_type_T = T;
    using value_type_E = E;
    inline static T f(const T& a, const T& b) {return (a > b) ? a : b;}
    inline static T g(const T& a, const E& c) {return a + c;}
    inline static E h(const E& c, const E& d) {return c + d;}
    inline static T identity_T() {return std::numeric_limits<T>::lowest();}
    inline static E identity_E() {return std::numeric_limits<E>::lowest();}
  };
}

template<class Monoid>
struct Segtree {
  using T = typename Monoid::value_type_T;
  using E = typename Monoid::value_type_E;
  int sz;
  vector<T> node;
  vector<E> lazy;
  vector<bool> do_prop;

  Segtree(int n_) {
    sz = 1;
    while (sz < n_) sz *= 2;
    node.resize(2*sz-1, Monoid::identity_T());
    lazy.resize(2*sz-1, Monoid::identity_E());
    do_prop.resize(2*sz-1, false);
  }

  inline void propagate(int l, int r, int k) {
    if (!do_prop[k]) return;
    node[k] = Monoid::g(node[k], lazy[k]);
    if (r - l > 1) {
      lazy[2*k+1] = Monoid::h(lazy[2*k+1], lazy[k]);
      lazy[2*k+2] = Monoid::h(lazy[2*k+2], lazy[k]);
      do_prop[2*k+1] = true;
      do_prop[2*k+2] = true;
    }
    lazy[k] = Monoid::identity_E();
    do_prop[k] = false;
  }

  inline void modify(int queryL, int queryR, int val, int k, int l, int r) {
    propagate(l, r, k);
    if (r <= queryL || queryR <= l) return ;
    if (queryL <= l && r <= queryR) {
      lazy[k] = val;
      do_prop[k] = true;
      propagate(l, r, k);
      return ;
    }
    int m = (l + r) / 2;
    modify(queryL, queryR, val, 2*k+1, l, m);
    modify(queryL, queryR, val, 2*k+2, m, r);
    node[k] = Monoid::f(node[2*k+1], node[2*k+2]);
  }

  inline void modify(int queryL, int queryR, int val) {
    modify(queryL, queryR, val, 0, 0, sz);
  }

  inline T get(int queryL, int queryR, int k, int l, int r) {
    propagate(l, r, k);
    if (r <= queryL || queryR <= l) return Monoid::identity_T();
    if (queryL <= l && r <= queryR) return node[k];
    int m = (l + r) / 2;
    T vl = get(queryL, queryR, 2*k+1, l, m);
    T vr = get(queryL, queryR, 2*k+2, m, r);
    return Monoid::f(vl, vr);
  }

  inline T get(int queryL, int queryR) {
    return get(queryL, queryR, 0, 0, sz);
  }

  void debug() {
    for (int i = 0; i < sz; i++) {
      cerr << "i:" << i << " / " << "val:" << node[i + sz - 1] << endl;
    }
  }
};

int n, q;

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> q;
  Segtree<Monoid::RMNUQ<int, int>> seg(n);
  rep(i, q) {
    int com, l, r, val;
    cin >> com >> l >> r;
    if (com == 0) {
      cin >> val;
      //cerr << l << " " << r << " " << val << endl;
      seg.modify(l, r+1, val);
      //seg.debug();
    }
    else {
      //cerr << l << " " << r << endl;
      cout << seg.get(l, r+1) << endl;
    }
  }
}
