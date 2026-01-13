#include <bits/stdc++.h>
using namespace std;
void solv()
{
    int m, n;
    cin >> m >> n;
    vector<long long> price(m);
    vector<int> how(n);
    vector<int> where(n);
    int valid = 1;
    for (int i = 0; i < m; i++)
    {
        cin >> price[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> how[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> where[i];
        if(where[i] > m)
        {
            valid = 0;
        }
    }
    
    long long sum = 0;
    long long x;
    cin >> x;

    if (!valid)
    {
        cout << "No" << endl;
        return;
    }

    sort(price.begin(), price.end());
    for (int i = 1; i < m; i++)
    {
        price[i] += price[i-1];
    }

    for (int i = 0; i < n; i++)
    {
        sum += price[where[i] - 1];
        sum += (how[i] - where[i]) * price[0];
        //cout << "sum:" << sum << endl;
    }
    cout << (sum > x ? "No" : "Yes") << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while(t--)
    {
        solv();
    }
}