#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define int long long

signed main ()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        int a[20005];
        int ans = 0;
        cin >> n >> m;
        for(int i = 1; i <= n ; i++)
        {
            cin>>a[i];
        }

        sort(a+1,a+n+1);
        
        for(int i = n ;i >= 1 && m; i--)
        {
            ans += a[i] * m;
            //cout<<ans<<' ';
            m--;
        }
        cout << ans << "\n";
    }
    return 0;
}