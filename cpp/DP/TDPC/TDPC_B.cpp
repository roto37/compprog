//---------------------------------------------------------------
//解法1
//これが最も直観的だが実装量がやや増える
int n, m;
int a[1005], b[1005];
pair<int, int> dp[1005][1005]
/*
dp[l][r] := 今、山aの一番上がl番目(0-indexed), 山bの一番上がr番目(0-indexed)で残っている
ときでその状態から山がなくなる(ゲームが終了する)まで考えたときの
{snuke_scoreのmax, smeke_scoreのmax}
*/
/*
turn : snuke
    snukeは自分のscoreの最大化を目指すから今の状態からとりうるscoreの
    最大を選ぶ
    つまり
    max(dfs(l + 1, r, turn^1).fi + a[l], dfs(l, r + 1, turn^1).fi + b[r])
    を選ぶ
turn : smeke
    smekeは自分のscoreの最大化を目指すから今の状態からとりうるscoreの
    最大を選ぶ
    つまり
    max(dfs(l + 1, r, turn^1).se + a[l], dfs(l, r + 1, turn^1).se + b[r])
    を選ぶ
*/

pair<int, int> dfs(int l, int r, int tr) {
    if (l == n && r == m) return {0, 0};
    if (dp[l][r].fi != -1 && dp[l][r].se != -1) return dp[l][r];
    int tmp;
    if (tr == 0) {
        if (l == n) {
            pii p = dfs(l, r + 1, tr^1);
            return dp[l][r] = {p.fi + b[r], p.se};
        }
        else if (r == m) {
            pii p = dfs(l + 1, r, tr^1);
            return dp[l][r] = {p.fi + a[l], p.se};
        }
        else {
            pii p1 = dfs(l, r + 1, tr^1);
            pii p2 = dfs(l + 1, r, tr^1);
            if (p2.fi + a[l] >= p1.fi + b[r]) {
                return dp[l][r] = {p2.fi + a[l], p2.se};
            }
            else {
                return dp[l][r] = {p1.fi + b[r], p1.se};
            }
        }
    }
    else {
        if (l == n) {
            pii p = dfs(l, r + 1, tr^1);
            return dp[l][r] = {p.fi, p.se + b[r]};
        }
        else if (r == m) {
            pii p = dfs(l + 1, r , tr^1);
            return dp[l][r] = {p.fi, p.se + a[l]};
        }
        else {
            pii p1 = dfs(l, r + 1, tr^1);
            pii p2 = dfs(l + 1, r, tr^1);
            if (p1.se + b[r] >= p2.se + a[l]) {
                return dp[l][r] = {p1.fi, p1.se + b[r]};
            }
            else {
                return dp[l][r] = {p2.fi, p2.se + a[l]};
            }
        }
    }
}

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    rep(i, n) cin >> a[i];
    rep(i, m) cin >> b[i];
    rep(i, n + 1)rep(j, m + 1) dp[i][j] = {-1, -1};
    cout << dfs(0, 0, 0).fi << endl;
}
//---------------------------------------------------------------
//解法2
//dpは自然な設定だが更新のときにsmekeのほうでは値を加えないので注意
int n, m;
int a[1005], b[1005];
int dp[1005][1005];
//dp[l][r] := snuke_scoreのmax
/*
turn : snuke
    snukeは自分のscoreの最大化を目指す。
    よって今の状態から最も大きいscoreになるようなものを選ぶ
    dp[l][r] = max(dfs(l + 1, r, turn^1) + a[l], dfs(l, r + 1, turn^1) + b[r])
turn : smeke
    今の状態からゲームが終了するまでのsnuke_score + smeke_scoreは二人が
    どんな取り方をしても今、残っているカードに書かれている数字の総和となる
    またsmekeも自分のscoreの最大化を目指すことから今の状態からsnuke_scoreが
    最小となるような状態をとるのが最適。
    dp[l][r] = min(dfs(l + 1, r, turn^1), dfs(l, r + 1, turn^1))
    (dpはsnuke_scoreなのでcardの数字を足さないことに注意)
*/

int dfs(int l, int r, int tr) {
    if (l == n && r == m) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    int tmp;
    if (tr == 0) {
        if (l == n) {
            tmp = dfs(l, r + 1, tr^1) + b[r];
        }
        else if (r == m) {
            tmp = dfs(l + 1, r, tr^1) + a[l];
        }
        else {
            tmp = dfs(l + 1, r, tr^1) + a[l];
            tmp = max(tmp, dfs(l, r + 1, tr^1) + b[r]);
        }
    }
    else {
        if (l == n) {
            tmp = dfs(l, r + 1, tr^1);
        }
        else if (r == m) {
            tmp = dfs(l + 1, r, tr^1);
        }
        else {
            tmp = dfs(l + 1, r, tr^1);
            tmp = min(tmp, dfs(l, r + 1, tr^1));
        }
    }
    return dp[l][r] = tmp;
}

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    rep(i, n) cin >> a[i];
    rep(i, m) cin >> b[i];
    rep(i, n + 1)rep(j, m + 1) dp[i][j] = -1;
    cout << dfs(0, 0, 0) << endl;
}

//---------------------------------------------------------------
//解法3
//解法2のsmekeに値を加えるversionみたいな感じ。だからdpも当然変わる。
int n, m;
int a[1005], b[1005];
int dp[1005][1005];
//dp[l][r] := max(snukeのscore - smekeのscore)
/*
snuke_score + smeke_score = const - ①
turn : snuke
    snuke_scoreのmaxを目指す
    これはdpであるsnuke_score - smeke_scoreにおいて
    ①より
    snuke_score - smeke_score = snuke_score - (const - snuke_score)
                              = 2 * snuke_score - const
    ∴snuke_score = ((snuke_score - smeke_score) + const) / 2
    という関係にあるため結局
    snuke_scoreのmaxをとる <=> snuke_score - smeke_scoreの"max"をとる
    といえる
turn : smeke
    smeke_scoreのmaxを目指す
    先ほどと同様に考える
    snuke_score - smeke_score =  (const - smeke_score) - smeke_score
                              = const - 2 * smeke_score
    ∴smeke_score = (-(snuke_score + smeke_score) + const) / 2
    よって
    smeke_scoreのmaxをとる <=> snuke_score - smeke_scoreの"min"をとる
*/


int dfs(int l, int r, int turn) {
    if (l == n && r == m) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    //turn:0->snuke, 1->smeke
    int score;
    if (turn == 0) {
        if (l == n) {
            score = dfs(l, r + 1, turn^1) + b[r];
        }
        else if (r == m) {
            score = dfs(l + 1, r, turn^1) + a[l];
        }
        else {
            score = dfs(l, r + 1, turn^1) + b[r];
            score = max(score, dfs(l + 1, r, turn^1) + a[l]);
        }
    }
    else {
        if (l == n) {
            score = dfs(l , r + 1, turn^1) - b[r];
        }
        else if (r == m) {
            score = dfs(l + 1, r, turn^1) - a[l];
        }
        else {
            score = dfs(l, r + 1, turn^1) - b[r];
            score = min(score, dfs(l + 1, r, turn^1) - a[l]);
        }
    }
    return dp[l][r] = score;
}

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int sum = 0;
    rep(i, n) {
        cin >> a[i];
        sum += a[i];
    }
    rep(i, m) {
        cin >> b[i];
        sum += b[i];
    }
    rep(i, n + 1)rep(j, m + 1) dp[i][j] = -1;
    cout << (sum + dfs(0, 0, 0)) / 2 << endl;
}
