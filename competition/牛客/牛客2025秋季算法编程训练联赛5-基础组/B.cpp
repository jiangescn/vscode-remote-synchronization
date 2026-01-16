#include <bits/stdc++.h>
using namespace std;


int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    int tar = s[8];
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if(s[i] > tar)count++;
    }

    //cout << "i:" << s[8] << endl;
    

    if(s[8]*10 >= m*8 || count <= 2)
    {
        cout << "Yes" << endl;
        return 0;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}