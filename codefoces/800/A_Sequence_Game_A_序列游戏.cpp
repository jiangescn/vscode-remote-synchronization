#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> s(n + 1);
        int Max = INT_MIN;
        int Min = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
            if (s[i] > Max)
            {
                Max = s[i];
            }
            if (s[i] < Min)
            {
                Min = s[i];
            }
        }
        // cout << "Max:" << Max << " Min:" << Min << endl;

        int x;
        cin >> x;
        // cout << "compare with:" << x << endl;
        if (x >= Min && x <= Max)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}