#include <bits/stdc++.h>
using namespace std;
k個のUnionFindをsizeをnで初期化する方法
vector<UnionFind> ufs(k, UnionFind(n));
ufs[0].same(u,v)等でそれぞれのUnionFindに操作が行える

引数にサイズを指定しないと初期化されない!!

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
UnionFindは0-indexed!!!!!!!!!!!!!!!!!!!
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
-------------------------------------------------------------

struct UnionFind {
	vector<int> par, rank;

	UnionFind() {}

	UnionFind(int n) : par(n), rank(n, 1) {
		for (int i = 0; i < n; i++) {
			par[i] = i;
		}
	}

	int find_root(int now) {
		if (par[now] == now) return now;
		return par[now] = find_root(par[now]);
	}

	void unite(int u, int v) {
		int x = find_root(u);
		int y = find_root(v);
		if (x == y) return;

		if (rank[x] < rank[y]) swap(x, y);
		par[y] = x;
		if (rank[x] == rank[y]) rank[x]++;
	}

	bool same(int u, int v) {
		return find_root(u) == find_root(v);
	}
};

-----------------------------------------------------
struct UnionFind {
	vector<int> par, rank;    //rank[i]:=頂点iの属する根からの深さ(縮約で変更はしない)
	//int cmps;    連結成分の総数
	//vector<int> cmp_cnt;    cmp_cnt[i]:=頂点iの属する連結成分内の要素数

	UnionFind() {}

	UnionFind(int n) : par(n), rank(n, 1) {
		//cmps = n;
		for (int i = 0; i < n; i++) {
			par[i] = i;
			//cmp_cnt[i] = 1;
		}
	}

	int find_root(int now) {
		if (par[now] == now) return now;
		return par[now] = find_root(par[now]);
	}

	void unite(int u, int v) {
		int x = find_root(u);
		int y = find_root(v);
		if (x == y) return;

		if (rank[x] < rank[y]) swap(x, y);
		par[y] = x;
		if (rank[x] == rank[y]) rank[x]++;
		//cmps--;
		//cmp_cnt[x] += cmp_cnt[y];
	}

	bool same(int u, int v) {
		return find_root(u) == find_root(v);
	}


	/*頂点xの属する連結成分の数を求める
	int count_same(int x) {
		return cmp_cnt[find_root(x)];
	}
	*/

};
------------------------------------------------------------
//並列二分探索のときに使う。cmps, cmp_cntがない。
//cntがある。(uniteした回数) <- これをさぼるとTLEする(?)

struct UnionFind {
    int cnt;
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
------------------------------------------------------------------------------
class UnionFind {
    private:
        vector<int> parent,rank,tree_w;
        int tree_num;
    public:
        UnionFind(int size) {
            tree_num = size;
            for (int i = 0; i < size; i++) {
                parent.push_back(i);
                rank.push_back(0);
                tree_w.push_back(1);
            }
        }

        int findset(int x) {
            return x == parent[x] ? x : parent[x] = findset(parent[x]);
        }

        void unite(int x, int y) {
            x = findset(x); y = findset(y);
            if (x == y) return;
            if (rank[x] > rank[y]) swap(x, y);
            parent[x] = y;
            tree_num -= 1;
            tree_w[y] += tree_w[x];
            if (rank[x] == rank[y]) rank[y] += 1;
        }

        bool same(int x, int y) {
            return findset(x) == findset(y);
        }

        int tree_number(){
            return tree_num;
        }

        int tree_weight(int x){
            return tree_w[findset(x)];
        }
};

//------------------------------------------------------------------------

int n,q;
int main(){
    cin >> n >> q;
    UnionFind uf(n);
    for(int i=0; i<q; i++){
        int c,x,y;
        cin >> c >> x >> y;
        if(c==0) uf.unite(x,y);
        else cout << uf.same(x,y) << endl;
    }
    return 0;
}
