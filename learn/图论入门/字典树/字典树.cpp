#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stack>
using namespace std;
#define int long long

const int N = 2e5 + 10;
int tree[N][27];
int e[N];
int p[N];
int cnt = 1;

void add(string s)
{
    int cur = 1;
    p[cur]++;
    for (int i = 0, path; i < s.size(); i++)
    {
        path = s[i] - 'a';
        if(tree[cur][path] == 0)
        {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
        p[cur]++;
    }
    e[cur]++;    
}

int find_word(string s)
{
    int cur = 1;
    for (int i = 0; i < s.size(); i++)
    {
        int path = s[i] - 'a';
        if (tree[cur][path] == 0)
        {
            return 0;
        }
        cur = tree[cur][path];
    }
    return e[cur];
}

int find_prefix(string s)
{
    int cur = 1;
    for (int i = 0; i < s.size(); i++)
    {
        int path = s[i] - 'a';
        if (tree[cur][path] == 0)
        {
            return 0;
        }
        cur = tree[cur][path];
    }
    return p[cur];
}

void dlt(string s)
{
    if (find_word(s) > 0)
    {
        int cur = 1;
        for (int i = 0, path; i < s.size(); i++)
        {
            path = s[i] - 'a';
            if(--p[tree[cur][path]] == 0)
            {
                tree[cur][path] = 0;
                return;
            }
            cur = tree[cur][path];
        }
        e[cur]--;
    }
}

void solve()
{
    

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}