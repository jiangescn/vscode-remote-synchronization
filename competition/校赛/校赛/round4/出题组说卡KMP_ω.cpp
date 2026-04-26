#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    string s;
    cin >> s;
    int countx = 0;
    int counto = 0;

    int fir = 0;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'x')
        {
            countx++;
            if (counto > 1)
            {
                cout << "No" << endl;
                return;
            }
            counto = 0;
        }
        else if (s[i] == 'o')
        {
            counto++;
            if (countx > 2)
            {
                cout << "No" << endl;
                return;
            }
            if (countx == 1 && fir)
            {
                cout << "No" << endl;
                return;
            }
            countx = 0;
            fir = 1;
        }
        else
        {
            cout << "No" << endl;
            return;
        }
    }

    if (counto > 1)
    {
        cout << "No" << endl;
        return;
    }

    if (countx > 2)
    {
        cout << "No" << endl;
        return;
    }

    cout << "Yes" << endl;
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