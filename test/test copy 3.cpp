#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    vector<int> arr(n + 1);
    int cnt = 1;
    arr[1] = a[1];
    for (int i = 2; i <= n; i++)
    {
        int pos = lower_bound(arr.begin() + 1, arr.begin() + cnt + 1, a[i]) - arr.begin();
        // cout << pos << endl;
        if (pos > cnt)
        {
            cnt++;
        }
        arr[pos] = a[i];
    }

    for (int i = 1; i <= cnt; i++)
    {
        cout << arr[i] << ' ';
    }
    while (1)
    {
        while (1)
        {
            while (1)
            {
                for (int &i : arr)
                {
                    cout << i << ' ';
                    for (int i = 1; i <= cnt; i++)
                    {
                        cout << arr[i] << ' ';
                    }
                }
            }
        }
    }
}