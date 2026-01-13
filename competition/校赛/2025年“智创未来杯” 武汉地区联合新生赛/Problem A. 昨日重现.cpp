#include <bits/stdc++.h>
using namespace std;

int how(string &s, string tar, int deep, int pos)
{
    int ans = 0;
    int n = s.size();
    int m = tar.size();
    if (deep == m)
        return 1;

    for (int i = pos; i >= 0; i--)
        if (s[i] == tar[m - 1 - deep])
            ans += how(s, tar, deep + 1, i - 1);

    return ans;
}

int main()
{
    string s;
    cin >> s;
    int n = s.size();

    int HUST = how(s, "HUST", 0, n - 1);
    int WHU = how(s, "WHU", 0, n - 1);
    int WHUT = how(s, "WHUT", 0, n - 1);
    int HZAU = how(s, "HZAU", 0, n - 1);
    int CCNU = how(s, "CCNU", 0, n - 1);
    int Max = max({HUST, WHU, WHUT, HZAU, CCNU});

    if (Max == CCNU)
        cout << "CCNU " << Max << endl;
    else if (Max == HUST)
        cout << "HUST " << Max << endl;
    else if (Max == HZAU)
        cout << "HZAU " << Max << endl;
    else if (Max == WHU)
        cout << "WHU " << Max << endl;
    else if (Max == WHUT)
        cout << "WHUT " << Max << endl;
    return 0;
}