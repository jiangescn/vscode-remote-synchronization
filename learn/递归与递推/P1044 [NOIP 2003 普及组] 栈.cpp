#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define int long long
int n;
int memo[200][200];

int f(int pushed, int st)
{
    int ans = 0;
    if (pushed == n && st == 0)
    {
        return 1;
    }

    if(memo[pushed][st] != -1)
    {
        return memo[pushed][st];
    }

    if (pushed < n)
    {
        ans += f(pushed + 1, st + 1);
    }

    if (st > 0)
    {
        ans += f(pushed, st - 1);
    }
    
    memo[pushed][st] = ans;
    return ans;
}

signed main()
{
    cin >> n;
    memset(memo, -1, sizeof(memo));

    int ans = f(0, 0);
    cout << ans << endl;
}