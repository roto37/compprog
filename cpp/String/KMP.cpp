//KMP法(?), MP法って名前かもしれない
//O[n + m] (n = |text|, m = |pt|)
//text内の部分文字列でptと一致するものの開始位置の集合をvector<int>で返す
//下に解説
//-----------------------------------------------------------------
vector<int> KMPTable(const string &pt) {
    int m = pt.size();
    vector<int> nx(m + 1, -1);
    int j = -1;
    for (int i = 0; i < m; i++) {
        while (j >= 0 && pt[i] != pt[j]) {
            j = nx[j];
        }
        j += 1;
        nx[i + 1] = j;
    }
    return nx;
}

vector<int> KMPSearch (const string &text, const string &pt) {
    int n = text.size(), m = pt.size();
    int start = 0;
    int pt_idx = 0;
    vector<int> ret;
    vector<int> nx = KMPTable(pt);
    while (start + pt_idx < n) {
        if (text[start + pt_idx] == pt[pt_idx]) {
            pt_idx++;
            if (pt_idx == m) {
                ret.push_back(start);
                start = start + (pt_idx - nx[pt_idx]);
                pt_idx = nx[pt_idx];
            }
        }
        else {
            if (pt_idx == 0) start++;
            else {
                start = start + (pt_idx - nx[pt_idx]);
                pt_idx = nx[pt_idx];
            }
        }
    }
    return ret;
}
//------------------------------------------------------------

string t;
string p;

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> t >> p;
    vector<int> ans = KMPSearch(t, p);
    int size = ans.size();
    for (int i = 0; i < size; i++) cout << ans[i] << endl;
}

//--------------------------------------------------------------
//解説
//KMPTableはO[m]
//(stackをイメージすると良い(j++がstackに積むとき、while内がstackから取り出すとき))

vector<int> KMPTable(const string &pt) {
    int m = pt.size();
    vector<int> nx(m + 1, -1);     //nx[i]:=pt[0:i)の最大共通接頭,尾辞数
    int j = -1;
    for (int i = 0; i < m; i++) {
        while (j >= 0 && pt[i] != pt[j]) {
            j = nx[j];
        }
        j += 1;
        nx[i + 1] = j;
    }
    return nx;
}
//KMPSearchはO[n + m]
vector<int> KMPSearch (const string &text, const string &pt) {
    int n = text.size(), m = pt.size();
    int start = 0;        //textにおける文字列照合の開始位置(0-indexed)
    int pt_idx = 0;       //今照合しているptのindex(0-indexed)
    vector<int> ret;      //ptがあった時のtextのstart位置を記録
    vector<int> nx = KMPTable(pt); //一致しなかった時の次の検索開始位置が記録されている
    while (start + pt_idx < n) {                  //→(最大共通接頭尾辞の接尾辞)
        if (text[start + pt_idx] == pt[pt_idx]) {
            pt_idx++;
            if (pt_idx == m) {            //ptと一致するものがあった!
                ret.push_back(start);
                start = start + (pt_idx - nx[pt_idx]);
                pt_idx = nx[pt_idx];
            }
        }
        else {
            if (pt_idx == 0) start++;      //最初の文字から一致しなかった
            else {                         //途中で一致しなかった
                start = start + (pt_idx - nx[pt_idx]);
                pt_idx = nx[pt_idx];
            }
        }
    }
    return ret;
}
