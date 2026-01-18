#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        vector<int> b(n + 1);
        int ji = 0;
        int ou = 0;

        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> b[i];
        }

        int end;
        for (int i = 1; i <= n; i++)
        {
            if (a[i] != b[i])
            {
                if (i % 2)
                {
                    ji++;
                    end = 1;
                }
                else
                {
                    ou++;
                    end = 0;
                }
            }
        }
        
        if((ji - ou) % 2 == 0)
        {
            cout << "Tie" << endl;
        }
        else
        {
            if(end)
            {
                cout << "Ajisai" << endl;
            }
            else
            {
                cout << "Mai" << endl;
            }
        }
    }
    sda
}