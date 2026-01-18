#include <iostream>
#include <vector>
using namespace std;
int n, m, k;
vector<vector<int>> s;
vector<int> vi;


int sum = 0;
int A = 0, B = 0;

void dfs(int arr)
{
    if (s[arr].empty())
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

int si()
{
    int preA = A, preB = B;
    A = 0, B = 0;
    for (int i = 1; i <= m+n; i++)
    {
        if(i <= n && vi[i] == 1)
        {
            A++;
        }
        if(i > n && i <= n+m && vi[i] == 1)
        {
            B++;
        }
    }

    sum += (A- preA) * (B - preB);
    //cout << (A - preA) << " * " << (B - preB) <<endl;
}

int main()
{
    cin >> n >> m >> k;

    s.resize(n + m + 1);
    vi.resize(n + m + 1, 0);
    for (int i = 0; i < k; i++)
    {
        int u, v;
        cin >> u >> v;

        s[u].push_back(v+n);
        s[v+n].push_back(u);
    }

    int count = 0;
    for (int i = 1; i <= n+m; i++)
    {
        if (vi[i] == 0)
        {
            count++;
            dfs(i);
            si();
        }
        
    }

    //cout << sum - k << endl;

    if ((sum - k) % 2)
        cout << "Arkham" << endl;
    else
        cout << "Yightek" << endl;
    return 0;
}