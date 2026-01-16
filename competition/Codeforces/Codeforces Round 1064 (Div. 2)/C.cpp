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
        vector<int> s(n);
        int Max = 0;
        int Min = INT_MAX;
        int Mini;
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
            Max = max(Max, s[i]);
            if(s[i] < Min)
            {
                Min = s[i];
                Mini = i;
            }
        }


        if(n == 2)
        {
            cout << max(s[0], s[1]) << endl;
            continue; 
        }

        int sum = 0;

        int i = Mini;
        int l = (i - 1 + n) % n;
        int r = (i + 1) % n;

        while(l != r)
        {
            if(s[l] >= s[r])
            {
                sum += max(s[i],s[r]);
                //cout << "remove" << s[i] << endl;
                s[i] = -1;
                i = r;
                r = (i + 1) % n;
            }
            else
            {
                sum += max(s[i],s[l]);
                //cout << "remove" << s[i] << endl;
                s[i] = -1;
                i = l;
                l = (i - 1 + n) % n;
            }
        }
        cout << sum + Max << endl;
        
    }
}
