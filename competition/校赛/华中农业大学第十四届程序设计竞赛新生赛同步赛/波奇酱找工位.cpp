#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n, m, k;
    cin >> n >> m >> k;
    int x[200];
    int y[200];
    for (int i = 0; i < k; i++)
    {
        int a, b;
        cin >> x[i] >> y[i];
    }


    pair<int, int> position;
    vector<int> ans;
    vector<int> ansx;
    vector<int> ansy;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int Min = 999;
            for (int l = 0; l < k; l++)
            {
                int dis = abs(i - x[l]) + abs(j - y[l]);
                if(dis < Min)
                {
                    Min = dis;
                    position.first = i, position.second = j;
                }
            }
            ans.push_back(Min);
            ansx.push_back(position.first);
            ansy.push_back(position.second);
        }
    }

    int Max = 0;
    for (int i = 0; i < ans.size(); i++)
    {
        if(ans[i] > Max)
        {
            Max = ans[i];
            position.first = ansx[i];
            position.second = ansy[i];
        }
    }
    
    cout << Max << endl;
    cout << position.first << " " << position.second << endl;
}