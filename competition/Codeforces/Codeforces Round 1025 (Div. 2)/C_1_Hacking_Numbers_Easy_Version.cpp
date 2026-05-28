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

    ask("digit");
    ask("digit");

    ask("add", -8);
    ask("add", -4);
    ask("add", -2);
    ask("add", -1);

    ask("add", tar - 1);

    cout << "!" << endl;
    cout.flush();

    int res;
    cin >> res;
    if (res == -1)
        exit(0);
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