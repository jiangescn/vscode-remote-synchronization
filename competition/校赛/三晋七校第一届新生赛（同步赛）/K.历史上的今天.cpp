#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<char> s(n+5);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    int i = 0;
    while(i < n)
    {
        if(s[i] == '0')
        {
            cout << 0;
            i++;
            continue;
        }
        else
        {
            cout << 1;
            i++;

            int count = 0;
            int j = i;
            while (j < n && s[j] == '1')
            {
                count++;
                j++;
            }

            for (int k = 0; k < count; k++)
            {
                cout << 0;
                i++;
            }

            if (i < n && s[i] == '0')
            {
                cout << 1;
                i++;
            }
        }
    }
    
}