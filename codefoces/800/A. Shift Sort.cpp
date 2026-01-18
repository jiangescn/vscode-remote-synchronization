#include <iostream>
using namespace std;

int main ()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int count0 = 0;
        for (char ch : s)
        {
            if(ch == '0')count0++;
        }

        int ans = 0;
        for (int i = 0; i < count0; i++)
        {
            if(s[i]=='1')ans++;
        }
        cout << ans << endl;
    }
}