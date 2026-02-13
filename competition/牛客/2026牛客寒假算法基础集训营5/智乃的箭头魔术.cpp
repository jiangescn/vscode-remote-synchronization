#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int cur = 0;
    string p = "0112233445142015320125410214530214510214102302142025101203201451451522302514203214510021454101002532";

    string ans = "";

    for (char op : p)
    {
        switch (op - '0')
        {
        case 0:
            if (cur == 0)
                cur = 3;
            else if (cur == 1)
                cur = 2;
            else if (cur == 2)
                cur = 1;
            else if (cur == 3)
                cur = 0;
            break;
        case 1:
            if (cur == 0)
                cur = 0;
            else if (cur == 1)
                cur = 3;
            else if (cur == 2)
                cur = 2;
            else if (cur == 3)
                cur = 1;
            break;
        case 2:
            if (cur == 0)
                cur = 1;
            else if (cur == 1)
                cur = 0;
            else if (cur == 2)
                cur = 3;
            else if (cur == 3)
                cur = 2;
            break;
        case 3:
            if (cur == 0)
                cur = 2;
            else if (cur == 1)
                cur = 1;
            else if (cur == 2)
                cur = 0;
            else if (cur == 3)
                cur = 3;
            break;
        case 4:
            if (cur == 0)
                cur = 1;
            else if (cur == 1)
                cur = 2;
            else if (cur == 2)
                cur = 3;
            else if (cur == 3)
                cur = 0;
            break;
        case 5:
            if (cur == 0)
                cur = 3;
            else if (cur == 1)
                cur = 0;
            else if (cur == 2)
                cur = 1;
            else if (cur == 3)
                cur = 2;
            break;
        }

        ans += to_string(cur);
    }

    cout << ans << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}