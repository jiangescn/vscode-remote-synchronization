// Problem URL: $url$
// Problem Name: $name$
#include <bits/stdc++.h>
using namespace std;
#define int long long

string mtp(string la, string lb)
{
    int lena = la.size(), lenb = lb.size();
    int len = lena + lenb;
    vector<int> a(lena + 1), b(lenb + 1), c(len + 1);

    for (int i = 1; i <= lena; i++)
        a[i] = (la[lena - i] - '0');
    for (int i = 1; i <= lenb; i++)
        b[i] = (lb[lenb - i] - '0');

    for (int i = 1; i <= lenb; i++)
    {
        for (int j = 1; j <= lena; j++)
        {
            c[i + j - 1] += a[j] * b[i];
        }
    }

    for (int i = 1; i < len; i++)
    {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

    while (c[len] == 0 && len > 1)
        len--;

    string ans;
    for (int i = len; i >= 1; i--)
    {
        ans += char(c[i] + '0');
    }
    return ans;
}
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

void solve()
{
    string a = "123";
    string b = "20";

    cout << add(a, b) << endl;
    cout << mtp(a, b) << endl;
    
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}