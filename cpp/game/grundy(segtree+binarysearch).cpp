//grundy数を高速に求める(ひとつのgrundy数当たり, O[loglogn])
//=> 二分探索(grundy数を二分探索) + segtree(配列のkey:grundy数, value:index)
//ただしこれが可能なのは, grundy数の値がsegtreeの配列に収まるときだけ!

/*ex) ARC038 C:茶碗と豆
         https://beta.atcoder.jp/contests/arc038/tasks/arc038_c

概要：n個の茶碗(0 ~ n-1)があり, i番目にはc[i], a[i]が与えられる。
       ・c[i]:=茶碗 [i - c[i] : i - 1] に豆を移動させることができる。
       ・a[i]:=茶碗 i にはa[i]この豆が最初入っている。
       二人のplayerは茶碗 [1 : n - 1] を選び豆を1つ選び, [i - c[i] : i - 1] に移動させる
       という行動を交互に行う。茶碗 [1 : n - 1] から豆を選べなくなった方が負けである。
       互いが最適に行動したとき, 勝つのはどちらか。
制約：n <= 10^5, 0 <= a <= 10^9, 0 <= c[i] <= i, Σa >= 1

解法：今 i 番目の茶碗について考えているとき
        grundy[i] = mex{grundy[i - c[i]], grundy[i - c[i] + 1], ..., grundy[i - 1]};
        であり mex を高速に求めるために二分探索と segtree を使う。
        具体的には
        葉 node の seg[x] := grundy数が x である茶碗の [0 : i - 1] の index の最大値
        の segtree を使い、grundy[i]の値を二分探索(初期値 l = 0, r = i + 1)で求める。
        判定は if (seg.get(0, m) >= i - c[i])  l = m; else r = m;
        (seg.get(0, m) >= i - c[i] なら grundy数が[0 : m) の値のものはすべて茶碗のindexが i - c[i]以上に
        なるので m は grundy[i] の候補になりうる)
        まだgrundy数が現れていない範囲[0:m)について考えているとき
        m は grundy[i] の候補にはならないことに注意!!
        (segtreeの初期化でmin_queryなのに-1で初期化する理由)
*/

#include <bits/stdc++.h>

int n;

struct segtree {
    int size;
    vector<long long> node;

    segtree (int n) : size(1) {
        while (size < n) size *= 2;
        node.resize(2 * size - 1, -1);  //<-----minだが-1で初期化!!
    }

    void update(int k, int a) {
        k += size - 1;
        node[k] = a;
        while (k > 0){
            k = (k - 1) / 2;
            node[k] = min(node[2 * k + 1], node[2 * k + 2]);
        }
    }
    //[queryL: queryR)
    long long get(int queryL, int queryR, int k = 0, int nodeL = 0, int nodeR = -1) {
        if (nodeR == -1) nodeR = size;
        if (nodeR <= queryL || queryR <= nodeL) return INFLL / 2;
        if (queryL <= nodeL && nodeR <= queryR) return node[k];
        else{
            int nodeM = (nodeL + nodeR) / 2;
            long long vl = get(queryL, queryR, 2 * k + 1, nodeL, nodeM);
            long long vr = get(queryL, queryR, 2 * k + 2, nodeM, nodeR);
            return min(vl, vr);
        }
    }
};

signed main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n;
    int xors = 0;
    segtree seg(n + 1);
    seg.update(0, 0);
    rep2(i, 1, n) {
        int c, a;
        cin >> c >> a;
        int l = 0, r = i + 1;
        while (r - l > 1) {
            int m = (r + l) / 2;
            if (seg.get(0, m) >= i - c) l = m;//[0 : m)が-1を含むときは-1が返ってきてmはgrundy数にはなりえない!
            else r = m;
        }
        int gr = l;
        if (a % 2 == 1) xors ^= gr;
        seg.update(gr, i);
    }
    cout << (xors == 0 ? "Second" : "First") << endl;
}
