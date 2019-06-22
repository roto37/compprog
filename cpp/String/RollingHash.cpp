//ローリングハッシュ
//文字列aがbに含まれるか
//O[n + m] (n = |text(b)|, m = |pt(a)|)

const ull B = 1e9 + 7;

bool contain(string a, string b) {
    int m = a.length(), n = b.length();
    if (m > n) return false;

    ull t = 1;
    for (int i = 0; i < m; i++) t *= BASE;

    ull ah = 0, bh = 0;
    for (int i = 0; i < m; i++) ah = ah * BASE + a[i];
    for (int i = 0; i < m; i++) bh = bh * BASE + b[i];

    for (int i = 0; i + m <= n; i++) {
        if (ah == bh) return true;
        if(i + m < n) bh = bh * BASE - b[i] * t + b[i + m];
    }
    return false;
}
//----------------------------------------------------
//これが最も汎用的
//構築O[n] (n = |text|)
//hs[i] := s[0:i)のハッシュ値
//baseとmodを2つ用意したver(long longになっている)

struct RollingHash {

  ll base1, base2;
  ll mod1, mod2;
  vector<ull> hash1, hash2;
  vector<ull> pow1, pow2;

  RollingHash() : base1(1009), base2(1007), mod1(999999937), mod2(1000000000 + 7) {}

  void init(const string &s) {
    int n = s.size();

    hash1.assign(n + 1, 0);
    hash2.assign(n + 1, 0);
    pow1.assign(n + 1, 1);
    pow2.assign(n + 1, 1);

    for (int i = 0; i < n; i++) {
      hash1[i + 1] = (hash1[i] + s[i]) * base1 % mod1;
      hash2[i + 1] = (hash2[i] + s[i]) * base2 % mod2;
      pow1[i + 1] = pow1[i] * base1 % mod1;
      pow2[i + 1] = pow2[i] * base2 % mod2;
    }
  }
  //[l, r) (0-indexed)
  pll get(int l, int r) {
    ll t1 = (hash1[r] - (hash1[l] * pow1[r - l]) % mod1 + mod1) % mod1;
    ll t2 = (hash2[r] - (hash2[l] * pow2[r - l]) % mod2 + mod2) % mod2;
    return make_pair(t1, t2);
  }

  bool match(int l1, int r1, int l2, int r2) {
    return get(l1, r1) == get(l2, r2) ? true : false;
  }
};

//----------------------------------------------------
//hs[i] := s[0:i)のハッシュ値
//O[n] (n = |s|)
//baseが一つでmod=2^64(unsigned long long)ver <------ これはやばい(衝突しやすい)!!

struct RollingHash {
    int n;
    ull BASE;
    vector<ull> hs;
    vector<ull> power;

    RollingHash(const string &s, ull b = 1000000007)
        : n(s.size()), hs(n + 1)
    {
        BASE = b;
        power.assign(n + 1, 1);
        for (int i = 0; i < n; i++) power[i + 1] = BASE * power[i];
        for (int i = 0; i < n; i++) hs[i + 1] = (hs[i] + s[i]) * BASE;
    }

    //[l, r) (0-indexed)
    ull get(int l, int r) {
        return hs[r] - (hs[l] * power[r - l]);
    }
};
----------------------------------------------------------
//
struct RollingHash
{
  vector <ull> hs, power;

  RollingHash(const string& s) {
    int sz = s.size();
    hs.assign(sz + 1, 0);
    power.assign(sz + 1, 0);

    power[0] = 1;
    for(int i = 0; i < sz; i++) {
      power[i + 1] = power[i] * BASE;
    }
    for(int i = 0; i < sz; i++) {
      hashed[i + 1] = (hs[i] + s[i]) * BASE;
    }
  }

  ull get(int l, int r) {
    return hs[r] - (hs[l] * power[r - l]);
  }

  ull connect(int h1, int h2, int h2len) {
    return h1 * power[h2len] + h2;
  }

  int LCP(RollingHash& b, int l1, int r1, int l2, int r2) {
    int len = min(r1 - l1, r2 - l2);
    int low = -1, high = len + 1;
    while(high - low > 1) {
      int mid = (low + high) / 2;
      if(get(l1, l1 + mid) == b.get(l2, l2 + mid)) low = mid;
      else high = mid;
    }
    return low;
  }
};
