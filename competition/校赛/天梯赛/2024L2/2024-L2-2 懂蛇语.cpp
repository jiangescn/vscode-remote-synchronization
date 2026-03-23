#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;
#define int long long

void solve()
{
    int n;
    cin >> n;
    // while(getchar() != '\n');
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    map<string, multiset<string>> data;
    for (int i = 1; i <= n; i++)
    {
        string idx = "";
        string s;
        // getline(cin >> ws, s);
        getline(cin, s);
        // cout << s << endl;
        for (int k = 0; k < s.size(); k++)
        {
            if (s[k] != ' ' && (k == 0 || s[k - 1] == ' '))
            {
                idx += s[k];
            }
        }
        data[idx].insert(s);
    }

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 1; i <= q; i++)
    {
        string idx = "";
        string s;
        // getline(cin >> ws, s);
        getline(cin, s);
        // cout << s << endl;
        // idx += s[0];
        for (int k = 0; k < s.size(); k++)
        {
            if (s[k] != ' ' && (k == 0 || s[k - 1] == ' '))
            {
                idx += s[k];
            }
        }

        int fir = 0;

        if (data[idx].empty())
        {
            cout << s << endl;
            continue;
        }
        else
        {
            for (auto it : data[idx])
            {
                if (fir)
                {
                    cout << '|';
                }
                cout << it;
                fir = 1;
            }
            cout << endl;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}