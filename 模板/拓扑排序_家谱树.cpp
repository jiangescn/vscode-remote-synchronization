#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> tops(vector<vector<int>> s, vector<int> ru, int n)
{
    queue<int> q;
    vector<int> toposort;
    for (int i =  1; i <= n; i++)
    {
        if(!ru[i])
        {
            q.push(i);
        }
    }

    while(!q.empty())
    {
        int temp = q.front();
        q.pop();
        toposort.push_back(temp);
        for (int it: s[temp])
        {
            if(!(--ru[it]))
            {
                q.push(it);
            }
        }
    }

    return toposort;
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> s(n + 5);
    vector<int> ru(n + 5);
    for (int i = 1; i <= n; i++)
    {
        int v;
        do
        {
            cin >> v;
            if(v)
            {
                s[i].push_back(v);
                ru[v]++;
            }
        }while(v);
    }

    vector<int> toposort = tops(s, ru, n);

    for (int i = 0; i < toposort.size(); i++)
    {
        cout << toposort[i] << " ";
    }
    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

// 拓扑排序的步骤：
//
// 计算每个点的入度。
// 入度为 0 就加入队列。
// 当队列不为空则循环：
//         取出队首元素并输出。
//         遍历队首元素的连边，对应节点的入度 −1。
//         当对应的节点入度为 0 就加入队列。