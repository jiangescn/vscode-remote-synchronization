#include <bits/stdc++.h>
using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int a;
            cin >> a;
            if(a == 6)
            {
                count++;
            }
        }
    }

    if(count & 1)
    {
        cout << "Super Miner Fan_an tql" << endl;
    }
    else
    {
        cout << "Super Miner is Era2333" << endl;
    }
    return 0;
}