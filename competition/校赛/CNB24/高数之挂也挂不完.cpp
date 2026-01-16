#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> s(n + 1);
    int i = 1;
    for (int l = 1; l <= k; l++)
    {
        for (int o = l; o <= n; o += k)
        {
            s[o] = i++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if(i != 1)cout << " ";
        cout << s[i];
    }
}