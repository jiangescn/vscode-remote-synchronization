#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if((s[j] % s[i]) % 2 == 0)
            {
                cout << s[i] << " " << s[j] << endl;
                return;
            }
        }
        
    }
    
    cout << -1 << endl;
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
        solv();
    }
    return 0;
}