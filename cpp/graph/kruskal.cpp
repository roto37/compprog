#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(a) (a).begin(),(a).end()

//UnionFindは0-indexed!!!!!!!!!!!!!!!!!!!
class UnionFind{
    public:
        vector<int> parent, rank, tree_w;
        int tree_num;
        UnionFind(int size){
            tree_num = size;
            for (int i = 0; i < size; i++){
                parent.push_back(i);
                rank.push_back(0);
                tree_w.push_back(1);
            }
        }

        int findset(int x){
            return x == parent[x] ? x : parent[x] = findset(parent[x]);
        }

        void unite(int x, int y){
            x = findset(x); y = findset(y);
            if (x == y) return;
            if (rank[x] > rank[y]) swap(x, y);
            parent[x] = y;
            tree_num -= 1;
            tree_w[y] += tree_w[x];
            if (rank[x] == rank[y]) rank[y] += 1;
        }

        bool same(int x, int y){
            return findset(x) == findset(y);
        }

        int tree_number(){
            return tree_num;
        }

        int tree_weight(int x){
            return tree_w[findset(x)];
        }
};

struct edge {ll cost,u,v;};
bool comp(const edge& e1, const edge& e2) {
    return e1.cost < e2.cost;
}

vector<edge> es;

ll kruskal(int v, int e, vector<edge> es) {//vは頂点数,eは辺数
    sort(all(es), comp);   //esは[辺の重み,辺の端点1,辺の端点2]
    UnionFind node(v);
    ll ret = 0;
    for (int i = 0; i < e; i++) {
        edge e = es[i];
        if (!node.same(e.u, e.v)) {
            ret += e.cost;
            node.unite(e.u, e.v);
        }
    }
    return ret;
}

int main(){

}
