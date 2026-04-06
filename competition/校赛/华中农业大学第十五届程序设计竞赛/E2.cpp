#include <bits/stdc++.h>
using namespace std;
#define int long long

map<char, int> vi;

void solve()
{
    string s;
    cin >> s;
    // cout << s << endl;
    if(!vi[s[s.size() - 1]])
    {
        cout << "No" << endl;
        return;
    }

    cout << "Yes" << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    vi['1'] = 1;
    vi['3'] = 1;
    vi['7'] = 1;
    vi['9'] = 1;

    int _ = 1;
    cin >> _;
    while(_--)
    {
        solve();
    }
    return 0;
}
