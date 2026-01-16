#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> s(n + 1);
    vector<int> dat(m + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    int l = 1, r = 1;
    int count = 0;
    int Min = INT_MAX;
    int min_l = 0, min_r = 0;

    while (r <= n + 1)
    {
        // for (int i = 1; i <= m; i++)
        // {
        //     cout << dat[i] << " ";
        // }
        // cout << endl;
        // cout << count << endl;
        // cout << "l:" << l << "  r:" << r << "   cha" << r - l << endl;
        // cout << endl;

        if (count < m)
        {
            if (dat[s[r]] == 0)
            {
                count++;
            }
            dat[s[r]]++;
            r++;
        }
        else
        {
            dat[s[l]]--;
            if (dat[s[l]] == 0)
            {
                count--;
            }
            l++;
        }

        if (count == m)
        {
            //cout << "count" << endl;
            if (r - l < Min && r >= m)
            {
                min_l = l;
                min_r = r;
                Min = r - l;
            }
        }
    }
    cout << min_l << " " << min_r - 1 << endl;
}