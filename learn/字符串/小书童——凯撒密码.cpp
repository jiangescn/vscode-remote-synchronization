#include <iostream>
#include <string>
using namespace std;

int main() 
{
    int n;
    cin >> n;

    string s;
    cin >> s; 

    for (int ch : s) {
        int c = (ch + n);
        if (c > 'z') c -= 26;
        cout << (char)c;
    }
    cout << endl; 
    return 0;
}