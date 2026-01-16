#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1E5 + 10;

struct sss
{
    int first;
    int second;
    int next;
};
vector<sss> maxs(N);
vector<bool> vi(N, false);

signed main()
{
    int n, d;
    cin >> n >> d;

    vector<int> t(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i];
        vi[t[i]] = true;
    }

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int fir = 0;
    int sec = 0;
    for (int i = n; i >= 1; i--)
    {
        if (s[i] > fir)
        {
            sec = fir;
            fir = s[i];
        }
        else if (s[i] > sec)
        {
            sec = s[i];
        }
        // cout << fir << " " << sec << endl;
        maxs[t[i]].first = fir;
        maxs[t[i]].second = sec;
    }

    int sum = 0;
    for (int i = 1; i <= d; i++)
    {
        int a;
        cin >> a;
        a--;
        if (a <= 0)
        {
            continue;
            ;
        }
        while (!vi[a] && a >= 0)
        {
            a--;
        }
        // cout << "Next : " << a << endl;
        if (a <= 0)
        {
            continue;
        }
        sum += maxs[a].first;
        sum += maxs[a].second;
    }
    cout << sum << endl;

    return 0;
}