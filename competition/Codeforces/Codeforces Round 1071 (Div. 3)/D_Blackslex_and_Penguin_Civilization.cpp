#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;

    int N = 1LL << n;

    cout << N - 1 << " ";

    for (int k = n - 1; k >= 0; k--)
    {
        int Min = (1LL << k) - 1;
        int step = 1LL << (k + 1);


        // 低 k 位全是 1
        // 第 k 位是 0
        for (int x = Min; x < N; x += step)
        {
            cout << x << " ";
        }
    }

    cout << endl;
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