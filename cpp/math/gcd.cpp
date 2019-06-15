//a,bの最大公約数を求める
long long  gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
//a,bの最小公倍数を求める
long long lcm(long long a, long long b) {
    long long g = gcd(a, b);
    return a / g * b;
}
