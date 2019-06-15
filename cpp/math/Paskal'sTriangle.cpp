//パスカルの三角形 O[n^2]
vector<vector<long long>> p_triangle(long long n) {
    vector<vector<long long>> ret(n + 1, vector<long long>(n + 1, 0));
    ret[0][0] = 1;
    for (int i = 1; i < n + 1; i++) {
        for (int j = 0 ; j < i + 1; j++) {
            if (j == 0) ret[i][j] = ret[i - 1][j];
            else if (j == i) ret[i][j] = ret[i - 1][j - 1];
            else ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
        }
    }
    return ret;
}

//確率ver(組み合わせを数えてからそれらが起きる確率で割ると誤差落ちすることがある!!!)
//nCk1, (n-k1)Ck2, ..., knCknという取り方をするとき knCkn が組み合わせで1だからといって省略してはいけない!!!
//knCkn = 1/(p^kn) で言いを持つ値が入っている。
//組み合わせとその確率について
//あるk個についてそれらが起きる確率が1/(p^k)であるとき, nCk通り選べるから
//この時の確率はnCk/(p^k)となる。
//ret[i][j] = iCj / (p^j) である。
vector<vector<long double>> p_triangle(long long n, long double p) {
    vector<vector<long double>> ret(n + 1, vector<long double>(n + 1, 0));
    ret[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0 ; j <= i; j++) {
            if (j == 0) ret[i][j] = ret[i - 1][j];
            else if (j == i) ret[i][j] = ret[i - 1][j - 1] / p;
            else ret[i][j] = ret[i - 1][j - 1] / p + ret[i - 1][j];
        }
    }
    return ret;
}
