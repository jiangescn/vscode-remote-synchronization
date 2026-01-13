#include <bits/stdc++.h>
using namespace std;

bool chongfu(vector<int>& nums)
{
    unordered_set<int> seem;

    for (int num:nums)
    {
        if(!seem.insert(num).second)
        {
            return true;
        }
    }
    return false;
}

vector<int> findchongfu(vector<int>& nums)
{
    unordered_set<int> seem;
    vector<int> chongfu;

    for (int num : nums)
    {
        if(!seem.insert(num).second&&find(chongfu.begin(),chongfu.end(),num)==chongfu.end())
        {
            chongfu.push_back(num);
        }
    }
    return chongfu;
}

int main()
{
    vector<int> test1 = {1, 2, 3, 4, 5};
    vector<int> test2 = {1, 2, 3, 4, 4};
    vector<int> test3 = {3, 3, 3, 3, 3};
    vector<int> test4 = {1, 2, 3, 2, 1, 4};

    cout << "test1: " <<(chongfu(test1)?"have":"nothave") << endl; 
    cout << "test2: " <<(chongfu(test2)?"have":"nothave") << endl; 
    cout << "test3: " <<(chongfu(test3)?"have":"nothave") << endl; 
    cout << "test4: " <<(chongfu(test4)?"have":"nothave") << endl;

    auto duplicates2 = findchongfu(test2);
    auto duplicates3 = findchongfu(test3);
    auto duplicates4 = findchongfu(test4);

    cout << "\n重复元素检测结果:";
    cout << "\n测试2中的重复元素: ";
    for (int num : duplicates2)
        cout << num << " ";

    cout << "\n测试3中的重复元素: ";
    for (int num : duplicates3)
        cout << num << " ";

    cout << "\n测试4中的重复元素: ";
    for (int num : duplicates4)
        cout << num << " ";
}