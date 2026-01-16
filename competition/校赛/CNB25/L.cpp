#include <bits/stdc++.h>
using namespace std;
#define int long long

int f(int day, int s[10][10])
{
    int count = 0;
    if (day > 7)
    {
        return 1;
    }

    for (int jie = 1; jie <= 6; jie++)
    {
        if (s[day][jie] == 0)
        {
            int temp = s[day + 1][jie];
            s[day + 1][jie] = 1;
            count += f(day + 1, s);
            s[day + 1][jie] = temp;
        }
    }
    return count;
}

signed main()
{
    int n;
    cin >> n;
    int s[10][10] = {0};
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a][b] = 1;
    }

    int ans = f(1, s);
    cout << ans << endl;
}