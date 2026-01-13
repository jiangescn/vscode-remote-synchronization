#include <iostream>
#include <vector>
using namespace std;

bool check(vector<int>& heights, int power)
{
    int len = heights.size();
    for (int i = 0; i < len - 1; i++)
    {
        if(heights[i + 1] > power)
        {
            power -= (heights[i + 1] - power);
        }
        else
        {
            power += (power - heights[i + 1]);
        }

        if(power < 0)
        {
            return false;
        }
    }
    
    return true;
}

int main ()
{
    int n;
    cin >> n;

    int left = 0;
    int right = 0;

    
    vector<int> heights(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cin >> heights[i];
        if(heights[i] > right)
        {
            right = heights[i];
        }
    }

    while(left <= right)
    {
        int mid = left + (right - left) / 2;

        if(check(heights, mid))
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    cout << left << endl;
    return 0;
}