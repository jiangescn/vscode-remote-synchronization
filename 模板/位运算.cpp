#include <bits/stdc++.h>
using namespace std;
#define int long long

int popcnt(long long x)
{
    return __builtin_popcountll(x);
}

int lowbit_pos(long long x)
{
    // x 不能为 0
    return __builtin_ctzll(x);
}

int highbit_pos(long long x)
{
    // x 不能为 0
    return 63 - __builtin_clzll(x);
}

int bit_length(long long x)
{
    // x 不能为 0
    return 64 - __builtin_clzll(x);
}

bool is_power_of_two(long long x)
{
    return x > 0 && (x & (x - 1)) == 0;
}

signed main()
{
    long long x = 40;

    cout << "x = " << x << endl;
    cout << "1 的数量: " << popcnt(x) << endl;
    cout << "最低位 1 的位置: " << lowbit_pos(x) << endl;
    cout << "最高位 1 的位置: " << highbit_pos(x) << endl;
    cout << "二进制长度: " << bit_length(x) << endl;
    cout << "是否是 2 的幂: " << is_power_of_two(x) << endl;

    return 0;
}