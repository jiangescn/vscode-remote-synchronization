#include <iostream>
#include <vector>
using namespace std;

int lower_bound(vector<int>& a, int target)
{
    int left = 0, right = a.size();
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if(a[mid] >= target)
        {
            right = mid - 1;
        }
        else 
        {
            left = mid + 1;
        }
    }
    return left;
}

int main()
{
    vector<int> s = { 2, 5, 7, 13, 42, 54, 75, 85, 89, 93, 234 };
    int target = 13;
    
    cout << lower_bound(s, target) << endl;
}