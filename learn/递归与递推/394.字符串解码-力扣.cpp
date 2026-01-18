#include <bits/stdc++.h>
using namespace std;
int where = 0;

string f(string& s, int& i)
{
    string path;
    int count = 0;

    while(i < s.size() && s[i] != ']')
    {
        if(isalpha(s[i]))
        {
            path += s[i];
            i++;
        }
        else if (isdigit(s[i]))
        {
            count = count * 10 + (s[i] - '0');
            i++;
        }
        else if(s[i] == '[')
        {
            i++;
            string in = f(s, i);
            i++;
            for (int j = 0; j < count; j++)
            {
                path += in;
            }
            count = 0;
        }
    }
    return path;
}

int main()
{
    string s;
    cin >> s;
    int i = 0;
    cout << f(s, i) << endl;
}