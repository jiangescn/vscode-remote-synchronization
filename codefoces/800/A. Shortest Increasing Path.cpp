#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int o;
    cin >> o;

    for (int l = 0; l < o; l++)
    {
        
        int x, y;
        cin >> x >> y;

        if(y > x)
        {
            cout << "2" << endl;
        }
        else if (y == 1||x == y+1||x == y)
        {
            cout << "-1" << endl;
        }
        else if(y == 0)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << "3" << endl;
        }
        
    }
    
    return 0;
}