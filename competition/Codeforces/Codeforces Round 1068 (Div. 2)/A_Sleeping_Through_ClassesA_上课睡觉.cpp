#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int count = 0;
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            if(s[i] == '0')
            {
                if(count != 0)
                {
                    count--;
                }
                else
                {
                    ans++;
                }
            }
            else if (s[i] == '1')
            {
                count = k;
            }
            
        }
        cout << ans << endl;
    }
}