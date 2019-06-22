//共通部分文字列
//O[(n + m)log^2(n + m)](n=|s|, m=|t|)(sa配列構築に一番時間がかかる)
//文字列sとtの共通した連続文字列の最長長さを求める


string s, t;

struct SuffixArray {
    int n, k;
    string text;
    vector<int> sa;
    vector<int> rank;
    vector<int> lcp;

    SuffixArray (const string &s)
    : text(s), n(s.size()), sa(n + 1), rank(n + 1), lcp(n)
    {}

    bool comp(int i, int j) {
        if (rank[i] != rank[j]) return rank[i] < rank[j];
        int ri = i + k <= n ? rank[i + k] : -1;
        int rj = j + k <= n ? rank[j + k] : -1;
        return ri < rj;
    }

    void construct_sa() {
        for (int i = 0; i <= n; i++) {
            sa[i] = i;
            rank[i] = i < n ? text[i] : -1;
        }

        for (k = 1; k <= n; k *= 2) {
            sort(sa.begin(), sa.end(), [&](const int& i, const int& j) {return comp(i, j);});

            vector<int> tmp(n + 1);
            tmp[sa[0]] = 0;
            for (int i = 1; i <= n; i++) {
                tmp[sa[i]] = tmp[sa[i - 1]] + (comp(sa[i - 1], sa[i]) ? 1 : 0);
            }

            for (int i = 0; i <= n; i++) {
                rank[i] = tmp[i];
            }
        }
    }

    void construct_lcp () {
        int h = 0;
        lcp[0] = 0;
        for (int i = 0; i < n; i++) {
            int j = sa[rank[i] - 1];
            if (h > 0) h--;
            for (; j + h < n && i + h < n; h++) {
                if (text[j + h] != text[i + h]) break;
            }
            lcp[rank[i] - 1] = h;
        }
    }
};

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    while (cin >> s >> t) {
        int n = s.size();
        int m = t.size();
        string st = s + '$' + t;
        SuffixArray suf(st);
        suf.construct_sa();
        suf.construct_lcp();
        int ans = 0;
        rep(i, n + m) {
            int mn = min(suf.sa[i], suf.sa[i + 1]);
            int mx = max(suf.sa[i], suf.sa[i + 1]);
            if (mn < n && n < mx) ans = max(ans, suf.lcp[i]);
        }
        cout << ans << endl;
    }
}
