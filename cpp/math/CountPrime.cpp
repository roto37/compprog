//[1, 2..., n]までの数字のうち素因数として素数pが出てくる回数の合計
//O[logp(n)]
//ans = n/p + n/p^2 + n/p^3 + ...で求めることができる

//ex) [1, 2, ...8]までで、2が出る回数の合計 -> 8/2 + 8/4 + 8/8 = 7

int total_p(ll n, int p) {
    int cnt = 0;
    ll di = p;
    while (n >= di) {
        cnt += n / di;
        di *= di;
    }
    return cnt;
}
