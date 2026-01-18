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

        int left_max = LLONG_MIN;
        int right_min = LLONG_MAX;
        int left_min = LLONG_MAX;
        int right_max = LLONG_MIN;

        vector<int> left(n);
        vector<int> right(n);

        for (int i = 0; i < n; i++)
        {
            cin >> left[i] >> right[i];
            left_max = max(left_max, left[i]);
            right_min = min(right_min, right[i]);
            left_min = min(left_min, left[i]);
            right_max = max(right_max, right[i]);
        }

        if (left_max > right_min)
        {
            cout << "No" << endl;
            continue;
        }


        bool has_contain = false;
        for (int i = 0; i < n; i++)
        {
            if (left[i] < left_min && right[i] > right_max)
            {
                has_contain = true;
                break;
            }
            if (left[i] > left_min && right[i] < right_max)
            {
                has_contain = true;
                break;
            }
        }

        if (has_contain)
        {
            cout << "No" << endl;
        }
        else
        {
            cout << "Yes" << endl;
        }
    }
    return 0;
}