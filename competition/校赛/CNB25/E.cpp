#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    string a, b;
    cin >> a >> b;
    if (a == b)
    {
        cout << "ni shi dui de" << endl;
        return 0;
    }

    string aa = "", bb = "";
    int ia = 0;
    int fir = 1;
    for (ia = 0; a[ia] != '.' && ia < a.size(); ia++)
    {
        if (fir && a[ia] == '0')
            continue;
        aa += a[ia];
        fir = 0;
    }
    int ib = 0;
    for (ib = 0; b[ib] != '.' && ib < b.size(); ib++)
    {
        if (fir && a[ib] == '0')
            continue;
        bb += b[ib];
        fir = 0;
    }

    if (aa != bb)
    {
        cout << "ni shi dui de" << endl;
        return 0;
    }

    string x = "", y = "";
    string zx = "", zy = "";
    fir = 1;
    for (int i = ++ia; i < a.size(); i++)
    {
        zx += a[i];
        if (fir && a[i] == '0')
            continue;
        x += a[i];
        fir = 0;
    }
    fir = 1;
    for (int i = ++ib; i < b.size(); i++)
    {
        zy += b[i];
        if (fir && b[i] == '0')
            continue;
        y += b[i];
        fir = 0;
    }

    string xx = zx;
    string yy = zy;
    while (xx.size() > yy.size())
        yy += '0';
    while (xx.size() < yy.size())
        xx += '0';
    int zhengque;
    if (xx > yy)
        zhengque = 1;
    else if (xx < yy)
        zhengque = 2;
    else
        zhengque = 3;

    int shuzi = 1;
    if (x > y)
        shuzi = 1;
    else if (x < y)
        shuzi = 2;
    else
        shuzi = 3;

    if (x.size() > y.size())
        shuzi = 1;
    else if (x.size() < y.size())
        shuzi = 2;

    if (shuzi == zhengque)
    {
        cout << "ni shi dui de" << endl;
        return 0;
    }

    if (shuzi == 1)
        cout << "ni cuo le, ying gai shi >" << endl;
    else if (shuzi == 2)
        cout << "ni cuo le, ying gai shi <" << endl;
    else
        cout << "ni cuo le, ying gai shi =" << endl;
}