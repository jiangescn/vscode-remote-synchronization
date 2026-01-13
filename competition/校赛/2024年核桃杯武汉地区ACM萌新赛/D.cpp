#include <iostream>
#include <vector>
using namespace std;

#define int long long

signed main()
{
    int n;
    cin >> n;
    int Max = 0;
    vector<int> s(n+1);
    vector<int> pre(n+1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    s[0] = s[1];
    for (int i = 1; i < n; i++)
    {
        pre[i] = s[i] - s[i - 1];
        Max = max(Max, pre[i]);
    }
    cout << Max << endl;
    return 0;   
}