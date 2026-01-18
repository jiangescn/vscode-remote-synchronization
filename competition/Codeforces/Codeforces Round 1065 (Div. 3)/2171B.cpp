#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }

        if(a[1] != -1 && a[n] != -1)
        {
            cout << abs(a[1] - a[n]) << endl;
            for (int i = 1; i <= n; i++)
            {
                if(i != 1)
                    cout << " ";
                if(a[i] == -1)
                {
                    cout << 0;
                }
                else
                {
                    cout << a[i];
                }
            }
            cout << endl;
        }

        if (a[1] != -1 && a[n] == -1)
        {
            cout << 0 << endl;
            for (int i = 1; i < n; i++)
            {
                if (a[i] == -1)
                {
                    cout << 0;
                }
                else
                {
                    cout << a[i];
                }
                cout << " ";
            }
            cout << a[1];
            cout << endl;
        }

        if (a[1] == -1 && a[n] != -1)
        {
            cout << 0 << endl;
            cout << a[n];
            for (int i = 2; i <= n; i++)
            {
                cout << " ";
                if (a[i] == -1)
                {
                    cout << 0;
                }
                else
                {
                    cout << a[i];
                }
            }
            cout << endl;
        }

        if (a[1] == -1 && a[n] == -1)
        {
            cout << abs(a[1] - a[n]) << endl;
            for (int i = 1; i <= n; i++)
            {
                if (i != 1)
                    cout << " ";
                if (a[i] == -1)
                {
                    cout << 0;
                }
                else
                {
                    cout << a[i];
                }
            }
            cout << endl;
        }
    }
    return 0;
}