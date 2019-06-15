//O[√n]

vector<int> divisor(int n){
    vector<int> div;
    for (int i=1; i*i<=n; i++){
        if (n%i==0){
            div.push_back(i);
            if (i!=n/i) div.push_back(n/i);
        }
    }
    return div;
}

int div_cnt(int n){
    int cnt=0;
    for (int i=1; i*i<=n; i++){
        if (n%i==0){
            cnt++;
            if (i!=n/i) cnt++;
        }
    }
    return cnt;
}
