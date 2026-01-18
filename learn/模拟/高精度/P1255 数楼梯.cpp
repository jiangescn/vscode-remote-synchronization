#include <iostream>
#include <vector>
#include <string>
using namespace std;

string add(string a, string b)
{
    int len = max(a.size(), b.size()), plus = 0;
    string ans = "";
    while (a.size() < len)
        a = '0' + a;
    while (b.size() < len)
        b = '0' + b;
    for (int i = len - 1; i >= 0; i--)
    {
        int temp1 = a[i] - '0', temp2 = b[i] - '0';
        int temp = temp1 + temp2 + plus;
        plus = temp / 10;
        temp %= 10;
        char ch = temp + '0';
        ans = ch + ans;
    }
    if (plus != 0)
        return '1' + ans;
    return ans;
}

int main()
{
    string s1 = "1", s2 = "2";
    int n;
    cin >> n;

    if(n == 0)
    {
        cout << 0 << endl;
        return 0;
    }
    
    for (int i = 0; i < n - 1; i++)
    {
        string temp = s2;
        s2 = add(s1, s2);
        s1 = temp;
    }

    cout << s1 << endl;
}