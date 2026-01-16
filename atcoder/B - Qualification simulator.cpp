// https://atcoder.jp/contests/code-festival-2016-qualb/tasks/codefestival_2016_qualB_b
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    un

    int A = 0, B = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'a' && A + B < a + b)
        {
            cout << "Yes" << endl;
            A++;
        }
        else if (s[i] == 'b' && A + B < a + b && B < b)
        {
            cout << "Yes" << endl;
            B++;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}

