#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n;
    cin >> n;
    map<int, int> s;
    for (int i = 0; i < 2 * n; i++)
    {
        int a;
        cin >> a;
        s[a]++;
    }

    int diff = s.size();
    if (diff == 1)
    {
        cout << (n & 1 ? 2 : 0) << endl;
        return;
    }

    int odd = 0;
    int ans = 0;
    int sp = 0;
    for (auto it : s)
    {
        if (it.second & 1)
        {
            odd += 1;
            ans += 1;
        }
        else
        {
            ans += 2;
        }

        if (it.second % 4 == 0)
        {
            sp++;
        }
    }
    if(sp & 1 && odd == 0)ans -= 2;
    cout << ans << endl;

    //1 1 1 2 3 4 4 4 4 5 5 6
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}