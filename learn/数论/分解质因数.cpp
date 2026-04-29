#include <bits/stdc++.h>
using namespace std;


vector<pair<long long, int>> fct(int n)
{
    vector<pair<long long, int>> res;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int cnt = 0;
            while (n % i == 0)
            {
                n /= i;
                cnt++;
            }
            res.push_back({i, cnt});
        }
    }
    if (n > 1) res.push_back({n, 1});
    return res;
}