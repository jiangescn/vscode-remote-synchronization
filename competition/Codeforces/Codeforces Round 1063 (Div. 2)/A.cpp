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
        vector<int> s(n+1);
        for (int i = 1; i <= n; i++)
        {
            cin >> s[i];
        }

        sort(s.begin(), s.end());
        bool found = false;
        for (int i = 1; i <= n; i++)
        {
            if(i % 2 || i == n)
            {
                continue;
            }
            if(s[i] != s[i+1])
            {
                found = true;
                break;
            }
        }
        
        if(found)
        {
            cout << "No" << endl;
        }
        else
        {
            cout << "Yes" << endl;
        }
        
    }
}
