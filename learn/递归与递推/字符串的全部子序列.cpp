#include <bits/stdc++.h>
using namespace std;
vector<string> ans;
int tar;

void dfs(vector<char> &s, string cur, int deep)
{
    if (deep == tar)
    {
        ans.push_back(cur); 
        return;
    }
    dfs(s, cur + s[deep], deep + 1);
    dfs(s, cur, deep + 1);
    return;
}

int main()
{
    string ls;
    cin >> ls;
    map<char, bool> vi;
    vector<char> s;
    for (int i = 0; i < ls.size(); i++)
    {
        if (!vi[ls[i]])
            s.push_back(ls[i]);
        vi[ls[i]] = true;
    }

    tar = s.size();
    dfs(s, "", 0);

    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << endl;
    }
    return 0;
}