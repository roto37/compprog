//有効グラフが与えられたときの(頂点 x -> y)トポロジカル順序の総数
//bitdp(O[2^N]:Nは頂点数)
//配るdp ver

int n, m;
vector<vector<int>> g(20);
ll dp[1<<16];

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    rep(i, m) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[y].push_back(x);          //配るdpでは有効グラフと逆なので注意
    }
    dp[0] = 1;
    rep(i, 1<<n) {
        rep(j, n) {                //今集合iを考えていてそこにjを加える場合
            if (i>>j & 1) continue;    //すでに集合iにjが入ってしまっている
            bool ok = true;
            for (auto k : g[j]) {
                if (!(i>>k & 1)) {     //jをiに加えることができるための条件は集合iで
                    ok = false;        //jに入ってくるような頂点がすべて含まれていること
                    break;
                }
            }
            if (ok) {
                dp[i|(1<<j)] += dp[i];
            }
        }
    }
}
------------------------------------------------------------------------
//もらうdp ver
signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    rep(i, m) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[y].push_back(x);          //もらうdpでは有効グラフと同じ
    }
    dp[0] = 1;
    rep(i, 1 << n) {
        rep(j, n) {               //jを加えて頂点集合iを作る
            if (!(i>>j & 1)) continue;   //iにjが含まれている必要がある
            bool ok = true;
            for (auto k : g[j]) {
                if (i>>k & 1) {          //jから出ている辺につながっている頂点が
                    ok = false;          //jを加える前からiにあるときは条件に反する(これは必要条件)
                }
            }
            if (ok) {
                dp[i] += dp[i^(1<<j)];  //上で書いたように十分条件ではないが更新では正しいものしか
            }                           //値が入らないので大丈夫(?)正しくないものもokとなり更新されるが
        }                               //0で更新される(?)
    }
    cout << dp[(1<<n) - 1] << endl;
}
