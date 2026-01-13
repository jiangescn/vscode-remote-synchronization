#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n;
    cin >> n;
    int count1 = 0, count2 = 0;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        if(a - 1)
        {
            count2++;
        }
        else
        {
            count1++;
        }
    }

    int ans = max(min({count1, count2}), count1 / 3);

    cout << ans << endl;
    
}