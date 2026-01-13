#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    if(s.find("2026")!= -1)
    {
        cout << "0" << endl;
    }
    else if(s.find("2025") != -1)
    {
        cout << "1" << endl;
    }
    else
    {
        cout << "0" << endl;
    }
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