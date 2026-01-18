#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n;
    cin >> n;

    if(n == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    vector<int> sl(n + 1);
    vector<int> s(n - 1);
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> sl[i];
    }
    for (int i = n; i >= 1; i--)
    {
        sl[i] = sl[i] - sl[i - 1];
        sum += sl[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        s[i] = sl[i + 2];
    }

    // for (int i = 0; i < n - 1; i++)
    // {
    //     cout << s[i] << endl;
    // }
    // cout << endl;
    // cout << endl;

    sort(s.begin(), s.end(), [](int a, int b){
        return a > b;
    });

    // for (int i = 0; i < n - 1; i++)
    // {
    //     cout << s[i] << endl;
    // }


    for (int i = 0; i < n; i++)
    {
        cout << sum - sl[1] << " ";
        sum -= s[i];
    }
    
    
}
