#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int Max = 0;
    int count = 0;
    for (int i = 0; i < 2 * n; i++)
    {
        if(s[i % n] == '0')
        {
            count++;
        }
        else
        {
            Max = max(Max, count);
            count = 0;
        }
    }
    cout << Max << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}