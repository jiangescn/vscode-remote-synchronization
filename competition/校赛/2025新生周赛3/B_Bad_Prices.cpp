#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    int Min = INT_MAX;
    int count = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if(s[i] > Min)
        {
            count++;
        }
        else
        {
            Min = s[i];
        }
    }
    cout << count << endl;
    

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