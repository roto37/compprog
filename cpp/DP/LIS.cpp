//LIS(最長増加部分列)(減少もaの各値をマイナスにすれば増加のときに帰着できる)
//今考える数列をaとする
//増加部分列とはすべてのi<jでai<ajを満たす部分列
//O[nlogn](n = a.size())
//dpの値がINT_MAXでないものでidxが最も大きくなるidx + 1が答えとなる。(idxは0-indexed)

int LIS(vector<long long> &a) {
    int size = a.size();
    vector<long long> dp(size, INFLL);

    for (int i = 0; i < size; i++ ) {
        int idx = lower_bound(all(dp), a[i]) - dp.begin();
        dp[idx] = a[i];
    }
    return lower_bound(all(dp), INFLL) - dp.begin();
}
