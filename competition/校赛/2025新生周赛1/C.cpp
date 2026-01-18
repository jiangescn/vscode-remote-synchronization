#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int q;
    cin >> q;
    map<int, int> cnt; 

    for (int i = 0; i < q; i++)
    {
        int op;
        cin >> op;

        if (op == 1)
        {
            int x, y;
            cin >> x >> y;
            cnt[x] += y; 
        }
        else if (op == 2)
        {
            int x, y;
            cin >> x >> y;
            if (cnt.find(x) != cnt.end())
            {                           
                cnt[x] = max(0LL, cnt[x] - y);
                if (cnt[x] == 0)
                {
                    cnt.erase(x);
                }
            }
        }
        else if (op == 3)
        {
            for (auto it = cnt.begin(); it != cnt.end();)
            {
                if (it->second > 1)
                {
                    it->second = 1;
                }
                if (it->second == 0)
                {
                    it = cnt.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
        else if (op == 4)
        {
            int x;
            cin >> x;
            if (cnt.find(x) != cnt.end())
            {
                cout << cnt[x] << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        }
    }
    return 0;
}