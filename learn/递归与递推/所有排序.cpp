#include <bits/stdc++.h>
using namespace std;
vector<int> s = {1, 2, 3};
vector<vector<int>> ans;

void f(int i)
{
    if (i == s.size())
    {
        ans.push_back(s);
    }

    else
    {
        for (int j = i; j < s.size(); j++)
        {
            swap(s[i], s[j]);
            f(i + 1);
            swap(s[i], s[j]);
        }
    }
}

int main()
{
    f(0);

    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            if (j != 0)
            {
                cout << " ";
            }
            cout << ans[i][j];
        }
        cout << endl;
    }
    return 0;
}