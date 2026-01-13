#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        string s;
        cin >> s;
        vector<int> count(257, 0);
        int len = s.size();
        for (int i = 0; i < len ; i++)
        {
            count[s[i]]++;
        }

        while (count['T']--)
        {
            cout << "T";
        }
        count['T'] = 0;

        for (char i = 'A'; i <= 'Z'; i++)
        {
            while(count[i]--)
            {
                cout << i;
            }
        }
        cout << endl;
    }
    return 0;
}