#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{

    int n;
    cin >> n;

    for (int i = 3; i <= n; i++)
    {
        cout << "? " << i * 2 - 1 << " " << i * 2 << endl;

        int res;
        cin >> res;
        if (res == -1) exit(0);

        if (!res)
        {
            continue;
        }
        else
        {
            cout << "! " << i * 2 << endl;
            return;
        }
    }

    //1,2,3,4 中至少有两个 0
    cout << "? 1 2" << endl;
    int res;
    cin >> res;
    if (res == -1)
        exit(0);
    if (res)
    {
        cout << "! 1" << endl;
        return;
    }

    cout << "? 2 3" << endl;
    cin >> res;
    if (res == -1)
        exit(0);
    if (res)
    {
        cout << "! 2" << endl;
        return;
    }

    cout << "? 1 3" << endl;
    cin >> res;
    if (res == -1)
        exit(0);
    if (res)
    {
        cout << "! 1" << endl;
        return;
    }

    cout << "! 4" << endl;
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