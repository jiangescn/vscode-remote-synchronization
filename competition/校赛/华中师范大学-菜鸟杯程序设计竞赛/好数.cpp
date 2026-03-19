#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;
#define int long long

void solve()
{
    int l, r;
    cin >> l >> r;
    int del = r - l + 1;
    l--;
    

    int count1 = 0, count2 = 0;
    while(l)
    {
        count1++;
        l /= 2;
    }
    while(r)
    {
        count2++;
        r /= 2;
    }
    cout << del - (count2 - count1) << endl;

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}