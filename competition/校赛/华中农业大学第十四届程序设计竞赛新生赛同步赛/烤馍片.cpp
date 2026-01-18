#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n;
    cin >> n;
    vector<pair<int, char>> s(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i].first >> s[i].second;
    }

    int x;
    cin >> x;
    if(x == 1)
    {
        char c;
        cin >> c;
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if(s[i].second == c)
            {
                count += s[i].first;
            }
        }
        cout << count << endl;
    }
    else
    {
        char a, b;
        cin >> a >> b;
        if(a == b)
        {
            int count = 0;
            for (int i = 0; i < n; i++)
            {
                if (s[i].second == a)
                {
                    count += s[i].first - 1;
                }
            }
            
            cout << count << endl;
        }
        else
        {
            int count = 0;
            for (int i = 0; i < n - 1; i++)
            {
                if(s[i].second == a && b == s[i + 1].second)
                {
                    count++;
                }
            }
            cout << count << endl;            
        }
    }
}
