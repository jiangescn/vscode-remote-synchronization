#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    vector<int> a(26);
    for (int i = 0; i < 26; i++)
    {
        cin >> a[i];
    }

    int sum = 0;
    vector<int> count(26);
    for (int i = 0; i < s.size(); i++)
    {
        count[s[i] - 'a']++;
        sum += a[s[i] - 'a'];
    }
    for (int i = 0; i < 26; i++)
    {
        if (i != 0)
            cout << " ";
        cout << count[i];
    }
    cout << endl;
    cout << sum << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}