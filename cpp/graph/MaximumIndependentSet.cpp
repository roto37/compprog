//最大独立集合の大きさを求める
//O[n * 1.466^n](?) n <= 40ぐらいなら高速
//グラフgの最大独立集合 <=> グラフgの補グラフでの最大クリーク
//             ↑                                           ↑
//        solve(true)                               solve(false)

#include <bits/stdc++.h>

int n, m;

struct MaxIndep {
	int n, ans;
	vector<vector<int>> g, G, H;    //"g"上での最大独立集合の大きさを求める

	MaxIndep(int max_v) : ans(0), n(max_v), G(max_v), H(max_v) {
		for (int i = 0; i < max_v; i++) {
			for (int j = 0; j < max_v; j++) {
				if (i == j) continue;
				H[i].push_back(j);
			}
		}
	}

	void edge(int fr, int to) {
		G[fr].push_back(to);
		G[to].push_back(fr);
		H[fr].erase(remove(H[fr].begin(), H[fr].end(), to), H[fr].end());
		H[to].erase(remove(H[to].begin(), H[to].end(), fr), H[to].end());
	}

	void dfs(int now, int cnt, vector<bool>& used) {
		if (n  - now + cnt <= ans) return;
		if (now == n) {
			ans = max(ans, cnt);
			return;
		}
	
		int deg = 0;
		for (auto nx : g[now]) if (!used[nx]) deg++;
		//not use
		if (deg > 1 || used[now]) {
			if (used[now]) dfs(now + 1, cnt, used);
			else {
				used[now] = true;
				dfs(now + 1, cnt, used);
				used[now] = false;
			}
		}
		//use
		if (!used[now]) {
			vector<int> tmp = {now};
			for (auto nx : g[now]) {
				if (!used[nx]) {
					tmp.push_back(nx);
					used[nx] = true;
				}
			} 
			dfs(now + 1, cnt + 1, used);
			for (auto v : tmp) used[v] = false;
		}
	}

	int solve(bool max_independent = true) { 
		if (max_independent) g = G;    //最大独立集合
		else g = H;    //最大クリーク
		vector<bool> used(n);
		dfs(0, 0, used);
		return ans;
	}
};



signed main() {	
    cin.tie(0);
    ios::sync_with_stdio(false);
	cin >> n >> m;
	MaxIndep MI(n);
	rep(i, m) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		MI.edge(a, b);//この時に "与えられるグラフ" と "その補グラフ" を同時に構築
	}

	//与えられたグラフで最大独立集合の大きさを求めるときはtrue, 最大クリークの大きさを求めるときはfalse
	cout << MI.solve(false) << endl;
}	
