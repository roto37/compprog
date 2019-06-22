//接尾辞配列(接尾辞を辞書順最小で並べたもの)と高さ配列(接尾辞配列の隣同士の共通最大接頭辞)
//考える文字列をsとする

//construct_saはO[nlog^2n] (nはテキスト(検索される文字列)の長さ)
//construct_lcpはO[n]
//low_bd(up_bd)はSA配列内でのlower_bound(upper_bound)([mlogn])
//countはO[mlogn] (mはパターン(検索する文字列)の長さ):パターンがテキストに何回出現するか数える

//sa[i]:=サフィックス配列でi番目(0-indexed)である、文字列sの開始位置(0-indexed)
//rank[i]:=文字列sのi番目からのサフィックスに対するsa配列のindex(0-indexed)
//lcp[i]:=sa[i]とsa[i + 1]の最大共通接頭辞数
//注意:空文字列もサフィックスに含む (sのn番目からのサフィックス(0-indexed))
//---------------------------------------------------------------------
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

    int low_bd(const string &pt) {
        int l = 0, r = n + 1;
        while (r - l > 1) {
            int m = (r + l) / 2;
            int val = text.compare(sa[m], pt.length(), pt);
            if (val < 0) l = m;
            else r = m;
        }
        return r;
    }

    int up_bd(const string &pt) {
        int l = 1, r = n + 1;
        while (r - l > 1) {
            int m = (r + l) / 2;
            int val = text.compare(sa[m], pt.length(), pt);
            if (val <= 0) l = m;
            else r = m;
        }
        return r;
    }

    bool match(const string &pt) {
        int idx = low_bd(pt);
        if (idx == sa.size()) return false;
        return text.compare(sa[idx], pt.length(), pt) == 0 ? true : false;
    }

    int count(const string &pt) {
        int l_idx = low_bd(pt);
        if (l_idx == sa.size()) return 0;
        if (text.compare(sa[l_idx], pt.length(), pt) != 0) return 0;
        int r_idx = up_bd(pt);
        return r_idx - l_idx;
    }
};

//--------------------------------------------------------------------
string s;
string pt[10];

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> s;
    rep(i, 10) cin >> pt[i];

    SuffixArray suf(s);
    suf.construct_sa(s);
    suf.construct_lcp(s);    //construct_saの後しかできない。

    rep(i, 10) {
        cout << pt[i] << " " << suf.count(s, pt[i]) << endl;
    }

}
