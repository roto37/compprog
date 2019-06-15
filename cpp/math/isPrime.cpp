//O[√x] +2ずつ増やしているのでもうちょっと早い？

bool isPrime(ll x) {
    if (x == 2) return true;
    else if (x < 2 || x % 2 == 0) return false;
    else {
        for (int i = 3; i * i <= x; i += 2) {
            if (x % i == 0) return false;
        }
    }
    return true;
}
