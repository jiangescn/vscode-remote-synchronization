#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main ()
{
    string s;
    cin >> s;

    for (int i = 0; i < s.length(); i++)
    {
        char c = toupper(s[i]);
        cout << c;
    }
    
    return 0;

}