#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long aj(int x1, int y1, int x2, int y2)
{
    long long a = (x2 - x1)*(x2 - x1);
    long long b = (y2 - y1) * (y2 - y1);
    long long ans = a + b;
    return ans;
}

int main()
{
    long long n;
    cin >> n;
    vector<long long> x(n);
    vector<long long> y(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
    }

    long long max1, max2;

    long long Max = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            long long dis = aj(x[i], y[i], x[j], y[j]);
            //cout << "dis:" << dis << endl;
            if(dis > Max)
            {
                //cout << "!!!!!" << endl;
                Max = dis;
                max1 = i, max2 = j;
            }
        }
    }
    //cout << "max1" << max1 << "max2" << max2 << endl;

    cout << x[max1] << " " << y[max1] << " " << x[max2] << " " << y[max2] << endl;
    
}