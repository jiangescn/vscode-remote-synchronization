#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    // for (int i = 0; i < 100; i++)
    // {
    //     int temp = i;
    //     int count = 0;
    //     while(temp)
    //     {
    //         temp /= 2;
    //         count++;
    //     }
    //     cout << count << " ";
    // }
    int n, k;
    cin >> n >> k;
    vector<int> s(n);
    vector<int> ss;
    map<int, int> count;
    int Max = 0;
    int Max_num = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        if(count[s[i]] == 0)ss.push_back(s[i]);
        count[s[i]]++;
        if(count[s[i]] >= Max)
        {
            Max = count[s[i]];
            Max_num = s[i];
        }
    }

    if(Max >= k)
    {
        cout << 0 << endl;
        return;
    }
    
    int ans = 0;
    sort(ss.begin(), ss.end());
    for (int i = 0; i < n; i++)
    {
        
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