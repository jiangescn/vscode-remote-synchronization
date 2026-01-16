#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<string> s(n + 1);
    map<string, int> count;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        count[s[i]]++;
        if(count[s[i]] == 1)
        {
            cout << "OK" << endl;
        }
        else
        {
            cout << s[i] << count[s[i]] - 1 << endl;
        }
    }
    
}