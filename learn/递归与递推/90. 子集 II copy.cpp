#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> nums = {1, 1, 2, 2, 2, 3};
vector<vector<int>> ans;
vector<int> path;

void f(int i, int size)
{
    if(i == nums.size())
    {
        vector<int> temp;
        for (int j = 0; j < size; j++)
        {
            temp.push_back(path[j]);
        }
        ans.push_back(temp);
    }
    else
    {
        int j = i + 1;
        while(j < nums.size() && nums[j] == nums[i])
        {
            j++;
        }
        f(j, size);
        while(i < j)
        {
            path[size++] = nums[i];
            f(j ,size);
            i++;
        }
    }
}

int main()
{
    sort(nums.begin(), nums.end());
    path.resize(nums.size());
    f(0, 0);

    for (int i = 0; i < ans.size() ; i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            if(j != 0)cout << " ";
            cout << ans[i][j];
        }
        cout << endl;
    }
    return 0;
}