//最大長方形面積
//O[h * w]
//grid[i][j]が1のときそのマスは使えない。
//grid[i][j]が0のときそのマスが使える。

int h, w;
vector<vector<int>> grid(2005, vector<int>(2005));

struct Rectangle {int height, pos;};

int largest_hist(int size, vector<int> &hist) {
    stack<Rectangle> s;
    int maxv = 0;
    hist[size] = 0;

    for (int i = 0; i <= size ; i++) {
        Rectangle rect;
        rect.height = hist[i];
        rect.pos = i;

        if (s.empty()) {
            s.push(rect);
        }
        else {
            if (s.top().height < rect.height) s.push(rect);
            else if (s.top().height > rect.height) {
                int target = i;
                while (!s.empty() && s.top().height >= rect.height) {
                    Rectangle pre = s.top(); s.pop();
                    int area = pre.height * (i - pre.pos);
                    maxv = max(maxv, area);
                    target = pre.pos;
                }
                rect.pos = target;
                s.push(rect);
            }
        }
    }
    return maxv;
}

int largest_rect(int h, int w, vector<vector<int>> &grid) {
    vector<vector<int>> hist(h, vector<int>(w + 1));
    for (int j = 0; j < w; j++) {
        for (int i = 0; i < h; i++) {
            if (grid[i][j] == 1) {
                hist[i][j] = 0;
            }
            else {
                hist[i][j] = (i > 0) ? hist[i - 1][j] + 1 : 1;
            }
        }
    }

    int ret = 0;
    for (int i = 0; i < h; i++) {
        ret = max(ret, largest_hist(w, hist[i]));
    }
    return ret;
}

-----------------------------------------------------------------------
signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> h >> w;
    rep(i, h)rep(j, w) cin >> grid[i][j];
    cout << largest_rect(h - 1, w - 1, grid) << endl;
}
