#include <bits/stdc++.h>
using namespace std;
#define int long long

void solv()
{
    string a, b;
    cin >> a >> b;
    vector<int> sa(30);
    vector<int> sb(30);
    for (int i = 0; i < a.size(); i++)
    {
        sa[a[i] - 'a']++;
    }
    for (int i = 0; i < b.size(); i++)
    {
        sb[b[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (sa[i] - sb[i] > 0)
        {
            cout << "Impossible" << endl;
            return;
        }
        sb[i] -= sa[i];
    }
    b = "";
    for (int i = 0; i < 26; i++)
    {
        char c = i + 'a';
        for (int j = 0; j < sb[i]; j++)
        {
            b += c;
        }
    }

    int i = 0, j = 0;
    while (i < a.size() && j < b.size())
    {
        if (b[j] < a[i])
        {
            cout << b[j++];
        }
        else
        {
            cout << a[i++];
        }
    }

    for (int k = i; k < a.size(); k++)
    {
        cout << a[k];
    }
    for (int k = j; k < b.size(); k++)
    {
        cout << b[k];
    }

    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solv();
    }
    return 0;
}