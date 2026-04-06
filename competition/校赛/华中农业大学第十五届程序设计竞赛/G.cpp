#include <bits/stdc++.h>
using namespace std;
#define int long long

struct G
{
    int a;
    int b;
    int c;
};


void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) cin >> c[i];
    vector<G> s(1);

    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if(a[i] >= b[i])
        {
            sum += c[i];
            continue;
        }
        s.push_back({a[i], b[i], c[i]});
    }

    sort(s.begin() + 1, s.end(), [&](G x, G y){
        if(x.b == y.b)
        {
            return x.c > y.c;
        }
        return x.b < y.b;
    });

    int Max = 0;
    for (int i = 1; i < s.size(); i++)
    {
        Max = max(Max, s[i].c);
        s[i].c = Max;
    }

    // for (int i = 1; i <= s.size(); i++)
    // {
    //     cout << s[i].b << " " << s[i].c << endl;
    // }    

    while(q--)
    {
        int x;
        cin >> x;

        int l = 0;
        int r = s.size() - 1;

        int ans = 0;


        while(l <= r)
        {
            int mid = (l + r) / 2;
            if(s[mid].b > x)
            {
                r = mid - 1;
                ans = s[mid - 1].c;
            }
            else
            {
                l = mid + 1;
            }
        }
        
        cout << sum + s[r].c << endl;
        
    }

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int _ = 1;
    cin >> _;
    while(_--)
    {
        solve();
    }
    return 0;
}