#include <bits/stdc++.h>
using namespace std;

vector<int> nums = {1, 1, 2, 2, 2, 3};
vector<int> vi;
map<int, int> cnt;
vector<vector<int>> ans;

void f(vector<int> s, int deep)
{
    if(deep == vi.size())
    {
        ans.push_back(s);
        return;
    }

    f(s, deep + 1);
    for (int i = 0; i < cnt[vi[deep]]; i++)
    {
        s.push_back(vi[deep]);
        f(s, deep + 1);
    }
    return;
}

int main()
{
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < nums.size(); i++)
    {
        if(!cnt[nums[i]])
        {
            vi.push_back(nums[i]);
        }
        cnt[nums[i]]++;
    }

    f(vector<int> (), 0);
    for (auto &subset : ans)
    {
        for (int num : subset)
        {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}