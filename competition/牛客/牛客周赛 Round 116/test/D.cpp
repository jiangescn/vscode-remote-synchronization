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
        map<int, int> nums;
        // set<int> a;
        for (int i = 0; i < n; i++)
        {
            int a, b;
            cin >> a >> b;
            if (nums.count(a) == 0 || b > nums[a])
            {
                nums[a] = b;
            }
        }

        // for (auto i = nums.begin(); i != nums.end(); i++)
        // {
        //     cout << "1:" << i->first << "    2:" << i->second << endl;
        // }

        bool valid = true;
        for (auto i = nums.begin(), j = ++nums.begin(); j != nums.end(); i++, j++)
        {
            //cout << "1:" << i->second << "    2:" << j->first << endl;
            if (i->second < j->first || i -> second >= j -> second)
            {
                cout << "No" << endl;
                valid = false;
                break;
            }
        }

        if (valid)
            cout << "Yes" << endl;
    }
    return 0;
}