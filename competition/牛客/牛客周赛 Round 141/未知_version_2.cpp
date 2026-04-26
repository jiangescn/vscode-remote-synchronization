#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e9;
const int mod = 1e9 + 7;
int qpow(int a, int b)
{
    int r = 1;
    while (b)
    {
        if (b & 1)
            r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

void solve()
{
    int n;
    cin >> n;

    vector<int> s(n + 1);
    map<int, int> count;
    int dayu2 = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        count[s[i]]++;
        if (count[s[i]] >= 2)
        {
            dayu2 = 1;
        }
    }

    if(count[1] >= 2)
    {
        cout << "YES" << endl;
        return;
    }

    if(dayu2 && count[1])
    {
        cout << "YES" << endl;
        return;
    }



    sort(s.begin() + 1, s.end());
    // s.erase(unique(s.begin() + 1, s.end()), s.end());

    for (int i = 1; i <= n; i++)
    {
        if(s[i] == 1)continue;

        int ai = s[i];
        int aj = 2;
        int az = qpow(ai, aj);

        // cout << ai << " " << aj << endl;
        
        while(az <= N)
        {
            if(count[aj] && count[az])
            {
                cout << "YES" << endl;
                return;
            }

            aj++;
            az *= ai;
        }
    }

    cout << "NO" << endl;
    return;
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