#include <bits/stdc++.h>
using namespace std;
#define int long long


void solve()
{
    int n, w;
    cin >> n >> w;
    vector<int> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> x[i] >> y[i];
    }

    priority_queue<pair<double, int>> pq;
    double sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += sqrt(x[i] * x[i] + y[i] * y[i]);
        double Nex = sqrt(x[i] * x[i] + y[i] * y[i]) - sqrt(x[i] * x[i] + (y[i] - 1) * (y[i] - 1));
        pq.push({Nex, i});
    }

    while(w > 0 && !(pq.empty()))
    {
        pair<double, int> top = pq.top();
        pq.pop();

        if(top.first <= 0)
        {
            break;
        }

        int i = top.second;
        sum -= top.first;
        y[i]--;
        w--;

        if(y[i] >= 1)
        {
            double Nex = sqrt(x[i] * x[i] + y[i] * y[i]) - sqrt(x[i] * x[i] + (y[i] - 1) * (y[i] - 1));
            pq.push({Nex, i});
        }

    }
    cout << fixed << setprecision(15) << sum << endl;
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