#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define int long long

signed main()
{
    int n, k;
    cin >> n >> k;

    vector<int> s(n+1);
    map<int, int> p;
    int ans = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    for (int i = 1; i <= n; i++)
    {
        s[i] += s[i-1];
    }

    for (int i = 1; i <= n; i++)
    {
        p[s[i - 1]]++;
        int t = s[i] - k;
        ans += p[t];
    }
    
    cout << ans <<endl;
    return 0;   
    
}