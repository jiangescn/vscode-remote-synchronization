#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    long long a;
    long long sum = 0;
    long long count = 0;
    while(cin >> a)
    {
        sum += a;
        count++;
    }
    cout << sum * (long long)pow(2, count - 1) << endl;
}