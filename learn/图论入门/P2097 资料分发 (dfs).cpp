#include <iostream>
#include <vector>
using namespace std;
int n, m;
vector<vector<int>> s;
vector<int> vi;

void dfs(int arr)
{
    if(s[arr].empty())
    {
        return;
    }
    vi[arr] = 1;
    for (int co : s[arr])
    {
        if (vi[co] == 0)
        {
            dfs(co);
        }
    }
    return;
}

int main()
{
    cin >> n >> m;

    s.resize(n + 1);
    vi.resize(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        s[u].push_back(v);
        s[v].push_back(u);
    }

    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if(vi[i] == 0)
        {
            count++;
            dfs(i);
        }
    }
    cout << count << endl;
    return 0;
}