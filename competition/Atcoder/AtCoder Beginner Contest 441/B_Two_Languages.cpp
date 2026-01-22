#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int m, n;
    cin >> m >> n;
    unordered_map<char, bool> a(m), b(n);
    for (int i = 0; i < m; i++)
    {
        char c; cin >> c;
        a[c] = true;
    }
    for (int i = 0; i < n; i++)
    {
        char c; cin >> c;
        b[c] = true;
    }
    int q;
    cin >> q;
    while(q--)
    {
        string s;
        cin >> s;
        int x = s.size();
        bool isa = true, isb = true;
        for (int i = 0; i < x; i++)
        {
            if(!a[s[i]])isa = false;
        }
        for (int i = 0; i < x; i++)
        {
            if(!b[s[i]])isb = false;
        }

        if(isa && isb)
        {
            cout << "Unknown" << endl;
        }
        else
        {
            if(isa)
            {
                cout << "Takahashi" << endl;
            }
            else
            {
                cout << "Aoki" << endl;
            }
        }
    }
    
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}