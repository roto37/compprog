/*
並列二分探索
各queryに対して二分探索するのではなく、二分探索中に各queryを処理する。
二分木を幅優先探索していく
queにはタプル(探索範囲左、探索範囲右、今の探索範囲で考えるべきquery群)を入れていく
最も左(most_left)になったときにUnionFindを初期化する

verify:https://code-thanks-festival-2017-open.contest.atcoder.jp/submissions/1837239
下のコードは最小値を求めるやつでrightはすべてqueryの条件を満たす(ただしright=mは除く)
*/

#include <bits/stdc++.h>

struct UnionFind {
    int cnt;    //uniteの回数
    vector<int> par, rank;

    UnionFind() {}
    
    UnionFind(int n) : par(n), rank(n, 0), cnt(0) {
        for (int i = 0; i < n; i++) {
            par[i] = i;
        }
	}

    int find_root(int now) {
        if (now == par[now]) return now;
        return par[now] = find_root(par[now]);
    }

    void unite(int u, int v) {
        cnt++;  
        int x = find_root(u);
        int y = find_root(v);
        if (x == y) return ;
        if (rank[x] < rank[y]) swap(x, y);
        par[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }

    bool same(int u, int v) {
        return find_root(u) == find_root(v);
    }
};

int n, m;
int a[100000 + 5], b[100000 + 5];
int x[100000 + 5], y[100000 + 5];
int ans[100000 + 5];
UnionFind uf[30];

//n:UnionFindの初期化size
//q:queryの数
//most_left, most_rightは二分探索で考えたい最も左、右の値
//下のものは各queryに対して最小値を求める(解がない場合はright == most_rightとする)
//最大も普通の二分探索のように書き換えればいい(leftに常に成立する値が入るとする。答えはleft)

void parallel_binary_search(int n, int q, int most_left, int most_right) {
    rep(i, q) ans[i] = -1;
    vector<int> all_query;
    rep(i, q) all_query.push_back(i);
    queue<tuple<int, int, vector<int>>> que;
    que.push(make_tuple(most_left, most_right, all_query));
    int idx = -1;
    while (!que.empty()) {
        int left, right; vector<int> query;
        tie(left, right, query) = que.front(); que.pop();
        if (left == most_left) {
            uf[++idx] = UnionFind(n);
        }
        if (right - left == 1) {
            if (right == most_right) continue;
            for (auto i : query) {
                ans[i] = right + 1;
            }
            continue;
        }
        int mid = (left + right) / 2;
        rep2(i, uf[idx].cnt, mid + 1) {
            uf[idx].unite(a[i], b[i]);
        } 
        vector<int> query_l, query_r; 
        for (auto i : query) {;
            if (uf[idx].same(x[i], y[i])) query_l.push_back(i);
            else query_r.push_back(i);
        }
        que.push(make_tuple(left, mid, query_l));
        que.push(make_tuple(mid, right, query_r));
    }
}
----------------------------------------------------------------------------------

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    rep(i, m) {
        cin >> a[i] >> b[i];
        a[i]--; b[i]--;
    }
    int q;
    cin >> q;
    rep(i, q) {
        cin >> x[i] >> y[i];
        x[i]--; y[i]--;
    }
    
    parallel_binary_search(n, q, -1, m);

    rep(i, q) cout << ans[i] << endl;
}
