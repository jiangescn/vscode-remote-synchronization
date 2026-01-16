#include<bits/stdc++.h>
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

        if(n == 0)
        {
            cout << 1 << endl;
            continue;
        }
        else if(n == 1)
        {
            cout << 3 << endl;
        }
        else 
        {
            int a = 1, b = 1;
            for (int i = 0; i < n; i++)
            {
                int temp = b;
                b = a + b;
                a = temp;
            }

            cout << a + b << endl;
        }
        
        
    }
}