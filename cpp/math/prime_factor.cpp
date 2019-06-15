map<int, int> primefactor(int x) {
    map<int, int> fac;
    for (int i = 2; i * i <= x; i++){
        while (x % i == 0) {
            fac[i]++;
            x = x / i;
        }
    }
    if (x != 1) fac[x] += 1;
    return fac;
}

----------------------------
int m = 100;
rep2(i, 1, m + 1) {
    map<int, int> f = primefactor(i);
    for (auto mp : f) {
        cout << mp.fi << ':' << mp.se << endl;
    }
    cout << "---------------" << endl;
}
