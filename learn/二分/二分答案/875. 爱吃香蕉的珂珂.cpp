// https://leetcode.cn/problems/koko-eating-bananas/description/
#include <iostream>
#include <vector>
using namespace std;

int H;

bool check(vector<int>& banana, int speed)
{
    int len = banana.size();

    int ans = 0;

    for (int i = 0; i < len; i++)
    {
        ans += (banana[i] + speed - 1) / speed;
    }
    if(ans <= H) return true;
    else return false;
}

int main()
{
    int n;
    cin >> n;
    vector<int> banana(n);

    int right = 0;
    int left = 1;

    for (int i = 0; i < n; i++)
    {
        cin >> banana[i];
        if(banana[i] > right) right = banana[i]; 
    }
    
    cin >> H;


    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if(check(banana, mid))
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