#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i].first >> s[i].second;
    }
    sort(s.begin(), s.end(), [](pair<int, int> a, pair<int, int> b)
         { return a.second < b.second; });


    int las = 0;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (las <= s[i].first)
        {
            ans++;
            las = s[i].second;
        }
    }

    cout << ans << endl;
    return 0;
}
