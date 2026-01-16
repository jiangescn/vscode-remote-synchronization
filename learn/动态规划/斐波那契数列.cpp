#include <iostream>
#include <vector>
using namespace std;

vector<int> dp(10000, -1);

int fb(int n)
{
    if(n == 0)
    {
        return 0;
    }
    if(n == 1)
    {
        return 1;
    }
    if(dp[n] != -1)
    {
        return dp[n];
    }
    int ans = fb(n - 1) + fb(n - 2);
    dp[n] = ans;
    return ans;
}

int main()
{
    int n;
    cin >> n;
    cout << fb(n) << endl;
}