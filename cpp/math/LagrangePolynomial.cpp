/*
ラグランジュ補間による多項式pn(x)にx=aとしたときの値を求める。
O[n^2]

ラグランジュ補間とは
既知のすべて異なるn + 1個のデータ x0, x1, ..., xnとその値 f0, f1, ..., fn
を用いてn次多項式pn(x)を求めることである。 

pn(x) = Σ f(xi) * L(n, xi)
         0≦i≦n
L(n, xi) = Π (x - xk) / (xi - xk)
        (0≦k≦n, k ≠ i) 
*/
#include <bits/stdc++.h>

double Lagrange_polynomial (int n, double a,  vector<double>& x, vector<double>& fx) {
    double ret = 0;
    for (int i = 0; i < n; i++) {
        double L = 1;
        for (int k = 0; k < n; k++) {
            if (i == k) continue;
            L *= (a - x[k]) / (x[i] - x[k]);
        }
        ret += fx[i] * L;
        cout << ret << endl;
    }
    return ret;
}