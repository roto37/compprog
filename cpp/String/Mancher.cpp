//回文半径(中心 + 半径)
//文字列sの各場所を中心とした場合の回文半径を求める。
//中心が二つの回文は求めていないので注意
//ex)aabaa -> radius[2] = 3 (baa)
//O[n] (n = |s|)


vector<int> Manacher(const string &s) {
    int n = s.size();
    int center = 0;
    int scope = 0;
    vector<int> radius(n);
    while (center < n) {
        while (center - scope >= 0 && center + scope < n && s[center - scope] == s[center + scope]) {
            scope += 1;
        }
        radius[center] = scope;
        int nx = 1;
        while (center - nx >= 0 && center + nx < n && nx + radius[center - nx] < scope) {
            radius[center + nx] = radius[center - nx];
            nx++;
        }
        center += nx;
        scope -= nx;
    }
    return radius;
}
//---------------------------------------------------------------------------
//解説
vector<int> Manacher(const string &s) {
    int n = s.size();
    int center = 0;
    int scope = 0;
    vector<int> radius(n);
    while (center < n) {
        //左右同時にscopeを1つずつ伸ばしていく
        while (center - scope >= 0 && center + scope < n && s[center - scope] == s[center + scope]) {
            scope += 1;
        }
        radius[center] = scope;
        int nx = 1;
        //回文であることを利用する。scope内ではcenter + nxとcenter - nxは同じであり
        //nx + radius[center - nx]がscopeからはみ出さない限り
        //radius[center + nx] = radius[center - nx]が成立する。
        while (center - nx >= 0 && center + nx < n && nx + radius[center - nx] < scope) {
            radius[center + nx] = radius[center - nx];
            nx++;
        }
        center += nx;
        scope -= nx;
    }
    return radius;
}
