#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    long long sum = 1;

    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;

        int x = b - a + 1;
        sum *= x;
    }

    //cout << sum << endl;

    if(sum <= 1e5)
    {
        cout << "NO TLE" << endl;
    }
    else if(sum <= 1e7)
    {
        cout << "POSSIBLE" << endl;
    }
    else 
    {
        cout << "TLE" << endl;
    }
}