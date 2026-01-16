#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;

        int a[200] = {0};
        int b[200] = {0};

        for (int i = 0; i < n; i++)
        {
            char c;
            cin >> c;
            a[c]++;
        }
        
        for (int i = 0; i < n; i++)
        {
            char c;
            cin >> c;
            b[c]++;
        }
        
        int diff = 0;

        for (int i = 0; i < 200; i++)
        {
            if(a[i]!=b[i])diff = 1;

            //cout << "A:" << a[i] << "B:" << b[i] << endl;
        }
        
        if(diff)cout << "NO" << endl;
        else cout << "YES" << endl;

    }
}