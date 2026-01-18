#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    
    if(x1 == x2)
        cout << x1 + 1 << " " << y1 << " " << x2 + 1 << " " << y2 << endl;
    else if(y1 == y2)
        cout << x1 << " " << y1 +1 << " " << x2 << " " << y2 +1 << endl;
    else
        cout << x1 << " " << y2 << " " << x2 << " " << y1 << endl;
    return 0;
}