#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
vector<int> s;

bool check(int x)
{
    int sum = 0, count = 0;

    for (int i = 1; i <= n; i++)
    {
        if (sum + s[i] > x)
        {
            count++;
            sum = 0;
        }
        sum += s[i];
    }

    return count >= m;
}

signed main()
{
    cin >> n >> m;
    s.resize(n + 1);
    int sum = 0;
    int Max = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        sum += s[i];
        Max = max(Max, s[i]);
    }

    int l = Max, r = sum;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (check(mid))
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    cout << l << endl;

    return 0;
}