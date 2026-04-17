#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        string s;
        cin >> n >> s;

        vector<int> pos;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '1')
                pos.push_back(i);
        }

        if (pos.empty())
        {
            cout << 0 << ' ' << 0 << '\n';
            continue;
        }

        int mn = 0, mx = 0;

        int L = pos[0], R = pos[0];
        for (int i = 1; i < (int)pos.size(); i++)
        {
            if (pos[i] - pos[i - 1] <= 2)
            {
                R = pos[i];
            }
            else
            {
                int len = R - L + 1;
                mn += (len + 2) / 2;
                mx += len;

                L = R = pos[i];
            }
        }

        int len = R - L + 1;
        mn += (len + 2) / 2;
        mx += len;

        cout << mn << ' ' << mx << '\n';
    }

    return 0;
}