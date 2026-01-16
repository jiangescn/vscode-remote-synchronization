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
        vector<int> s(n+1);
        vector<int> count(k+1, 0);
        int kk = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
            if(s[i] == k)
            {
                kk++;
            }
            else if(s[i] < k)
            {
                count[s[i]]++;
            }
            
        }

        int hide = 0;
        for (int i = 0; i < k; i++)
        {
            if(count[i]==0)hide++;
        }
        cout << max(kk, hide) << endl;
        
    }
}