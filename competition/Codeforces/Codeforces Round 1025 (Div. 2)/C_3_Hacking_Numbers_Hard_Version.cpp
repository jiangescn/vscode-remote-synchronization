#include <bits/stdc++.h>
using namespace std;
#define int long long

int ask(string s)
{
    cout << s << endl;
    cout.flush();

    int res;
    cin >> res;
    if (res == -1)
        exit(0);
    return res;
}

int ask(string s, int x)
{
    cout << s << " " << x << endl;
    cout.flush();

    int res;
    cin >> res;
    if (res == -1)
        exit(0);
    return res;
}

void solve()
{
    int tar;
    cin >> tar;

    if(tar == 81)
    {
        ask("mul", 999999999);
        ask("digit");
    }
    else
    {
        ask("mul", 999999999);
        ask("digit");
        ask("add", tar - 81);
    }

    cout << "!" << endl;

    int res;
    cin >> res;
    if (res == -1) exit(0);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}