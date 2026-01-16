#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n, c;
    cin >> n >> c;
    map<int, int> s;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        s[a[i]]++;
    }

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        count += s[a[i] + c];
    }
    cout << count << endl;
    return 0;
}