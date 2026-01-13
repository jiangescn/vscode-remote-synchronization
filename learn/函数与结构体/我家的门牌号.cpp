// https://www.luogu.com.cn/problem/B2133
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int i = 1;
    while(1)
    {
        for (int j = 1; j <= i; j++)
        {
            if((1+i) * i / 2 - j * 3 == n)
            {
                cout << j << " " << i;
                return 0;
            }
        }
        i++;
    }
    return 0;
}