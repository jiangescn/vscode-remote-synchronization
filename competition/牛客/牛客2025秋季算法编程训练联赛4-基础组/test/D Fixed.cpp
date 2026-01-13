#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        int left_max = INT_MIN;
        int right_min = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            int right , left ;
            cin >> left >> right;

            left_max = max(left_max, left); 
            right_min = min(right_min, right); 
        }


        cout << "left:" << left_max << "  right:" << right_min << endl;

        if(left_max > right_min)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout  << "No" << endl;
        }
    }   
    return 0;
}