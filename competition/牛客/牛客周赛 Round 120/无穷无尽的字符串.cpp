#include <bits/stdc++.h>
using namespace std;

int main()
{
    int l, r;
    cin >> l >> r;

    int round = (r - l + 1) / 3;
    int yu = r - l + 1 - round * 3;

    //cout << "round:" << round << endl;
    //cout << "yu:" << yu << endl;

    vector<int> s(4);
    for (int i = 1; i <= 3; i++)
    {
        s[i] = round;
    }
    
    for (int i = l % 3; i < l % 3 + yu; i++)
    {
        s[i]++;
    }
    
    cout << s[1] << " " << s[2] << " " << s[3] + s[0] << endl;
}