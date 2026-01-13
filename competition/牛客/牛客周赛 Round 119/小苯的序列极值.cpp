#include <bits/stdc++.h>
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
        vector<int> s(n + 1);
        int Max = INT_MIN;
        int Min = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
            if (s[i] > Max)
            {
                Max = s[i];
            }
            if (s[i] < Min)
            {
                Min = s[i];
            }
        }
        
        cout << abs(Max - Min) << endl;
    }
}