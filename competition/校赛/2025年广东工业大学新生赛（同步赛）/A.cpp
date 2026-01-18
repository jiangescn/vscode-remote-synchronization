#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    sort(s.begin(), s.end());
    cout << 1 << " " << n << " " << s[n - 1] - s[0] << endl; 

}