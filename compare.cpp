#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int x, y;
    cin >> x >> y;

    int time = y / 500;

    int rest = time % 5;
    int zhengshu = time / 5;


    if(rest & 1)
    {

    }
}  

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}