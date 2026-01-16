#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    string s;
    cin >> s;
    int n = s.size();

    char ed = s[s.size() - 1] + 1;
    s += ed;

    int cur = 1;
    int last = 0;
    int sum = 0;
    int plus = 0;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == s[i - 1])
        {
            cur++;
            // cout << "A" << endl;
        }
        else if ((s[i] - s[i - 1]) == 1)
        {
            // cout << "Sum+=" << min(cur, last) << " cur=" << cur << " last=" << last << endl;

            if(plus)
            {
                sum += min(cur, last);
                plus = 0;
            }
            plus = 1;
            last = cur;
            cur = 1;
            // cout << "B" << endl;
        }
        else
        {
            if (plus)
            {
                sum += min(cur, last);
                plus = 0;
            }
            last = cur;
            cur = 1;
            // cout << "C" << endl;
        }
        // cout << "now" << s[i] << endl;
        // cout << "len: " << cur << endl;
    }
    cout << sum << endl;
    return 0;
}