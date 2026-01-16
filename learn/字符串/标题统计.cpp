#include <iostream>
#include <cctype>
using namespace std;

int main()
{
    string s;
    getline(cin,s);

    int count = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if(!isblank(s[i]))count++;
    }
    cout << count <<endl;
    return 0;
}