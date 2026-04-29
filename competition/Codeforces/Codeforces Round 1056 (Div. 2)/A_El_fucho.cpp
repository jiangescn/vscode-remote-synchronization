#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    int win = n;
    int loser = 0;

    int count = 0;

    while (win > 1 || loser > 0)
    {
        if (win == 1 && loser == 1)
        {
            count++;
            loser = 0;
            break;
        }

        count += win / 2;
        int plus = win / 2;
        win = (win + 1) / 2;

        // cout << "     plus:" << plus << endl;

        count += loser / 2;
        loser = (loser + 1) / 2;
        loser += plus;

        // cout << "count:" << count << endl;
        // cout << " win:" << win << " loser:" << loser << endl;
    }

    cout << count << endl;
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