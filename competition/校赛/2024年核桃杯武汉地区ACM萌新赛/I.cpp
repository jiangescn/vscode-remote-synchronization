#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> s(n);
        int Max = INT_MIN;
        int Min = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
            Max = max(Max, s[i]);
            Min = min(Min, s[i]);
        }

        int qm = Max - s[0];
        int hz = s[s.size()-1] - Min;
        int ll = (s[s.size() - 1] - s[0]) * 2;

        //cout << qm << " " << hz << " " << ll << endl;

        int Big = max({qm, hz, ll});

        cout << s[0] - s[s.size() - 1] + Big << endl;
    }
}