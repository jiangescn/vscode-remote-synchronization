#include <iostream>
#include <string>
using namespace std;

int main()
{
    string a, b;
    cin >> a >> b;
    char x = a[a.size() - 1];
    char y = b[b.size() - 1];

    //cout << x << " " << y << endl;

    int n = x - '0';
    int m = y - '0';

    int ans = (m + n) % 10;
    
    cout << ans << endl;
    return 0;
}