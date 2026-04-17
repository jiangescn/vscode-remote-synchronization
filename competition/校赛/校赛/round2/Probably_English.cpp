#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    map<string, int> s;
    s["and"] = 1;
    s["not"] = 1;
    s["that"] = 1;
    s["you"] = 1;
    s["the"] = 1;


    int ok = 0;
    for (int i = 1; i <= n; i++)
    {
        string a;
        cin >> a;
        if(s[a]) ok = 1;
    }


    cout << (ok ? "Yes" : "No") << endl;

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