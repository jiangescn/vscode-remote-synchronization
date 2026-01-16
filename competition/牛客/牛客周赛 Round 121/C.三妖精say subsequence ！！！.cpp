#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 998244353;

signed main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<char, int> da;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        da[s[i]]++;
    }
    
    //cout << "diff:" << da.size() << endl;

    n = da.size();
    if(n < 3)
    {
        cout << 0 << endl;
        return 0;
    }

    int sum = 0;
    
    for (auto i: da)
    {
        for (auto j: da)
        {
            if (i.first == j.first)
            {
                continue;
            }
            for (auto k: da)
            {
                if(k.first == j.first || k.first == i.first)
                {
                    continue;
                }
                int temp = (i.second % N) * (j.second % N);
                temp = temp * (k.second % N) % N;
                sum += temp;
                sum %= N;
            }
        }
    }
    
    
    cout << sum << endl;
    return 0;    

}