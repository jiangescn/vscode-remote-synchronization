#include <bits/stdc++.h>
using namespace std;

void solve()
{

    string s;
    cin >> s;
    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '>' && s[i + 1] == '<' || s[i] == '*' && s[i + 1] == '*' || s[i] == '>' && s[i + 1] == '*' || s[i] == '*' && s[i + 1] == '<')
        {
            cout << -1 << endl;
            return;
        }
    }

    int countl = 0;
    int countr = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '<')
        {
            countl++;
        }
        else
        {
            if (s[i] == '*')
                countl++;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] == '>')
        {
            countr++;
        }
        else
        {
            if (s[i] == '*')
                countr++;
            break;
        }
    }

    //cout << "L:" << countl << "   R:" << countr << endl;

    if (countl == 0 && countr == 0)
    {
        cout << 1 << endl;
        return;
    }
    int Max = max(countl, countr);
    cout << Max << endl;

    return;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}