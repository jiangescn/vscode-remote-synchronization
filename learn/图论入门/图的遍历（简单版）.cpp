#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> s;
vector<bool> vi;
vector<int> memo;
vector<bool> computing;//！！！！！！！！

int dfs(int cur)
{
    vi[cur] = true;

    if (computing[cur])
    {
        return memo[cur] > 0 ? memo[cur] : cur;
    }

    if (memo[cur] != 0)
    {
        return memo[cur];
    }

    int maxnode = cur;

    for (int nb : s[cur])
    {
        if (!vi[nb])
        {
            maxnode = max(maxnode, dfs(nb));
        }
        else
        {
            maxnode = max(maxnode, memo[nb]);
        }
        if (maxnode == s.size() - 1)
            break;
    }

    memo[cur] = maxnode;
    return maxnode;
}

int main()
{
    int n, m;
    cin >> n >> m;

    s.resize(n + 1);
    memo.resize(n + 1, 0);

    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
    }

    for (int i = 1; i <= n; i++)
    {
        vi.assign(n + 1, false);
        if (memo[i] == 0)
        {
            memo[i] = dfs(i);
        }
        if (i != 1)
            cout << " ";
        cout << memo[i];
    }
    cout << endl;
    return 0;
}