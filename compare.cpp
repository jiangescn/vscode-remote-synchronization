#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

// 计算 x 的平方核：去掉所有平方因子后剩下的 square-free 部分
long long square_free_kernel(long long x) {
    long long s = 1;
    for (long long p = 2; p * p <= x; ++p) {
        if (x % p == 0) {
            int parity = 0; // 记录指数奇偶
            while (x % p == 0) {
                x /= p;
                parity ^= 1;
            }
            if (parity) s *= p; // 奇次幂保留一个 p
        }
    }
    if (x > 1) s *= x; // 剩下的质因子指数为 1
    return s;
}

// 安全的整型向上除法 ceil(a / b)，假设 b > 0
long long ceil_div(long long a, long long b) {
    return (a + b - 1) / b;
}

// 整数平方根向上取整：返回最小的 k，使得 k^2 >= n（n >= 0）
long long ceil_sqrt(long long n) {
    if (n <= 0) return 0;
    long long k = sqrtl((long double)n);
    while (k * k < n) ++k;
    while ((k - 1) >= 0 && (k - 1) * (k - 1) >= n) --k;
    return k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x, l, r;
    if (!(cin >> x >> l >> r)) return 0;

    long long s = square_free_kernel(x);

    // 在 [ceil(l/s), floor(r/s)] 内找一个平方数 q = k^2
    long long qL = (s == 0 ? 0 : ceil_div(l, s));
    long long qR = (s == 0 ? -1 : r / s); // s>=1 本题下不会为 0

    if (qL > qR) {
        cout << -1 << "\n";
        return 0;
    }

    long long k = ceil_sqrt(qL);
    if (k * k <= qR) {
        long long y = s * (k * k);
        cout << y << "\n";
    } else {
        cout << -1 << "\n";
    }
    return 0;
}
``