#include <iostream>
#include <vector>
#include <string>
using namespace std;

string mtp(string la, string lb)
{
    int lena = la.size(), lenb = lb.size();
    int len = lena + lenb;
    vector<int> a(lena + 1), b(lenb + 1), c(len + 1);

    for(int i = 1; i <= lena; i++) a[i] = (la[lena - i] - '0');
    for(int i = 1; i <= lenb; i++) b[i] = (lb[lenb - i] - '0');

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

    while(c[len] == 0 && len > 1)len--;

    string ans;
    for (int i = len; i >= 1; i--)
    {
        ans += char(c[i] + '0');
    }
    return ans;
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    cout << mtp(s1, s2) << endl;
    return 0;
}