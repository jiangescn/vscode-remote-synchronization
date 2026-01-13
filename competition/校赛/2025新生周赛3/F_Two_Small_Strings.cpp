#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    cout << "YES" << endl;
    if(a[0] == a[1] && a[1] == b[1] && b[1] == b[0])
    {
        for (int i = 0; i < n; i++)
        {
            cout << "abc";
        }
        cout << endl;
        return;
    }

    if (a[0] == b[1] && a[1] == b[0])
    {
        char c = 'a' + 'b' + 'c' - a[0] - a[1];
        for (int i = 0; i < n; i++)
        {
            cout << a[0];
        }
        for (int i = 0; i < n; i++)
        {
            cout << c;
        }
        for (int i = 0; i < n; i++)
        {
            cout << a[1];
        }
        
        return;
    }

    if(a[0] == b[0] && a[1] != b[1] && a[1] != a[0] && b[1] != b[0])
    {
        for (int i = 0; i < n; i++)
        {
            for (int i = 0; i < 3; i++)
            {
                char c = 'a' + i;
                if(c != a[0])cout << c;
            }
        }
        for (int i = 0; i < n; i++)
        {
            cout << a[0];
        }
        cout << endl;
        return;
    }

    if (a[0] != b[0] && a[1] == b[1] && a[1] != a[0] && b[1] != b[0])
    {
        for (int i = 0; i < n; i++)
        {
            cout << a[1];
        }
        for (int i = 0; i < n; i++)
        {
            for (int i = 0; i < 3; i++)
            {
                char c = 'a' + i;
                if(c != a[1])cout << c;
            }
        }
        cout << endl;
        return;
    }

    string tar1 = "abca";
    if (tar1.find(a) == string::npos && tar1.find(b) == string::npos)
    {
        tar1 = "abc";
        for (int i = 0; i < n; i++)
        {
            cout << tar1;
        }
        return;
    }
    string tar2 = "acba";
    if (tar2.find(a) == string::npos && tar2.find(b) == string::npos)
    {
        tar2 = "acb";
        for (int i = 0; i < n; i++)
        {
            cout << tar2;
        }
        return;
    }
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