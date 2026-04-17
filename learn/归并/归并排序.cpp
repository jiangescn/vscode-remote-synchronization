#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stack>
using namespace std;
#define int long long

const int N = 1e5 + 10;
int s[N], temp[N];

void merge(int l, int r)
{
    if (l >= r) return;

    int mid = (l + r) / 2;

    merge(l, mid);
    merge(mid + 1, r);

    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
    {
        if (s[i] <= s[j]) temp[k++] = s[i++];
        else temp[k++] = s[j++];
    }

    while (i <= mid) temp[k++] = s[i++];
    while (j <= r) temp[k++] = s[j++];

    for (int i = 0; i < k; i++)
    {
        s[l + i] = temp[i];
    }
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    merge(1, n);
    for (int i = 1; i <= n; i++)
    {
        cout << s[i] << " \n"[i == n];
    }
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}