#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> a(n+1);
        vector<int> b(n+1);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++)
        {
            cin >> b[i];
        }

        int more = 0;
        int less = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] > b[i])
            {
                more += a[i] - b[i];
            }
            else if (a[i] < b[i])
            {
                less += b[i] - a[i];
            }
        }

        cout << more + 1 << endl;
        
        
    }
}