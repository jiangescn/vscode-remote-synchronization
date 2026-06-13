#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

void solve()
{
    string s;
    cin >> s;
    vector<int> count(10);
    for (int i = 0; i < s.size(); i++)
    {
        count[s[i] - '0']++;
    }

    for (int i = 0; i < s.size(); i++)
    {
        for (int j = 9 - i; j <= 9; j++)
        {
            if(count[j])
            {
                count[j]--;
                cout << j;
                break;
            }
        }
    }

    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}