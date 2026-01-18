#include <bits/stdc++.h>
using namespace std;

int compute(stack<int> &nums, stack<char> &ops)
{
    //反转
    vector<int> numVec;
    vector<char> opVec;

    while (!ops.empty())
    {
        opVec.push_back(ops.top());
        ops.pop();
    }
    reverse(opVec.begin(), opVec.end());

    while (!nums.empty())
    {
        numVec.push_back(nums.top());
        nums.pop();
    }
    reverse(numVec.begin(), numVec.end());


    int ans = numVec[0];
    for (int i = 0; i < opVec.size(); i++)
    {
        if (opVec[i] == '+')
        {
            ans += numVec[i + 1];
        }
        else
        {
            ans -= numVec[i + 1];
        }
    }
    return ans;
}

void mtp(char op, stack<int>& nums, stack<char>& ops, int cur)
{
    int n = nums.size();
    if(n == 0 || ops.top() == '+' || ops.top() == '-')
    {
        nums.push(cur);
        ops.push(op);
    }
    else
    {
        int topnum = nums.top();
        nums.pop();
        char topop = ops.top();
        ops.pop();
        if (topop == '*')
            cur = topnum * cur;
        else
            cur = topnum / cur;

        nums.push(cur);
        ops.push(op);
    }
}


int ccl(int& i, string& s)
{
    stack<char> ops;
    stack<int> nums;
    int cur = 0;
    while(i < s.size() && s[i] != ')')
    {
        if(isdigit(s[i]))
        {
            cur = cur * 10 + (s[i] - '0');
            i++;
        }
        else if(s[i] == '(')
        {
            i++;
            cur = ccl(i, s);
            
        }
        else
        {
            mtp(s[i], nums, ops, cur);
            i++;
            cur = 0;
        }
    }
    mtp('+', nums, ops, cur);
    return compute(nums, ops);
}

int main()
{
    string s;
    int i = 0;
    cin >> s;

    int result = ccl(i, s);
    cout << result << endl;
    return 0;
}