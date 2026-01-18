#include <bits/stdc++.h>
using namespace std;
#define int long long

// vector<int> vi;
// vector<int> dep;
// vector<int> ans;

// void dfs(int cur, int deep)
// {
//     // cout << cur << " deep :" << deep << endl;
//     if (s[cur].empty())
//     {
//         return;
//     }

//     dep[deep]++;
//     ans[deep] = cur;

//     vi[cur] = 1;
//     for (int co : s[cur])
//     {
//         if (vi[co] == 0)
//         {
//             dfs(co, deep + 1);
//         }
//     }
//     return;
// }

// signed main()
// {
//     int t;
//     cin >> t;
//     while (t--)
//     {
//         int n;
//         cin >> n;
//         s.resize(n + 1, {});
//         vi.resize(n + 1, 0);
//         dep.resize(n + 1, 0);
//         ans.resize(n + 1, 0);
//         for (int i = 0; i < n - 1; i++)
//         {
//             int a, b;
//             cin >> a >> b;
//             s[a].push_back(b);
//             s[b].push_back(a);
//         }

//         if (n < 3)
//         {
//             cout << "2 0" << endl;
//             continue;
//         }

//         dfs(1, 1);

//         vector<int> fr(n + 1);

//         int frMax = 0;
//         int po;
//         for (int i = 2; i < n - 1; i++)
//         {
//             fr[i] = dep[i - 2] +  dep[i + 2];
//             cout << fr[i] << " ";
//             cout << endl;
//             if(fr[i] > frMax)
//             {
//                 frMax = fr[i];
//                 po = i;
//             }
//         }

//         cout << "deep:" << endl;
//         for (int i = 0; i < n; i++)
//         {
//             cout << "deep" << i << ":" << dep[i] << endl;
//         }

//         cout << po << " " << frMax << endl;
//     }
// }

int how(int x, vector<vector<int>>& s)
{
    int sum = 0;
    for (int co : s[x])
    {
        //cout << co << " have: " << s[co].size() << endl;
        sum += s[co].size();
    }
    return sum - s[x].size();
}

signed main()
{

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<vector<int>> s(n + 1);
        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;
            s[a].push_back(b);
            s[b].push_back(a);
        }

        if (n < 3)
        {
            cout << "1 0" << endl;
            continue;
        }

        vector<int> fr(n + 1);
        int Max = 0, Maxi = 0;
        for (int i = 1; i < n; i++)
        {
            fr[i] = how(i, s);
            if (fr[i] > Max)
            {
                Max = fr[i];
                Maxi = i;
            }
        }

        // for (int i = 0; i < s[2].size(); i++)
        // {
        //     cout << s[2][i] << " ";
        // }cout << endl;
        

        cout << Maxi << " " << Max << endl;
    }
}