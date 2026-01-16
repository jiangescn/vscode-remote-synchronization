#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    sort(s.begin(), s.end());

    // for (int i = 0; i < n; i++)
    // {
    //     cout << s[i] << " ";
    // }cout << endl;
    

    vector<int> qian(n+1), hou(n+1);     
    for (int l = 0, r = 0; r < n; r++)
    {
        while(s[r] - s[l] > k && l <= r)
        {
            l++;
        }
        if (r == 0)
        {
            qian[r] = r - l + 1;
        }
        else
        {
            qian[r] = max(qian[r - 1], r - l + 1);
        }
    }

    for (int i = n - 1, l = n - 1, r = n - 1; l >= 0; l--)
    {
        while(s[r] - s[l] > k && l <= r)
        {
            r--;
        }
        if (l == n - 1)
        {
            hou[l] = r - l + 1;
        }
        else
        {
            hou[l] = max(hou[l + 1], r - l + 1);
        }
    }

    int M = 0;
    for (int i = 0; i < n - 1; i++)
    {
        M = max(M, qian[i] + hou[i + 1]);
    }
    
    M = max(M, qian[n - 1]);

    cout << M << endl;
    return 0;
}

//1 5 5 9 10 12 14