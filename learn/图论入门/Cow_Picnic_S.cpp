#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

int k, n, m;
vector<vector<int>> s;
vector<int> cow;
vector<int> vi;

int count;

int bfs(int cur)
{
    // cout << "begin: " << cur << endl;
    vector<int> vi(n + 1, 0);
    queue<int> q;

    vi[cur] = 1;
    q.push(cur);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        vi[x] = 1;

        if (cow[x])
        {
            count++;
            // cout << "found cow:" << x << endl;
        }

        for (int co : s[x])
        {

            if (vi[co] == 0)
            {
                q.push(co);
                vi[co] = 1;
            }
        }
    }
    return 0;
}

int main()
{
    // 存图
    cin >> k >> n >> m;
    s.resize(n + 1);
    cow.resize(n + 1);
    vi.resize(n + 1);
    for (int i = 1; i <= k; i++)
    {
        int a;
        cin >> a;
        cow[a] = 1;
    }
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        s[b].push_back(a);
    }

    // 有奶牛的牧场
    int have_cow = 0;
    for (int i = 1; i <= n; i++)
    {
        if (cow[i] == 1)
            have_cow++;
    }

    // bfs
    int ans = 0;
    for (int i = n; i >= 1; i--)
    {
        count = 0;
        bfs(i);
        if (count == have_cow)
        {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}