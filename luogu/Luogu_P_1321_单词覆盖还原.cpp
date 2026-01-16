#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    string s;
    cin >> s;
    
    int boy = 0, girl = 0;

    for (int i = 0; i < s.size(); i++)
    {
        if(s[i] == 'b' || s[i + 1] == 'o' || s[i + 2] == 'y')
        {
            boy++;
        }
        if(s[i] == 'g' || s[i + 1] == 'i' || s[i + 2] == 'r' || s[i + 3] == 'l')
        {
            girl++;
        }
    }
    
    cout << boy << endl;
    cout << girl << endl;
    return;
}

signed main()
{
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}