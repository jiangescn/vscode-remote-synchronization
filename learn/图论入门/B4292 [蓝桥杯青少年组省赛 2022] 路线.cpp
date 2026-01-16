#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<vector<int>> s;
vector<bool> vi;
vector<int> ans;
queue<int> q;

void bfs()
{
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int co : s[x])
        {
            if (vi[co] == 0)
            {
                q.push(co);
                vi[co] = true;
                ans[co] = ans[x] + 1;
            }
        }
    }
}

int main()
{
    cin >> n >> m;

    s.resize(n + 1);
    vi.resize(n + 1, false);
    ans.resize(n + 1, -1);

    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
        s[b].push_back(a);
    }
    q.push(n);
    ans[n] = 0;
    vi[n] = 1;

    bfs();

    for (int i = 1; i < n; i++)
    {
        if(i != 1) cout << " ";
        cout << ans[i];
    }
    return 0;    
}