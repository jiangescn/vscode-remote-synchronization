#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
int prea[N][30], preb[N][30];

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        vector<int> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; i++)
        {
            char temp;
            cin >> temp;
            a[i] = temp - 'a';
        }

        for (int i = 1; i <= n; i++)
        {
            char temp;
            cin >> temp;
            b[i] = temp - 'a';
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                prea[i][j] = prea[i - 1][j];
                preb[i][j] = preb[i - 1][j];
                if (a[i] == j)
                    prea[i][j]++;
                if (b[i] == j)
                    preb[i][j]++;
            }
        }



        for (int z = 0; z < q; z++)
        {
            int l, r;
            cin >> l >> r;
            int sum = 0;
            for (int i = 0; i < 26; i++)
            {
                int acount = prea[r][i] - prea[l - 1][i];
                int bcount = preb[r][i] - preb[l - 1][i];
                sum += abs(acount - bcount);
            }
            cout << sum / 2 << endl;
        }
    }
    return 0;
}