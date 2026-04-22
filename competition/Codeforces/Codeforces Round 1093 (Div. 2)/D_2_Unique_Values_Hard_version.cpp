#include <bits/stdc++.h>
using namespace std;
#define int long long

int ask(vector<int> s)
{
    cout << "? " << s.size();
    for (auto it : s)
    {
        cout << " " << it;
    }
    cout << endl;

    int n;
    cin >> n;
    if (n == -1)
        exit(0);
    return n;
}

int check(vector<int> s)
{
    int n = ask(s);
    return (s.size() - n) & 1;
}

void solve()
{
    int n;
    cin >> n;
    int N = 2 * n + 1;

    int l = 1, r = N;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        vector<int> t;
        for (int i = 1; i <= mid; i++)
        {
            t.push_back(i);
        }

        if (check(t))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    int z = l;

    l = 1, r = N;
    while (l < r)
    {
        int mid = l + (r - l + 1) / 2;
        vector<int> t;
        for (int i = mid; i <= N; i++)
        {
            t.push_back(i);
        }

        if (check(t))
        {
            l = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    int x = l;

    l = x + 1, r = z - 1;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        vector<int> t;
        t.push_back(x);
        t.push_back(z);
        for (int i = x + 1; i <= mid; i++)
        {
            t.push_back(i);
        }

        if (check(t))
            r = mid;
        else
            l = mid + 1;
    }
    int y = l;

    cout << "! " << x << " " << y << " " << z << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--)
    {
        solve();
    }
    return 0;
}