#include <iostream>
#include <string>
using namespace std;

void fan(string s)
{
    int first = 1;
    string re;
        for (int i = s.length() - 1; i >= 0 ; i--)
        {
            if(first&&s[i]=='0')continue;
            re.push_back(s[i]);
            first = 0;
        }

    cout << re;
}

int main()
{
    string s;
    cin >> s;

    if(s == "0")
    {
        cout << "0" <<endl;
        return 0;
    }
    if(s == "0.0")
    {
        cout << "0.0" <<endl;
        return 0;
    }
    if(s == "0%")
    {
        cout << "0%" << endl;
        return 0;
    }

    string type = "0";

    for (int i = 0; i < s.length(); i++)
    {
        if(s[i]=='.')
        {
            type = "xiaoshu";
            break;
        }
        else if(s[i]=='/')
        {
            type = "fenshu";
            break;
        }
        else if(s[i]=='%')
        {
            type = "baifenshu";
            break;
        }
        else type = "zhengshu";
    }

    if(type == "zhengshu")
    {
        fan(s);
        return 0;
    }

    if(type == "xiaoshu")
    {
        string before;
        int j = 0;
        for (j = 0; s[j] != '.'; j++)
        {
            before.push_back(s[j]);
        }
        if(before == "0")cout << "0";
        else fan(before);
        cout << ".";

        string after_0;
        int temp = j;
        for (temp++; temp < s.length(); temp++)
        {
            after_0.push_back(s[temp]);
        }
        if(after_0 == "0")
        {
            cout << "0";
            return 0;
        }


        string after;
        int first = 1;
        for (j++; j < s.length(); j++)
        {
            if(first&&s[j]=='0')continue;
            after.push_back(s[j]);
            first = 0;
        }
        if(after == "0")cout << "0";
        else fan(after);
    }

    if(type == "fenshu")
    {
        string before;
        int j;
        for (j = 0; s[j] != '/'; j++)
        {
            before.push_back(s[j]);
        }
        if(before == "0")cout << "0";
        else fan(before);
        cout << "/";
        string after;
        for (j++; j < s.length(); j++)
        {
            after.push_back(s[j]);
        }
        if(after == "0")cout << "0";
        else fan(after);
    }

    if(type == "baifenshu")
    {
        string sub;
        for (int i = 0; i < s.length() - 1; i++)
        {
            sub.push_back(s[i]);
        }
        fan(sub);
        cout << "%";
    }
    return 0;
    
}