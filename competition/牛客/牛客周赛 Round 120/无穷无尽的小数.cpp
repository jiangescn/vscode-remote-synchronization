#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int a, b;
    cin >> a >> b;
    string xx, yy;
    cin >> xx >> yy;
    
    string x = "", y = "";
    for (int i = 0; i < b; i++)
    {
        x += xx;
    }
    for (int i = 0; i < a; i++)
    {
        y += yy;
    }

    //cout << "X:" << x << endl;
    //cout << "Y:" << y << endl;

    vector<int> ans(a + b);
    bool sw = y > x;
    if(sw)swap(x, y);
    for (int i = a + b - 1; i >= 0; i--)
    {
        ans[i] = x[i] - y[i];
        if (ans[i] < 0)
        {
            ans[i] += 10;
            x[i - 1]--;
        }
    }

    // for (auto it : ans)
    // {
    //     cout << it;
    // }
    // cout << endl;

    if(sw)
    {
        for(auto& it: ans)
        {
            it = 9 - it;
        }
    }
    
    cout << a + b << endl;
    for (auto it: ans)
    {
        cout << it;
    }
    


}

signed main()
{
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}