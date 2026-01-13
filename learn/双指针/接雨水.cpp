#include <vector>
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> heights(n);

    for (int i = 0; i < n; i++)
    {
        cin >> heights[i];
    }

    int left = 1, right = n - 2;
    int lmax = heights[0], rmax = heights[n - 1];

    int water = 0;

    while(left <= right)
    {
        if(lmax <= rmax)
        {
            water += max(0, lmax - heights[left]);
            lmax = max(lmax, heights[left++]);
        }
        else
        {
            water += max(0, rmax - heights[right]);
            rmax = max(rmax, heights[right--]);
        }
    }

    cout << water << endl;
}