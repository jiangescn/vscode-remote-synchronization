#include <iostream>
#include <vector>
using namespace std;

int M;

bool check(vector<int>& nums,int large)
{
    int counts = 1;
    int sum = 0;
    for (int num : nums)
    {
        if(sum + num <= large)
        {
            sum += num;
        }
        else
        {
            counts++;
            sum = num;
            if (num > large)
            {
                return false;
            }
        }
    }
    if(counts <= M)return true;
    else return false;
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    int right = 0;
    int left = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
        right += nums[i];
    }

    cin >> M;

    while(left<=right)
    {
        int mid = left + (right - left) / 2;
        if(check(nums, mid))
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    cout << left << endl;


}