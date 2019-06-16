#include <bits/stdc++.h>
using namespace std;

//Range Minimum Query (struct ver)

struct segtree {
    int size;
    vector<long long> node;

    segtree (int n) : size(1) {
        while (size < n) size *= 2;
        node.resize(2 * size - 1, INFLL / 2);
    }

    void update(int k, int a) {
        k += size - 1;
        node[k] = a;
        while (k > 0){
            k = (k - 1) / 2;
            node[k] = min(node[2 * k + 1], node[2 * k + 2]);
        }
    }
    //[queryL: queryR)
    long long get(int queryL, int queryR, int k = 0, int nodeL = 0, int nodeR = -1) {
        if (nodeR == -1) nodeR = size;
        if (nodeR <= queryL || queryR <= nodeL) return INFLL;//初期値より大きく
        if (queryL <= nodeL && nodeR <= queryR) return node[k];
        else{
            int nodeM = (nodeL + nodeR) / 2;
            long long vl = get(queryL, queryR, 2 * k + 1, nodeL, nodeM);
            long long vr = get(queryL, queryR, 2 * k + 2, nodeM, nodeR);
            return min(vl, vr);
        }
    }
};
----------------------------------------------------------------------------
//Range Maximum Query (struct ver)

struct segtree {
    int size;
    vector<long long> node;

    segtree (int n) : size(1) {
        while (size < n) size *= 2;
        node.resize(2 * size - 1, -INFLL / 2);
    }

    void update(int k, int a) {
        k += size - 1;
        node[k] = a;
        while (k > 0){
            k = (k - 1) / 2;
            node[k] = max(node[2 * k + 1], node[2 * k + 2]);
        }
    }
    //[queryL: queryR)
    long long get(int queryL, int queryR, int k = 0, int nodeL = 0, int nodeR = -1) {
        if (nodeR == -1) nodeR = size;
        if (nodeR <= queryL || queryR <= nodeL) return -INFLL; //初期値より小さく
        if (queryL <= nodeL && nodeR <= queryR) return node[k];
        else{
            int nodeM = (nodeL + nodeR) / 2;
            long long vl = get(queryL, queryR, 2 * k + 1, nodeL, nodeM);
            long long vr = get(queryL, queryR, 2 * k + 2, nodeM, nodeR);
            return max(vl, vr);
        }
    }
};

-----------------------------------------------------------------------------------
//使い方
int n, q;

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n;
    segtree seg(n);
    cin >> q;
    rep(i, q) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0) seg.update(x, y);
        else {
            cout << seg.get(x, y + 1) << endl;
        }
    }
}
------------------------------------------------------------------------------------
//Range Maximun Query (関数セグ木ver)
//node1, node2...と作ることがseg1, seg2...のように複数のセグ木を作ることに対応
//グローバル変数↓

int size;
vector<int> node1((1 << 19) - 1);
vector<int> node2((1 << 19) - 1);

void init(int n_, vector<int>& node) {
    size = 1;
    while (size < n_) size *= 2;
    for (int i = 0; i < 2 * size - 1; i++) node[i] = -INT_MAX;
}

void update(int k, int a, vector<int>& node) {
    k += size - 1;
    node[k] = a;
    while (k > 0){
        k = (k - 1) / 2;
        node[k] = max(node[2 * k + 1], node[2 * k + 2]);
    }
}

int get_max(int queryL, int queryR, vector<int>& node, int k = 0, int nodeL = 0, int nodeR = -1) {
    if (nodeR == -1) nodeR = size;
    if (nodeR <= queryL || queryR <= nodeL) return -INT_MAX;
    if (queryL <= nodeL && nodeR <= queryR) return node[k];
    else{
        int nodeM = (nodeL + nodeR) / 2;
        int vl = get_max(queryL, queryR, node, 2 * k + 1, nodeL, nodeM);
        int vr = get_max(queryL, queryR, node, 2 * k + 2, nodeM, nodeR);
        return max(vl, vr);
    }
}
------------------------------------------------------------------------------------
//最小値と最小値のあるnodeのpos(0-indexed)を得ることができるセグ木

int size;
vector<int> node1((1 << 19) - 1);
vector<int> pos1((1 << 19) - 1);
vector<int> node2((1 << 19) - 1);
vector<int> pos2((1 << 19) - 1);

void init(int n_, vector<int>& node, vector<int>& pos) {
    size = 1;
    while (size < n_) size *= 2;
    for (int i = 0; i < 2 * size - 1; i++) node[i] = INT_MAX;
    for (int i = size - 1; i < 2 * size - 1; i++) pos[i] = i - (size - 1);
}

void update(int k, int a, vector<int>& node, vector<int>& pos) {
    k += size - 1;
    node[k] = a;
    while (k > 0){
        k = (k - 1) / 2;
        if (node[2 * k + 1] < node[2 * k + 2]) {
            node[k] = node[2 * k + 1];
            pos[k] = pos[2 * k + 1];
        }
        else {
            node[k] = node[2 * k + 2];
            pos[k] = pos[2 * k + 2];
        }
    }
}

pair<int, int> get_min(int queryL, int queryR, vector<int>& node, vector<int>& pos, int k = 0, int nodeL = 0, int nodeR = -1) {
    if (nodeR == -1) nodeR = size;
    if (nodeR <= queryL || queryR <= nodeL) return make_pair(INT_MAX, INT_MAX);
    if (queryL <= nodeL && nodeR <= queryR) return make_pair(node[k], pos[k]);
    else{
        int nodeM = (nodeL + nodeR) / 2;
        pair<int, int> vl = get_min(queryL, queryR, node, pos, 2 * k + 1, nodeL, nodeM);
        pair<int, int> vr = get_min(queryL, queryR, node, pos, 2 * k + 2, nodeM, nodeR);
        int val = INT_MAX; int min_pos = INT_MAX;
        if (vl.fi < vr.fi) {val = vl.fi; min_pos = vl.se;}
        else {val = vr.fi; min_pos = vr.se;}
        return make_pair(val, min_pos);
    }
}
-------------------------------------------------------------------------------
//最大値と最大値のあるnodeのpos(0-indexed)を得ることができるセグ木
int size;
vector<int> node1((1 << 19) - 1);
vector<int> pos1((1 << 19) - 1);
vector<int> node2((1 << 19) - 1);
vector<int> pos2((1 << 19) - 1);

void init(int n_, vector<int>& node, vector<int>& pos) {
    size = 1;
    while (size < n_) size *= 2;
    for (int i = 0; i < 2 * size - 1; i++) node[i] = -INT_MAX;
    for (int i = size - 1; i < 2 * size - 1; i++) pos[i] = i - (size - 1);
}

void update(int k, int a, vector<int>& node, vector<int>& pos) {
    k += size - 1;
    node[k] = a;
    while (k > 0){
        k = (k - 1) / 2;
        if (node[2 * k + 1] > node[2 * k + 2]) {
            node[k] = node[2 * k + 1];
            pos[k] = pos[2 * k + 1];
        }
        else {
            node[k] = node[2 * k + 2];
            pos[k] = pos[2 * k + 2];
        }
    }
}

pair<int, int> get_max(int queryL, int queryR, vector<int>& node, vector<int>& pos, int k = 0, int nodeL = 0, int nodeR = -1) {
    if (nodeR == -1) nodeR = size;
    if (nodeR <= queryL || queryR <= nodeL) return make_pair(-INT_MAX, -INT_MAX);
    if (queryL <= nodeL && nodeR <= queryR) return make_pair(node[k], pos[k]);
    else{
        int nodeM = (nodeL + nodeR) / 2;
        pair<int, int> vl = get_max(queryL, queryR, node, pos, 2 * k + 1, nodeL, nodeM);
        pair<int, int> vr = get_max(queryL, queryR, node, pos, 2 * k + 2, nodeM, nodeR);
        int val = -INT_MAX; int max_pos = -INT_MAX;
        if (vl.fi > vr.fi) {val = vl.fi; max_pos = vl.se;}
        else {val = vr.fi; max_pos = vr.se;}
        return make_pair(val, max_pos);
    }
}
--------------------------------------------------------------------------------------
//Range Minimum Query(クラスver)
//class内ではあまり大きなメモリを確保できない(1<<18でセグフォる)

class segtree{
    public:
        int size;
        int node[(1<<17)-1];
        segtree(int n_){
            size=1;
            while (size<n_) size*=2;
            for (int i=0; i<2*size-1; i++) node[i]=INT_MAX;
        }

        void update(int k,int a){
            k+=size-1;
            node[k]=a;
            while (k>0){
                k=(k-1)/2;
                node[k]=min(node[2*k+1],node[2*k+2]);
            }
        }

        int get_min(int queryL,int queryR,int k=0,int nodeL=0,int nodeR=-1){
            if (nodeR==-1) nodeR=size;
            if (nodeR<=queryL or queryR<=nodeL) return INT_MAX;
            if (queryL<=nodeL and nodeR<=queryR) return node[k];
            else{
                int nodeM=(nodeL+nodeR)/2;
                int vl=get_min(queryL,queryR,k*2+1,nodeL,nodeM);
                int vr=get_min(queryL,queryR,k*2+2,nodeM,nodeR);
                return min(vl,vr);
            }
        }
};

------------------------------------------------------------------------
//Range Maximun Query
class segtree{
    public:
        int size;
        int node[(1<<17)-1];
        segtree(int n_){
            size=1;
            while (size<n_) size*=2;
            for (int i=0; i<2*size-1; i++) node[i]=INT_MIN;
        }

        void update(int k,int a){
            k+=size-1;
            node[k]=a;
            while (k>0){
                k=(k-1)/2;
                node[k]=max(node[2*k+1],node[2*k+2]);
            }
        }

        int get_max(int queryL,int queryR,int k=0,int nodeL=0,int nodeR=-1){
            if (nodeR==-1) nodeR=size;
            if (nodeR<=queryL or queryR<=nodeL) return INT_MIN;
            if (queryL<=nodeL and nodeR<=queryR) return node[k];
            else{
                int nodeM=(nodeL+nodeR)/2;
                int vl=get_max(queryL,queryR,k*2+1,nodeL,nodeM);
                int vr=get_max(queryL,queryR,k*2+2,nodeM,nodeR);
                return max(vl,vr);
            }
        }
};

int main(){
    segtree seg(100);
    seg.update(0,100);
    seg.update(10,3);
    seg.get_min(0,100);
    seg.get_max(9,10);

    return 0;
}
