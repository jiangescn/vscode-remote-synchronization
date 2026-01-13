#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<int> l(n);
    vector<int> r(n);
    for (int i = 0; i < n; i++)
    {
        cin >> l[i] >> r[i];
    }

    vector<int> x(q);
    for (int i = 0; i < q; i++)
    {
        cin >> x[i];
    }

    for (int i = 0; i < q; i++)
    {
        int found = 0;
        for (int j = 0; j < n; j++)
        {
            if (x[i] >= l[j] && x[i] <= r[j])
            {
                cout << j + 1 << endl;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            cout << "-1" << endl;
        }
    }
    return 0;
}