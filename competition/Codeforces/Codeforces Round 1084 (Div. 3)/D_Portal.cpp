#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> s(n + 1);
    vector<int> In;
    vector<int> Out;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];

        if (i > x && i <= y)
        {
            In.push_back(s[i]);
        }
        else
        {
            Out.push_back(s[i]);
        }
    }

    // cout << "In:" << endl;
    // for (int i = 0; i < In.size(); i++)
    // {
    //     cout << In[i] << " ";
    // }cout << endl;
    // cout << "Out:" << endl;
    // for (int i = 0; i < Out.size(); i++)
    // {
    //     cout << Out[i] << " ";
    // }cout << endl;

    int Min = INT_MAX;
    int idx = 0;
    for (int i = 0; i < In.size(); i++)
    {
        if (In[i] < Min)
        {
            Min = In[i];
            idx = i;
        }
    }

    // cout << "idx:" << idx << endl;

    if (Out.empty())
    {
        for (int j = idx; j < In.size(); j++)
        {
            cout << In[j] << " ";
        }
        for (int j = 0; j < idx; j++)
        {
            cout << In[j] << " ";
        }
        cout << endl;
        return;
    }

    int ins = 1;
    for (int i = 0; i < Out.size(); i++)
    {
        if (Out[i] > Min && ins)
        {
            ins = 0;
            for (int j = idx; j < In.size(); j++)
            {
                cout << In[j] << " ";
            }
            for (int j = 0; j < idx; j++)
            {
                cout << In[j] << " ";
            }
        }
        cout << Out[i] << " ";
    }
    if (ins)
    {
        for (int j = idx; j < In.size(); j++)
        {
            cout << In[j] << " ";
        }
        for (int j = 0; j < idx; j++)
        {
            cout << In[j] << " ";
        }
        cout << endl;
        return;
    }
    cout << endl;
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