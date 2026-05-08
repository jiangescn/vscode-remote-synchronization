#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    vector<int> odd;
    vector<int> even;
    vector<int> it;
    vector<int> sp;

    for (int i = 1; i <= n; i++)
    {
        if(s[i] % 6 == 0)
        {
            sp.push_back(s[i]);
        }
        else if(s[i] % 2 == 0)
        {
            even.push_back(s[i]);
        }
        else if(s[i] % 3 == 0)
        {
            odd.push_back(s[i]);
        }
        else
        {
            it.push_back(s[i]);
        }
    }

    // sort(sp.begin(), sp.end());
    // sort(odd.begin(), odd.end());
    // sort(even.begin(), even.end());
    // sort(it.begin(), it.end());

    for (auto x : sp)
    {
        cout << x << " ";
    }
    for (auto x : even)
    {
        cout << x << " ";
    }
    for (auto x : it)
    {
        cout << x << " ";
    }
    for (auto x : odd)
    {
        cout << x << " ";
    }
    cout << endl;
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
        solve();
    }
    return 0;
}

