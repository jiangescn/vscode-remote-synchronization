#include <iostream>
#include <vector>
using namespace std;

#define int long long

signed main()
{
    int n;
    cin >> n;

    vector<int> s(n+1);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        s[i] += s[i - 1];
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     cout << s[i] << " ";
    // }cout << endl;

    int Max = 0;
    for (int i = 0; i < 7; i++)
    {
        int l = -1;
        int r = -1;

        for (int k = 0; k <= n; k++)//0!!!!!
        {
            if(s[k] % 7 == i)
            {
                l = k;
                break;
            }
        }


        for (int k = n; k >= 0; k--)//0
        {
            if(s[k] % 7 == i)
            {
                r = k;
                break;
            }
        }

        if (l != -1 && r != -1 && l < r)
        {
            Max = max(Max, r - l);
        }
    }
    cout << Max << endl;
    return 0;
}