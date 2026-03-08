#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    string s, a;
    cin >> s >> a;

    // vector<int> need;

    // if (s == a)
    // {
    //     cout << "YES" << endl;
    //     return;
    // }

    // // 无1
    // int shave1 = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     if (s[i] == '1')
    //     {
    //         shave1 = 1;
    //     }
    // }
    // int ahave1 = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     if (a[i] == '1')
    //     {
    //         ahave1 = 1;
    //     }
    // }

    // if (shave1 == 0 && ahave1 == 1)
    // {
    //     cout << "NO" << endl;
    //     return;
    // }

    // // long == 1
    // if (n == 1)
    // {
    //     if (s == a)
    //     {
    //         cout << "YES" << endl;
    //         return;
    //     }
    //     else
    //     {
    //         cout << "NO" << endl;
    //         return;
    //     }
    // }

    // // long == 2
    // if (n == 2)
    // {
    //     if (s == "11")
    //     {
    //         if (a == "00")
    //         {
    //             cout << "YES" << endl;
    //             return;
    //         }
    //         else
    //         {
    //             cout << "NO" << endl;
    //             return;
    //         }
    //     }
    //     if (s == "01" || s == "10")
    //     {
    //         if (a == "00" || a == "11")
    //         {
    //             cout << "YES" << endl;
    //             return;
    //         }
    //         else
    //         {
    //             cout << "NO" << endl;
    //             return;
    //         }
    //     }
    //     else
    //     {
    //         cout << "NO" << endl;
    //         return;
    //     }
    // }


    // if(n == 3)
    // {
    //     if(a == "010")
    //     {
    //         cout << "NO" << endl;
    //         return;
    //     }

    //     if(a == "011")
    //     {
    //         if(s == "010" || s == "001")
    //         {
    //             cout << "YES" << endl;
    //             return;
    //         }
    //         else
    //         {
    //             cout << "NO";
    //             return;
    //         }
    //     }

    //     if(a == "110")
    //     {
    //         if(s == "010" || s == "100")
    //         {
    //             cout << "YES" << endl;
    //             return;
    //         }
    //         else
    //         {
    //             cout << "NO";
    //             return;
    //         }
    //     }
    // } 

    // // long >= 3
    // //...101...
    // for (int i = 2; i < n; i++)
    // {
    //     if (a[i - 2] == '1' && a[i - 1] == '0' && a[i] == '1')
    //     {
    //         need.push_back(i - 1);
    //         if (s[i - 1] != '0')
    //         {
    //             cout << "NO" << endl;
    //             return;
    //         }
    //     }
    // }

    // // // 前&后
    // // for (int i = 0; i < n; i++)
    // // {
    // //     if (a[i] == '1')
    // //     {
    // //         need.push_back(i);
    // //         break;
    // //     }
    // // }
    // // for (int i = n - 1; i > 0; i--)
    // // {
    // //     if (a[i] == '1')
    // //     {
    // //         need.push_back(i);
    // //         break;
    // //     }
    // // }

    // need.push_back(0);
    // need.push_back(n-1);

    // // cout << "need:" << endl;
    // // for (int i = 0; i < need.size(); i++)
    // // {
    // //     cout << need[i]+1 << endl;
    // // }

    // sort(need.begin(), need.end());
    // for (int i = 1; i < need.size(); i++)
    // {
    //     int x = need[i - 1], y = need[i];
    //     // cout << "X:" << x << " Y:" << y << endl;
    //     int ok = 0;
    //     for (int i = x; i <= y; i++)
    //     {
    //         if (s[i] == '1')
    //         {
    //             ok = 1;
    //         }
    //     }

    //     if (ok == 0 && x != y)
    //     {
    //         cout << "NO" << endl;
    //         return;
    //     }
    // }

    // cout << "YES" << endl;

    int found1 = 0;
    for (int i = 0; i < n; i++)
    {
        if(s[i] == '1')
        {
            found1 = 1;
        }
    }

    if (s == a)
    {
        cout << "YES" << endl;
        return;
    }

    if(!found1)
    {
        cout << "NO" << endl;
        return;
    }

    
    int seam = 0;
    for (int i = 1; i < n; i++)
    {
        if(a[i] == a[i-1])
        {
            seam = 1;
        }
    }

    if(seam)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
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