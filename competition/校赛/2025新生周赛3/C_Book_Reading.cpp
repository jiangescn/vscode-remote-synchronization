#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, m;
    cin >> n >> m;

    if(n == 1 && m == 1)
    {
        cout << 1 << endl;
        return;
    }

    vector<int> s;
    s.push_back(m % 10);
    int temp = -1;
    int val = m;
    while (temp != s[0])
    {
        val += m;
        temp = val % 10;
        if (temp != s[0])
        {
            s.push_back(temp);
        }
    }
    int len = s.size();

    // cout << "s:------------" << endl;
    // for (int i = 0; i < s.size(); i++)
    // {
    //     cout << s[i] << " ";
    // }
    // cout << endl << "---------------" << endl;
    // cout << "len:" << len << endl;

    int sum = 0;
    vector<int> pre(len);
    pre[0] = s[0];
    for (int i = 0; i < s.size(); i++)
    {
        sum += s[i];
        if(i >= 1)
        {
            pre[i] = pre[i - 1] + s[i];
        }
    }

    int round = n / m / len;
    int ans = sum * round;
    if(n / m % len - 1 >= 0)ans += pre[n / m % len - 1];


    // cout << "pre:------------" << endl;
    // for (int i = 0; i < pre.size(); i++)
    // {
    //     cout << pre[i] << " ";
    // }
    // cout << endl << "---------------" << endl;
    

    // cout << "round:" << round  << "    plus:"  << round * sum << endl;
    // cout << "yuxia:" << n / m % len << "    plus:" << pre[n / m % len - 1] << endl;
    // cout << endl;

    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}