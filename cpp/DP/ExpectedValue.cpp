//条件付き期待値dp(最適に行動したときの最小値(最大でもいける?))

//now:今の状態
//prob[now][nx]:=状態nowから状態nxに遷移するときの確率
//cost[now][nx]:=状態nowから状態nxに遷移するときのコスト

double dfs(int now) {
    if (dp[now] != 初期値) return dp[now];
    for (int i = 0: i < 次に選択できる行動数; i++) {
        double expected_value = 0;              //ある行動をとった時の期待値
        double same = 1;                       //左辺の係数
        int cnt = 0;
        for (auto nx : i番目の行動におけるnowからの次の遷移集合) {
            if (now == nx) {
                cnt++;
                expected_value += cost[now][nx] * prob[now][nx];
                same -= prob[now][nx];  //遷移しても今と同じ状態のとき左辺に移項するので引いておく
            }
            else {
                expected_value += (dfs(nx) + cost[now][nx]) * prob[now][nx];
            }
        }
        if (cnt == nowからの次の遷移数) continue; //ある行動とったときすべての遷移で変化がないので明らかに最適ではない
    }                                          //この時same0だが誤差があるのでcntで数えるのが安全
    dp[now] = min(dp[now], expected_value / same);
    return dp[now];
}
