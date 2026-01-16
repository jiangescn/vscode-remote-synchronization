#include <bits/stdc++.h>
using namespace std;
#define int long long
#define _ << " " << 

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, m;
        cin >> n >> m;

        vector<int> s(m + 1);
        for (int i = 1; i <= m; i++)
        {
            cin >> s[i];
        }

        int ans = n - s[m] + 1;
        for (int i = 2; i <= m; i++)
        {
            if(s[i] == 1) ans = 1;
        }
        cout << ans << endl;
    }
    return 0;
}