//行列累乗
//O[m^3logn](正方行列(m x m)のn乗)

mat mul(mat &A, mat &B, int mod) {
    mat C(A.size(), vector<int> (B[0].size()));
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < B.size(); k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return C;
}

mat pow(mat &A, long long n, int mod) {
    mat B(A.size(), vector<int> (A.size()));
    for (int i = 0; i < A.size(); i++) {
        B[i][i] = 1;
    }
    while (n > 0) {
        if (n & 1) B = mul(B, A, mod);
        A = mul(A, A, mod);
        n >>= 1;
    }
    return B;
}
