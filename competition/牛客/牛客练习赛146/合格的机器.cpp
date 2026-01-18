#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n;
    cin >> n;
    vector<int> s(n + 1);
    int sum = 0;
    int one = 0;
    int ji = 0;
    int ou = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        if(s[i] > 2)
        {
            sum += s[i] - 2;
        }

        if(s[i] == 1)
        {
            one++;
        }
    }


    if(sum - one >= 0)
    {
        if ((sum - one) % 2)
        {
            cout << n - 1 << endl;
        }
        else
        {
            cout << n << endl;
        }
    }
    else
    {
        cout << n - (one - sum) << endl;
    }

    return 0;
}