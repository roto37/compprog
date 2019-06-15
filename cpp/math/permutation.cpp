//permutation
//O[n!]
//sort忘れない!
//next_permutation(v.begin(), v.end())は昇順で今の順列vの次の順列が生成できれば生成しtrueを返す
//できない場合=降順はfalseを返す
//do内でcontinueするとwhileの方へ行く.(普通のwhile文と同じふるまい)

vector<int> v = {2, 1, 3};
sort(v.begin(), v.end());
do {
  for (auto x : v) {
    cout << x << " ";
  }
  cout << endl;
} while( next_permutation(v.begin(), v.end()) );

/*
実行結果(sortなし)
2 1 3
2 3 1
3 1 2
3 2 1

*/
/*
実行結果(sortあり)
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
*/
