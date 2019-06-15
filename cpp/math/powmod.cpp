n^kをO[logk]で求める

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
