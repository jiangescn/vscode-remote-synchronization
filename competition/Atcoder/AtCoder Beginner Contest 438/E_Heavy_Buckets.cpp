#include <iostream>
#include <vector>
using namespace std;
#define int long long
const int N = 200000 + 5;
const int K = 30;
int pos[K + 1][N], sum[K + 1][N];

signed main()
{
    int n, q;
    cin >> n >> q;
    int s[N] = {0};
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    // pos[k][x]：从x出发，走2ᵏ步后到达的点
    // sum[k][x]：从x出发，走2ᵏ步经过的所有点编号之和

    for (int i = 1; i <= n; i++)
    {
        pos[0][i] = s[i];
        sum[0][i] = i;
    }
    for (int k = 1; k <= K; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            int mid = pos[k - 1][i];
            pos[k][i] = pos[k - 1][mid];
            sum[k][i] = sum[k - 1][i] + sum[k - 1][mid];
        }
    }

    while (q--)
    {
        int t, b;
        cin >> t >> b;
        int temp = b;
        int ans = 0;
        for (int k = K; k >= 0; k--)
        {
            if (t >= (1LL << k))
            {
                ans += sum[k][temp];
                temp = pos[k][temp];
                t -= (1LL << k);
            }
        }
        cout << ans << endl;
    }
    return 0;
}