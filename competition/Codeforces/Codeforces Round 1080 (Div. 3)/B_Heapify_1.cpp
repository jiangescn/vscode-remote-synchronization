#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    vector<int> cand;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int ok = 1;
    for (int i = 1; i <= n; i++)
    {
        int k = s[i];
        if(k > i)
        {
            while(k > i)
            {
                k /= 2;
            }
            if(k != i)
            {
                ok = 0; 
                break;
            }
        }
        else if(k < i)
        {
            while(k < i)
            {
                k *= 2;
            }
            if(k != i)
            {
                ok = 0;
                break;
            }
        }
    } 

    cout << (ok ? "YES" : "NO") << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}