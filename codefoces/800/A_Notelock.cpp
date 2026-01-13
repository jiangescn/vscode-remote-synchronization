#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int count_zero = k - 1;
        int ans = 0;
        int found = 0;
        for (int i = 0; i < n; i++)
        {

            if (i == 0)
            {
                if (s[i] == '1')
                {
                    ans++;
                    found = 1;
                    count_zero = 0;
                    //cout << "peota:" << i + 1 << endl;
                }
            }
            else
            {
                if (s[i] - '0') // 1
                {
                    found = 1;
                    if (count_zero < k - 1)
                    {
                        //cout << "skpi:" << i + 1 << endl;
                    }
                    else
                    {
                        ans++;
                        //out << "peota:" << i + 1 << endl;
                    }
                    count_zero = 0;
                }
                else // 0
                {
                    if (found)
                    {
                        count_zero++;
                    }
                }
            }
            //cout << "i :" << i + 1 << "  zero:" << count_zero << endl;
        }
        cout << ans << endl;
        //cout << endl;
    }
    return 0;
}