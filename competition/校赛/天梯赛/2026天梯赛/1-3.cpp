#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int a, b;
    cin >> a >> b;

    int c = b - a;

    cout << c << endl;
    if(c <= 0)
    {
        cout << "hai sheng ma?" << endl;
    }
    else if(c <= 250)
    {
        cout << "nin tai cong ming le!" << endl;
    }
    else
    {
        cout << "jiu ting tu ran de..." << endl;
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