#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int i;
    for (i = 0; i < s.size(); i++)
    {
        if (s[i] == 'e')
        {
            // cout << i + 1 << endl;
            break;
        }
    }

    int va = 0;
    for (int j = i; j < s.size(); j++)
    {
        if (s[j] == 'z')
        {
            // cout << j + 1 << endl;
            va = 1;
            break;
        }
    }
    cout << (va ? "easy" : "hard") << endl;
}