#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n;
    cin >> n;
    vector<double> s;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        s.push_back(a);
    }
    sort(s.begin(), s.end());
    double sum = s[0];

    for (int i = 1; i < n; i++)
    {
        sum = pow((double)sum*s[i], 0.5);
    }
    
    cout << fixed << setprecision(12) << sum << endl;
    
}

signed main()
{
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}