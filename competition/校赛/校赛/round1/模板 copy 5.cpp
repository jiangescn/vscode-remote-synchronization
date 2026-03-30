#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n + m + 2);
    vector<int> b(n + m + 2);
    for (int i = 1; i <= m + n + 1; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= m + n + 1; i++)
    {
        cin >> b[i];
    }

    vector<int> prea(n + m + 2);
    vector<int> preb(n + m + 2);
    vector<int> chooce(n + m + 2);
    int needa = n, needb = m;
    for (int i = 1; i <= m + n + 1; i++)
    {
        prea[i] = prea[i - 1];
        preb[i] = preb[i - 1];

        if (a[i] > b[i])
        {
            if (needa > 0)
            {
                needa--;
                prea[i] += a[i];
                chooce[i] = 1;
            }
            else
            {
                needb--;
                preb[i] += b[i];
                chooce[i] = 2;
            }
        }
        else
        {
            if (needb > 0)
            {
                needb--;
                preb[i] += b[i];
                chooce[i] = 2;
            }
            else
            {
                needa--;
                prea[i] += a[i];
                chooce[i] = 1;
            }
        }
    }

    // for (int i = 1; i < m + n + 1; i++)
    // {
    //     cout << prea[i] << " ";
    // }cout << endl;
    // for (int i = 1; i < m + n + 1; i++)
    // {
    //     cout << preb[i] << " ";
    // }cout << endl;


    int aa = prea[m + n];
    int bb = preb[m + n];
    int sum = aa + bb;

    for (int i = 1; i < m + n + 1; i++)
    {
        if (chooce[i] == 1)
        {
            cout << sum - a[i] + a[m + n + 1] << " ";
        }
        else
        {
            cout << sum - b[i] + b[m + n + 1] << " ";
        }
    }

    cout << sum << endl;
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