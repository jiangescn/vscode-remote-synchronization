#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    map<pair<int, char>, int> data;
    vector<pair<int, char>> s(n);
    for (int i = 0; i < n; i++)
    {
        int a;
        char c;
        cin >> a >> c;
        data[{a, c}] = i;
        s[i] = {a, c};
    }
    
    map<int, set<char>> quchong;
    for (auto it: s)
    {
        quchong[it.first].insert(it.second);
    }

    int sum = 0;
    for (auto it : quchong)
    {
        
        if (it.second.size() >= 2)
        {
            sum += 2;
            if (it.second.size() == 4)
            {
                sum += 2;
            }
        }
    }
    cout << sum << endl;

    for (auto it : quchong)
    {
        vector<char> temp;
        for (auto Z: (it.second))
        {
            temp.push_back(Z);
        }

        if(it.second.size() >= 2)
        {
            cout << data[{it.first, temp[0]}] + 1 << " " << data[{it.first, temp[1]}] + 1 << endl;
            if (it.second.size() == 4)
            {
                cout << data[{it.first, temp[2]}] + 1 << " " << data[{it.first, temp[3]}] + 1 << endl;
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