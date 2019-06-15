//nCk自体はO[log(mod)](inv_factを前計算しておけば、O[1])だがfactの前計算にO[n]
//powmod(繰り返し二乗法)はmin(O[log(mod)])
//フェルマーの小定理を用いると1/a = a^(p-2) (mod p)(p:素数)
//つまり1/aのmod pを計算したいときはa^(p－2)のmod pを代わりに計算すればよい

vector<long long> fact(200000 + 5, 1);

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
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    return fact;
}

long long nCk(long long n, long long k) {
    if (n - k < k) k = n - k;
    return fact[n] * (inverse(fact[n - k]) * inverse(fact[k]) % mod) % mod;
}
