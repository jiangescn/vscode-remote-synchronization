#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int count = 0;
    vector<int> ans;
    for (int i = 0; i <= n; i++)
    {
        if(count == k)
        {
            ans.push_back(i - 1);
            count = 0;
        }
        if(s[i] == '0')
        {
            count++;
        }
        else if(s[i] == '1')
        {
            count = 0;
        }
    }

    //cout << "     " << ans.size() << endl;
    
    for (int i = 0; i <= n; i++)
    {
        if(i < ans.size())
        {
            cout << ans[i] << " ";
        }
        else
        {
            cout << n << " ";
        }
    }
    
}