#include <iostream>
#include <vector>
using namespace std;
#define int long long

bool check(int x, vector<int>& s)
{
    int temp = x;
    for (int i = 1; i < s.size(); i++)
    {
        if(x > s[i])
        {
            x++;
        }
        else if(x < s[i])
        {
            x--;
        }
    }
    return x > temp;
}

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> s(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> s[i];
        }

        int l = 1, r = 1e9 + 10;
        while(l <= r)
        {
            int mid = l + (r - l) / 2;
            if(check(mid, s))
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        cout << l << endl;
    }
}