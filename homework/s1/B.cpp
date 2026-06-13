#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s, b;
    cin >> s >> b;

    int data[256] = {0};
    for (int i = 0; i < s.size(); i++)
    {
        data[s[i]]++;
    }
    for (int i = 0; i < b.size(); i++)
    {
        data[b[i]]++;
    }

    int found = 0;
    for (int i = 0; i < 256; i++)
    {
        if(data[i] > 1)
        {
            cout << (char)i;
            found = 1;
        }
    }
    cout << endl;

    if(!found)
    {
        cout << "EMPTY" << endl;
    }
    return 0;    
}