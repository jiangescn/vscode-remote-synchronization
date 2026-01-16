#include <bits/stdc++.h>
using namespace std;
#define int long long

void f(int i, vector<int>& s, vector<vector<int>>& group)   
{
    if(i == s.size())
    {
        group.push_back(s);        
    }

    for (int j = i; j < s.size(); j++)
    {
        swap(s[i], s[j]);
        f(i + 1, s, group);
        swap(s[i], s[j]);
    }
    return ;
}

void solve()
{
    int n, j, k;
    cin >> n >> j >> k;
    vector<int> s;
    vector<vector<int>> group;
    while(n != 0)
    {
        s.push_back(n % 10);
        n /= 10;
    }

    f(0, s, group);    

    sort(group.begin(), group.end());

    vector<int> a = group[j - 1];
    vector<int> b = group[k - 1];


    // for (int i = 0; i < a.size(); i++)
    // {
    //     cout << a[i] << " ";
    // }cout << endl;
    // for (int i = 0; i < b.size(); i++)
    // {
    //     cout << b[i] << " ";
    // }cout << endl;
    

    int A = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if(a[i] == b[i])A++;
    }
    int B = s.size() - A;

    cout << A << "A" << B << "B" << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}