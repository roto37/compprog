//重複組み合わせ
//n種類のものから重複を許してk個選ぶ場合の数はnHk=(n+k−1)Ck通り。
//min(O[k],O[n-k])(ただし,kはnCkのk powmod(繰り返し二乗法)はmin(O[logk],O[log(n-k)])

long long powmod(long long n, long long k){
    if (k == 0) return 1;
    else if (k % 2 == 0){
        long long tmp = powmod(n, k / 2);
        return tmp * tmp % mod;
    }
    else return powmod(n, k - 1) * n % mod;
}

long long inverse(long long n) {
    return powmod(n, mod - 2);
}

vector<long long> init_fact(long long n) {
    vector<long long> fact(n + 1, 0);
    fact[0] = 1;
    for (int i = 1; i < n + 1; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    return fact;
}

long long nCk(long long n, long long k) {
    long long ret = 1;
    if (n - k < k) k = n - k;
    for (int i = n; i > n - k; i--) {
        ret = ret * i % mod;
    }
    //factは初期化!!
    /*
    long long fact[k + 1];
    fact[0] = 1;
    for (int i = 1; i < k + 1; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    */
    return ret * inverse(fact[k]) % mod;
}


long long nHk(long long n, long long k) {
    long long m = n + k - 1;
    return nCk(m, k);
}
