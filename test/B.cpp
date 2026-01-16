#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    string s;
    cin >> s;
    while(t--)
    {
        int n;
        cin >> n;
        if(n == 1)
        {
            string a;
            cin >> a;
            int pos = s.find(a);
            cout << pos << endl;
        }
        else if(n == 2)
        {
            string a, b;
            cin >> a >> b;
            int pos = s.find(a);
            s.replace(pos, a.length(), b);
            cout << s << endl;
        }
        else if(n == 3)
        {
            char a, b;
            cin >> a >> b;
            string ss;
            cin >> ss;

            for (int j = 1; j < s.size(); j++)
            {
                if(s[j - 1] == a && s[j] == b)
                {
                    s.insert(j, ss);
                    j += ss.size();
                }
            }
            cout << s << endl;
        }
    }
}