//BITは1-indexed
//                 """add, sum, range_sumのi, l, rもすべて1-indexed!!!!!!"""
//sumは[1:i]の総和(segtreeと違って閉区間)
//range_sumは[l:r]の総和
//bisect_leftはBIT内でx番目に小さい数字のindex(1-indexed)を返す
    //->これを使うときはBITのnodeは0, 1でなければならない。
    //nodeの値がxであるindexがx番目に大きい数値であると考えているため。
    //従ってnodeのindexを実際の数値と考えて、その場所を0, 1とすることで数値の存在のなし、あるを
    //表現し、またx番目に小さい数値も上述の判定で求めることができる。(ARC 033 データ構造)
-------------------------------------------------------------------------------------
//基本(struct ver)
struct BIT {
    int size;
    vector<int> node;

    BIT(int n, long long init_num) {
        size = n;
        node.resize(size + 1, init_num);
    }

    void add(int i, long long x) {
        while (i <= size) {
            node[i] += x;
            i += i & -i;
        }
    }

    long long sum(int i) {
        long long ret = 0;
        while (i > 0) {
            ret += node[i];
            i -= i & -i;
        }
        return ret;
    }
};
------------------------------------------------------------------------------
//追加
    long long range_sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    int bisect_left(int x) {
        if (x <= 0) return x;
        int ret = 0;
        int i = 1<<24;
        while (i > 0){
            if ((ret + i < size) && (node[ret + i] < x)) {
                ret += i;
                x -= node[ret];
            }
            i = i>>1;
        }
        return ret + 1;
    }
-------------------------------------------------------------------------------
//基本(class ver)
class BIT {
    public:
        int size;
        vector<int> node;

        BIT(int n, long long init_num) {
            size = n;
            for (int i = 0; i <= size; i++){
                node.pb(init_num);
            }
        }

        void add(int i, long long x) {
            while (i <= size) {
                node[i] += x;
                i += i & -i;
            }
        }

        long long sum(int i) {
            long long ret = 0;
            while (i > 0) {
                ret += node[i];
                i -= i & -i;
            }
            return ret;
        }

        long long range_sum(int l, int r) {
            return sum(r) - sum(l - 1);
        }

        int bisect_left(int x) {
            if (x <= 0) return x;
            int ret = 0;
            int i = 1<<24;
            while (i > 0){
                if ((ret + i < size) && (node[ret + i] < x)) {
                    ret += i;
                    x -= node[ret];
                }
                i = i>>1;
            }
            return ret + 1;
        }
};
