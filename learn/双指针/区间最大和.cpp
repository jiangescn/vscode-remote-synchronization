// https://www.luogu.com.cn/problem/P5745
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int l = 1, r = 1;
    long long sum = 0;
    long long Max = 0;
    int maxl, maxr;
    while (l < n && r < n)
    {
        if (sum + s[r] <= m)
        {
            //cout << "+:" << s[r] << endl;
            sum += s[r++];
        }
        else
        {
            //cout << "-:" << s[l] << endl;
            sum -= s[l++];
        }
        if (Max < sum && sum <= m)
        {
            Max = sum;
            maxl = l;
            maxr = r - 1;
            //cout << "l:" << l << "   r:" << r << endl;
        }
    }

    cout << maxl << " " << maxr << " " << Max << endl;
}