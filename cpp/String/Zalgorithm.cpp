//Zalgorithm(共通接頭辞の最大長さを求める)
//O[n] (n = |s|)
//文字列s全体とsの各位置(0-indexed)からの接尾辞の共通接頭辞の最大長さを求める

vector<int> Zalgorithm(const string &s) {
    int n = s.size();
    vector<int> coprefix(n, 0);
    coprefix[0] = n;
    int start = 1;
    int now = 0;
        while (start + now < n && s[now] == s[start + now]) now++;
        coprefix[start] = now;
        if (now == 0) {
            start++;
            continue;
        }
        int nx = 1;
        while (start + nx < n && nx + coprefix[nx] < now) {
            coprefix[start + nx] = coprefix[nx];
            nx += 1;
        }
        start += nx;
        now -= nx;
    }
    return coprefix;
}

//-------------------------------------------------------------------------
//解説
//line51"<--ここ"について：[start, now)まで見たもので次に調べるのはstart + 1からであるが
//[start + 1, now)が共通しているのはすでに分かっており, coprefix[1]も分かって
//いるのでわざわざまた調べる必要はない。ただしnx + coprefix[start + nx]が
//now以上は今までの一致範囲を超えているので調べられない。
//(nx + coprefix[nx] = nowのとき、startから調べて一致した最後の文字が、nxから最大一致した
//最後の文字にもなるが、now番目が一致するかもしれないのでcoprefix[nx]を確定できない)

vector<int> Zalgorithm(const string &s) {
    int n = s.size();
    vector<int> coprefix(n, 0);
    coprefix[0] = n;
    int start = 1;         //文字列sのstart番目からの接尾辞と文字列全体の共通接頭辞を探す(0-index)
    int now = 0;           //文字列sの先頭からnow番目を表す(0-index)。常にs[start, start + now)が共通接頭辞になる。
    while (start < n) {
        while (start + now < n && s[now] == s[start + now]) now++;
        coprefix[start] = now;
        if (now == 0) {
            start++;
            continue;
        }
        int nx = 1;
        while (start + nx < n && nx + coprefix[nx] < now) { //<--ここ
            coprefix[start + nx] = coprefix[nx];
            nx += 1;
        }
        start += nx;
        now -= nx;
    }
    return coprefix;
