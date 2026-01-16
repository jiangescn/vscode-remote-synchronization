#include <iostream>
#include <vector>
using namespace std;
int n, m;
vector<vector<int>> s;
vector<int> vi;

void dfs(int cur, int dep)
{
    if (vi[cur] != 0)
        return;
    vi[cur] = dep;
    for (int co : s[cur])
    {
        dfs(co, dep);
    }
}

int main()
{

    cin >> n >> m;
    s.resize(n + 1);
    vi.resize(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        s[b].push_back(a);
    }

    for (int i = n; i; i--)
    {
        dfs(i, i);
    }

    for (int i = 1; i <= n; i++)
    {
        if (i != 1)
            cout << " ";
        cout << vi[i];
    }

    cout << endl;
    return 0;
}