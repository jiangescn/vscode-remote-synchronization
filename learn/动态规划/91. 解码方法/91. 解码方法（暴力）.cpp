//https://leetcode.cn/problems/decode-ways/description/
#include <bits/stdc++.h>
using namespace std;
string s;
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
    int ans = f(i + 1);
    if(i + 1 < len && (s[i] - '0') * 10 + s[i + 1] - '0' <= 26)
    {
        ans += f(i + 2);
    }
    return ans;
}

int main()
{
    cin >> s;
    len  = s.size();
    cout << f(0) << endl;
}