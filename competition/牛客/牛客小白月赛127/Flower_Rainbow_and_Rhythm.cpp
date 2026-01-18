#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+10;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    vector<int> count(N);
    for(int i = 0; i < n; i++)
    {
        count[s[i]%k]++;
    }
    for(int i = 0; i < n; i++)
    {
        if(count[i]%2)
        {
            cout << "No" << endl;
            return;
        }
    }
    cout << "Yes" << endl;
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