#include <bits/stdc++.h>
using namespace std;

int binary_search(vector<int> &a, int target)
{
    int l = 0, r = (int)a.size() - 1; // [l, r]
    while (l <= r)
    {
        int m = l + (r - l) / 2; // 防止溢出
        if (a[m] == target)
            return m;
        else if (a[m] < target)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1; // 未找到
}

