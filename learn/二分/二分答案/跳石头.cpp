// https://www.luogu.com.cn/problem/P2678
#include <iostream>
#include <vector>
using namespace std;
int r, n, m;
vector<int> s;

bool check(int x)
{
    int mv = 0;
    int now = 0, next = 0;
    while(next < n+1)
    {
        next++;
        if(s[next] - s[now] < x)
        {
            mv++;
        }
        else
        {
            now = next;
        }
    }
    
    if(mv > m) return false;
    else return true;
}


int main()
{
    cin >> r >> n >> m;
    s.push_back(0);
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        s.push_back(a);
    }
    s.push_back(r);

    int l = 0;
    while(l <= r)
    {
        int mid = l + (r - l) / 2;
        if(check(mid))
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    cout << r << endl;
    return 0;
}