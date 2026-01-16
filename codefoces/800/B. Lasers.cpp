#include <iostream>
using namespace std;

int main()
{
    int o;
    cin >> o;
    for (int l = 0; l < o; l++)
    {
        int x, n;
        cin >> x >> n;

        if(n%2 == 0)cout << 0 << endl;
        else cout << x <<endl;
    }
    return 0;
}