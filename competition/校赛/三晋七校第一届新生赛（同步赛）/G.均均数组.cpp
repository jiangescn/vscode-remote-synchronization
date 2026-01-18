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
        vector<int> s(n);
        long long sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
            sum += s[i];
        }
        if(sum % n)
        {
            cout << "No" << endl;
        }
        else
        {
            cout << "Yes" << endl;
        }
        
    }
}