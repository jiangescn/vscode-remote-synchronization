#include <bits/stdc++.h>
using namespace std;

string add(string a, string b)
{
    int len = max(a.size(), b.size()), plus = 0;
    string ans = "";
    while(a.size() < len) a = '0' + a;
    while(b.size() < len) b = '0' + b;
    for (int i = len - 1; i >= 0; i--)
    {
        int temp1 = a[i] - '0', temp2 = b[i] - '0';
        int temp = temp1 + temp2 + plus;
        plus = temp / 10;
        temp %= 10;
        char ch = temp + '0';
        ans = ch + ans;
    }
    if(plus != 0)return '1' + ans;
    return ans;
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    cout << add(s1, s2) << endl;;
    return 0;
}