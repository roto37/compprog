//エラトステネスの篩
//O[n * loglogn]
//アルゴリズム
/*まず0~nまですべて列挙する
0, 1は素数でないのでfalse
この後は2から順に小さい値を見ていき、次の①, ②を繰り返す(nまで)
① is_prime[i] = trueなら i は素数であり、②に行く。そうでないなら i+=1 して①に戻る。

(∵小さいものからみているのでis_prime[i]がtrueなら
i は [1, 2, 3...i-1] の倍数でない(②の操作からわかる)、つまり i は [1, 2, 3...i - 1] を約数にもたないため.
あと当然 i は [i +1, ...n] の数字で約数を持たないため.)

② 2i, 3i, 4i...はすべて合成数なので is_prime[2*i], is_prime[3 * i]...をfalseにしていく。i+=1して①に戻る
*/

//--------->nまでの素数の数は大体n/10個<---------------!!!!!!!!!!!!!
#include <bits/stdc++.h>


vector<bool> sieve(int n) {
	vector<bool> is_prime(n + 1, true);
	is_prime[0] = false;
	is_prime[1] = false;
	for (int i = 2;  i <= n; i++) {
		if (is_prime[i]) {
			for (int j = 2 * i; j <= n; j += i) {
				is_prime[j] = false;
			}
		}
	}
	return is_prime;
}
