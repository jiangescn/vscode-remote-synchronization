#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> fa;

int Find1(int x)
{
    if (fa[x] == x)
    {
        return x;
    }
    else
    {
        return fa[x] = Find1(fa[x]);
    }
}

void un(int a, int b)
{
    int x = Find1(a), y = Find1(b);
    fa[x] = y;
}

void solve()
{
    int n;
    cin >> n;

    fa.resize(n + 1, 0);
    map<int, int> ans;

    string dat;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    cin >> dat;

    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
    }

    for (int i = 1; i <= n; i++)
    {
        int a = s[i], b = s[a];
        while(Find1(a) != Find1(b))
        {
            un(a, b);
            a = b;
            b = s[b];
        }
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << fa[i] << " ";
    // }
    // cout << endl;


    for (int i = 1; i <= n; i++)
    {
        if(dat[i - 1] == '0')
        {
            ans[fa[s[i]]]++;
        }
    }


    for (int i = 1; i <= n; i++)
    {
        cout << ans[fa[s[i]]] << " ";
    }
    cout << endl;



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