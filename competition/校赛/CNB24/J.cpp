#include <bits/stdc++.h>
using namespace std;
#define int long long

bool isPrime(int x)
{
    if(x < 2) return false;
    if(x == 2) return true;
    if(x % 2 == 0) return false;
    for(int i = 3; i * i <= x; i += 2)
    {
        if(x % i == 0)return false;
    }
    return true;
}

signed main()
{
    int n;
    cin >> n;
    string s = to_string(n);

    if(isPrime(n))
    {
        cout << 0 << endl;
        return 0;
    }

    int len = s.size();
    int tot = 1 << len;
    vector<string> sub;
    for (int mask = 1; mask < tot; mask++)
    {
        string temp = "";
        for (int i = 0; i < len; i++)
        {
            if(mask & (1 << i))
            {
                temp += s[i];
            }
        }
        sub.push_back(temp);
    }

    int Max = 0;
    for (int i = 0; i < sub.size(); i++)
    {
        int cur = stoll(sub[i]);
        if(isPrime(cur))
        {
            Max = max(Max, (long long)sub[i].size());
        }
    }
    
    if(Max > 0)
    {
        cout << len - Max << endl;
    }
    else
    {
        cout << -1 << endl;
    }
    return 0;
}