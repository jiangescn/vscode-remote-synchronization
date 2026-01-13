#include <iostream>
#include <vector>
using namespace std;

#define int long long

signed main()
{
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        int dis = s[i] - s[i - 1];
        if(dis * a > b)
        {
            sum += b;
        }
        else
        {
            sum += a * dis;
        }
    }
    cout << sum << endl;
    return 0;
}