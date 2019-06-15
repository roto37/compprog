//累積xor O(1) (累積和と違って前計算もいらないので空間計算量はO(1))
//sum_xor(n) = 0^1^2^3^...^n
//任意の位置からの累積xorもok
//A^(A+1)^....B = {B^(B-1)^...^1^0} ^ {(A-1)^(A-2)^...^1^0}
//              = sum_xor(B) ^ sum_xor(A-1)
//             (A = 0の時はsum_xor(B)が答え)

ll sum_xor(int x) {
    if (x % 4 == 0) return x;
    if (x % 4 == 1) return 1;
    if (x % 4 == 2) return x+1;
    if (x % 4 == 3) return 0;
}
