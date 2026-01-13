#include <bits/stdc++.h>
using namespace std;
const int NN = 2E5 + 10;

void solv()
{
    int n, x;
    cin >> n >> x;
    long long sum = 0;
    for (int i = 1; i <= x; i++)
    {
        for (int j = i; j <= x; j++)
        {
            for (int k = j; k <= x; k++)
            {
                if (i + j + k <= x)
                {
                    if (i * j + i * k + j * k <= n)
                    {
                        if (i == j && j == k)
                        {
                            sum += 1;
                        }
                        else if (i != j && i != k && j != k)
                        {
                            sum += 6;
                        }
                        else
                        {
                            sum += 3;
                        }
                    }
                }
            }
        }
    }
    cout << sum << endl;   
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
        solv();
    return 0;
}