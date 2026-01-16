// https://www.luogu.com.cn/problem/P5738
#include <iostream>
#include <climits>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    double n, m;
    cin >> n >> m;


    double Max = 0;
    for (int i = 0; i < n; i++)
    {
        double sum = 0;
        double cur_max = INT_MIN, cur_min = INT_MAX;
        for (int j = 0; j < m; j++)
        {
            double a;
            cin >> a;
            sum += a;
            cur_max = max(cur_max, a);
            cur_min = min(cur_min, a);
        }
        sum = sum - (cur_max + cur_min);

        Max = max(Max, sum);
    }
    cout << fixed << setprecision(2) << Max / (m - 2) << endl;
    return 0;
}