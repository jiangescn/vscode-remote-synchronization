#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2E7 + 10;
bool s[N] = {false};
void solve()
{
    for (int i = 1; i * i < N; i++)
    {
        for (int j = i; i * i + j * j < N; j++)
        {
            s[i*i + j*j] = true;
        }
    }
    
    int q;
    cin >> q;
    while(q--)
    {
        int a;
        cin >> a;
        if(s[a])
        {
            cout << "Yes" << endl; 
        }
        else
        {
            cout << "No" << endl;
        }
    }

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