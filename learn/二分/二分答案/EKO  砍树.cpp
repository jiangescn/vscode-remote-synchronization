#include <iostream>
#include <vector>
using namespace std;

bool check(vector<int> &height, long long x, long long M)
{
    long long len = height.size();

    long long sum = 0;

    for (long long i = 0; i < len; i++)
    {
        if(x < height[i])sum +=  height[i] - x;
    }

    //cout << "sum=" << sum << endl; 

    if(sum >= M)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    long long N, M;
    cin >> N >> M;

    long long left = 0;
    long long right = 0;

    vector<int> height(N);
    for (long long i = 0; i < N; i++)
    {
        cin >> height[i];
        if(height[i] > right) right = height[i];
    }

    //if(check(height, 15, M))cout << "YES" << endl;

    while(left <= right)
    {
        //cout << "qwq" << endl;
        long long mid = left + (right - left) / 2;
        //cout << "mid = " << mid << endl;
        if(check(height, mid, M))
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    cout << right << endl;
    
}