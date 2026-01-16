#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> yin(int x)
{
    vector<int> s;
    int i;
    for (i = 1; i * i < x; i++)
    {
        if(x % i == 0)
        {
            s.push_back(i);
            s.push_back(x/i);
        }
    }

    if(i * i == x)s.push_back(i); 
    return s;
}

signed main()
{
    int n;
    cin >> n;

    vector<int> s = yin(n);
    sort(s.begin(), s.end());

    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if(s[i]+1 == s[i+1])count++;
    }
    cout << count << endl;
    return 0;
}