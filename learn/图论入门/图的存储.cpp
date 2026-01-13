#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> s(n + 1, vector<int>(n + 1));
    vector<vector<int>> u(n + 1);
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a][b]++;
        s[b][a]++;

        u[a].push_back(b);
        u[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << u[i].size();
        sort(u[i].begin(),u[i].end());
        for (int j = 0; j < u[i].size(); j++)
        {
            cout << ' ' << u[i][j];
        }
        cout << endl;
    }
}