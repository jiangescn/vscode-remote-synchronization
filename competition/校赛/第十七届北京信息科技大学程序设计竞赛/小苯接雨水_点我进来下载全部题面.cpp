#include <iostream>
#include <vector>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> s(n+1);
        int max1 = 0, max2 = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> s[i];
            if(s[i] >= max1)
            {
                max2 = max1;
                max1 = s[i];
            }
            else if(s[i] > max2)
            {
                max2 = s[i];
            }
        }
        //cout << "Max:" << Max << " last:" << last << endl;
        cout << max2 * (n - 1) << endl;
    }
}