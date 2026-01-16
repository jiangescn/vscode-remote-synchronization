#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1E5 + 10;

signed main()
{
    int n, k;
    cin >> n >> k;
    int a[N];
    int b[N];
    set<int> s;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            s.insert(a[i] + b[j]);
        }
    }

    auto it = s.end();
    for (int i = 0; i < k; i++)
    {
        it--;
    }
    

    cout << *it << endl;
}