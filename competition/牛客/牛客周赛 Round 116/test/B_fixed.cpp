#include <bits/stdc++.h>
using namespace std;

bool duiying(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}



int main()
{
    string s;
    getline(cin, s);
    int n = s.size();

    if (s.empty())
    {
        cout << "Yes" << endl;
        return 0;
    }

    stack<char> stk;

    for (char a: s)
    {
        if(a == '(' || a == '{' || a == '[')
        {
            stk.push(a);
        }
        else
        {
            if(stk.empty())
            {
                cout << "No" << endl;
                return 0;
            }
            else
            {
                if (duiying(stk.top(), a))
                {
                    stk.pop();
                }
                else
                {
                    stk.push(a);
                }
            }
        }
    }

    //cout  << stk.size() << endl;
    if(stk.empty())
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    
}