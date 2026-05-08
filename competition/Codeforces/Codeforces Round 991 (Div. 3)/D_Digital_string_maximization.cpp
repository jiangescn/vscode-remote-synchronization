#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        int temp = s[i], pos = i;
        for (int j = i + 1; j < min(n, i + 11); j++)
        {
            if (s[j] - (j - i) > temp)
            {
                temp = s[j] - (j - i);
                pos = j;
            }
        }
        for (int j = pos; j > i; j--)
        {
            swap(s[j], s[j - 1]);
            s[j - 1]--;
        }
    }
    cout << s << endl;
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