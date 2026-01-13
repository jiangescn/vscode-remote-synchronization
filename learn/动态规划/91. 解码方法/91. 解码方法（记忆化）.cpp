//https://leetcode.cn/problems/decode-ways/description/
#include <bits/stdc++.h>
using namespace std;
string s;
vector<int> dp;
int len;

int f(int i)
{
    if(i == len)
    {
        return 1;
    }
    if(s[i] == '0')
    {
        return 0;
    }
    if(dp[i] != -1)
    {
        return dp[i];
    }
    int ans = f(i + 1);
    if(i + 1 < len && (s[i] - '0') * 10 + s[i + 1] - '0' <= 26)
    {
        ans += f(i + 2);
    }

    dp[i] = ans;
    return ans;
}

int main()
{
    cin >> s;
    len  = s.size();
    dp.resize(len, -1);
    cout << f(0) << endl;
}