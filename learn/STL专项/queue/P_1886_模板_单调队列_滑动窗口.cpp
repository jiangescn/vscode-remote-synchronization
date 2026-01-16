#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> s;
    s.reserve(n + 10);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    deque<int> dq;
    for (int i = 0; i < n; i++)
    {
        if(!dq.empty() && i - dq[0] >= k)
        {
            dq.pop_front();
        }
        while (!dq.empty() && s[i] < s[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);

        // for (int j = 0; j < dq.size(); j++)
        // {
        //     cout << dq[j] << " \n"[j == dq.size() - 1];
        // }
        
        if(i >= k - 1)cout << s[dq.front()] << " ";
    }
    cout << endl;

    while(!dq.empty())dq.pop_back();
    for (int i = 0; i < n; i++)
    {
        if(!dq.empty() && i - dq[0] >= k)
        {
            dq.pop_front();
        }
        if (!dq.empty() && s[i] > s[dq.back()])
        {
            while (!dq.empty() && s[i] > s[dq.back()])
            {
                dq.pop_back();
            }
        }
        dq.push_back(i);
        
        if(i >= k - 1)cout << s[dq.front()] << " ";
    }
    cout << endl;
    

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