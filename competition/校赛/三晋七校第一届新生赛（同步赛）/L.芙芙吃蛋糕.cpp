#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int Max = 0;
    for (int i = 0; i < n; i++)
    {
        if(s[i] == '(')
        {
            int j = i + 1;
            while(j < n && s[j] == '#')
            {
                j++;
            }

            if(j < n && s[j] == ')')
            {
                Max = max(Max, j - i + 1);
            }
        }
    }
    
    cout << Max << endl;
    return 0;
}