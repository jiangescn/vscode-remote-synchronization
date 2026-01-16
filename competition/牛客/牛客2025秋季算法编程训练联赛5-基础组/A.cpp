#include <bits/stdc++.h>
using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    string a;
    string b;
    cin >> a >> b;

    int sum = abs(m - n);

    for (int i = 0; i < min(m, n); i++)
    {
        if(a[i] != b[i]) sum++;
    }
    cout << sum << endl;
}