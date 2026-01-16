#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<char> s(n + 1);
        s[0] = ' ';
        for (int i = 1; i <= n; i++)
        {
            cin >> s[i];
        }
        stack<char> q;
        for (int i = 1; i <= n; i++)
        {
            char c = s[i];
            if (c == ')')
            {
                if (!q.empty() && q.top() == '(')
                {
                    q.pop();
                    //cout << "pop:" << c << endl;
                }
                else
                {
                    q.push(c);
                    //cout << "push:" << c << endl;
                }
            }
            else
            {
                q.push(c);
                //cout << "push:" << c << endl;
            }
        }

        cout << q.size() << endl;
    }
    return 0;
}