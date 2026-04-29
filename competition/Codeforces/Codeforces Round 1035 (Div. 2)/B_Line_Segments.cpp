#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    int x1, y1, x2 ,y2;
    cin >> x1 >> y1 >> x2 >> y2;

    vector<double> s(n + 1);
    double sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        sum += s[i];
    }


    double dis = (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1);

    double r = sqrt(dis);
    sum += r;

    s.push_back(r);

    sort(s.begin() + 1, s.end());

    if(s[n + 1] <= sum - s[n + 1])
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }


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