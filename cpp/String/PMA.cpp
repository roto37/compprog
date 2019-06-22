//Pattern Matching Automaton (Aho-chorasick法)
//O[n + m] (n:textの長さ, m:ptの文字列の長さの総和)
//addとconstructにO[m], matchにO[n]


struct Tnode {
    vector<int> nx, accept;
    char fr, to;

    Tnode(char fr = 'a', char to = 'z')
        :fr(fr), to(to)
    {
        nx.resize(to - fr + 1, -1);
    }
};

struct PMA {
    int root;
    vector<Tnode> node;
    vector<int> fail_back;
    char fr, to;

    PMA (char fr = 'a', char to = 'z')
        :root(0), fr(fr), to(to)
    {
        node.push_back(Tnode(fr, to));
    }

    void add(const string &s, int id) {
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

    void construct() {
        queue<int> q;
        q.push(root);
        fail_back.resize(node.size(), 0);
        fail_back[root] = -1;
        while (!q.empty()) {
            int now = q.front(); q.pop();
            for (int c = 0; c <= to - fr; c++) {
                int next = node[now].nx[c];
                if (next == -1) continue;
                q.push(next);
                if (now == root) {
                    fail_back[next] = root;
                    continue;
                }
                int back_node = fail_back[now];
                while (back_node >= root && node[back_node].nx[c] == -1) {
                    back_node = fail_back[back_node];
                }
                fail_back[next] = max(root, node[max(root, back_node)].nx[c]);
            }
        }
    }

    int match (const string &s, vector<int> &result) {
        int now = root;
        int total = 0;
        for (auto c : s) {
            c -= fr;
            while (now >= root && node[now].nx[c] == -1) now = fail_back[now];
            if (now < root) {
                now = root;
                continue;
            }
            int next = node[now].nx[c];
            for (auto idx : node[next].accept) {
                result[idx]++;
                total++;
            }
            now = next;
        }
        return total;
    }

};


int k, q;
string text;
string pt[1005];

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> text;
    cin >> q;
    rep(i, q) cin >> pt[i];

    PMA pma('A', 'z');
    rep(i, q) pma.add(pt[i], i);
    pma.construct();
    vector<int> result(q);
    int cnt = pma.match(text, result);

    rep(i, q) {
        if (result[i] > 0) cout << 'y' << endl;
        else cout << 'n' << endl;
    }
}
