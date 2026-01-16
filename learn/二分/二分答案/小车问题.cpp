// https://www.luogu.com.cn/problem/P1258
#include <bits/stdc++.h>
using namespace std;

int main()
{
    double s, s1, s2, v1, v2, t1, t2, mid;
    double a, b;
    cin >> s >> v1 >> v2;
    s1 = 0;
    s2 = s;

    do 
    {
        mid = s1 + (s2 - s1) / 2.0;
        a = mid / v2;
        b = (mid - a * v1) / (v1 + v2);
        t1 = a + (s - mid) / v1;
        t2 = a + b + (s - (a + b) * v1) / v2;
        if(t1 < t2)
        {
            s2 = mid;
        }
        else
        {
            s1 = mid;
        }
    }
    while(fabs(t1 - t2) > 1e-8);

    cout << fixed << setprecision(6) << t1 << endl;
    return 0;
}