#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    vector<int> s(7);
    int Max = 0;
    for (int i = 0; i < 7; i++)
    {
        cin >> s[i];
    }
    for (int i = 0; i < 7; i++)
    {
        if(s[i] > s[Max])
        {
            Max = i;
        }
    }

    string ss[7] = {"Red", "Orange", "Yellow", "Green", "Blue", "Indigo", "Violet"};

    cout << ss[Max] << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}