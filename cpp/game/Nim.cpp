//Nimゲーム
//O[n]:nはpile(石の山)の個数
/*ゲーム概要
n個の石の積まれた山がある. 各山の石の数はc1, c2, ..., cn個である.
player1, player2がいる. player1から以下のゲームを交互におこなう.
・石が1つ以上存在する山を一つ選び, 一つ以上の石をその山から取り除く.
・石を一つも取れなくなった方の負け(最後の石をとった方の "勝ち" ).
両者が最適に行動したときどちらが勝つか.

[解法] c1^c2^...^cnの値が 0 => player2(Second), そうでなければ player1(First)

*/

#include <bits/stdc++.h>

void Nim(int n, vector<long long>& pile) {
	long long xor_sum = 0LL;
	for (int i = 0; i < n; i++) {
		xor_sum ^= pile[i];
	}
		if (xor_sum == 0) cout << "Second" << endl;
		else cout << "First"  << endl;
}
