//Trie木
//構築(add)にO[m] (m:Trie木にaddする総文字数)
//検索(search)にO[n] (n:検索する文字列の長さ)
//検索は構築したときに入れた文字と完全に一致していたら,true(部分文字列になっていたりするものはfalse)
//英小文字に対応するようになっているので大文字の時は書き換える

//-----------------------------------------------------------
struct Tnode {
    vector<int> nx, accept;
    char fr, to;

    Tnode(char fr = 'a', char to = 'z')
        :fr(fr), to(to)
    {
        nx.resize(to - fr + 1, -1);
    }
};

struct Trie {
    int root;
    vector<Tnode> node;
    char fr, to;

    Trie(char fr = 'a', char to = 'z')
        :root(0), fr(fr), to(to)
    {
        node.push_back(Tnode(fr, to));
    }

    void add(int id, const string &s) {
        int now = root;
        for (auto c : s) {
            c -= fr;
            if (node[now].nx[c] == -1) {
                node[now].nx[c] = node.size();
                node.push_back(Tnode(fr, to));
            }
            now = node[now].nx[c];
        }
        node[now].accept.push_back(id);
    }

    int match(const string &s) {
        int now = root;
        for (auto c : s) {
            c -= fr;
            if (node[now].nx[c] == -1) return 0;
            now = node[now].nx[c];
        }
        return node[now].accept.size();
    }
};
//-----------------------------------------------------------

int n = 10;
string text[10];
string pt[10];

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    rep(i, n) cin >> text[i];
    rep(i, n) cin >> pt[i];

    Trie tr('A', 'z');
    rep(i, n) tr.add(i, text[i]);

    rep(i, n) {
        cout << pt[i] + " " + "is" + " ";
        if (tr.match(pt[i])) cout << "exist" << endl;
        else cout << "not found" << endl;
    }
}
