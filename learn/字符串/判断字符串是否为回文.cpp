#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;

    string result;
    
    for (int i = s.length() - 1; i >= 0 ; i--)
    {
        result.push_back(s[i]);
    }


    if(result == s)
    {
        cout << "yes" << endl;
    }else
    {
        cout << "no" << endl;
    }
        
    return 0;    
    
}