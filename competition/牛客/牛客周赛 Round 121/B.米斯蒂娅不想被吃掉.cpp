#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    int n, x;
    cin >> n >> x;
    vector<int> s(n + 1);
    queue<pair<int, int>> pa;
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    for (int i = 1; i <= n; i++)
    {
        pa.push({i, s[i]});
        sum += s[i];

        while (!pa.empty() && (pa.front().second == 0 || pa.front().first + 2 <= i))
        {
            sum -= pa.front().second;
            pa.pop();
        }

        if (sum < x)
        {
            cout << "No" << endl;
            return;
        }

        int temp = x;
        while(temp)
        {
            if(pa.front().second > temp)
            {
                pa.front().second -= temp;
                sum -= temp;
                temp = 0;
            }
            else
            {
                temp -= pa.front().second;
                sum -= pa.front().second;
                pa.pop();
            }
        }
    }
    cout << "Yes" << endl;
    return;
}

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        solv();        
    }
}