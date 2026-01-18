#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

vector<vector<int>> s;

vector<int> ansdfs;
vector<int> ansbfs;
vector<int> vi;
queue<int> q;

void dfs(int arr)
{
    if(vi[arr] == 1)return;

    ansdfs.push_back(arr);
    vi[arr] = 1;
    
    // if(s[arr].empty())
    // {
    //     return;
    // }

    for (int co : s[arr])
    {
        if(vi[co] == 0)
        {
            dfs(co);
        }
    }
    return;
}

void bfs(int arr)
{
    q.push(arr);
    vi[arr] = true;
    int count = 0;
    while(!q.empty())
    {
        //cout << count++ << endl;
        int x = q.front();
        q.pop();
        ansbfs.push_back(x);

        for (int co: s[x])
        {
            if (vi[co] == false)
            {
                q.push(co);
                vi[co] = true;
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    s.resize(n+1);

    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].push_back(b);
    }

    for (int i = 1; i <= n; i++)
    {
        sort(s[i].begin(), s[i].end());
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 0; j < s[i].size(); j++)
    //     {
    //         cout << s[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    vi.assign(n + 1, false);
    dfs(1);

    for (int i = 0; i < ansdfs.size(); i++)
    {
        if(i != 0)cout << " ";
        cout << ansdfs[i];
    }
    cout << endl;

    vi.assign(n + 1, false);
    bfs(1);
    for (int i = 0; i < ansbfs.size(); i++)
    {
        if(i != 0)cout << " ";
        cout << ansbfs[i];
    }
    cout << endl;
}