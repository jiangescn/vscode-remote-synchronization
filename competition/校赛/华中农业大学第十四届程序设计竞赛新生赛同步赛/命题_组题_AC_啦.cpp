#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> s(n + 1);
        vector<int> vi(10);
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
        }

        int r = 0;
        int count = 1;
        while (r < n)
        {
            if(vi[s[r]] == 0)
            {
                vi[s[r]]++;
                r++;
            }
            else
            {
                count++;
                fill(vi.begin(), vi.end(), 0);
                vi[s[r]]++;
                r++;
            }
        }
        cout << count << " " << n << endl;
    }
    return 0;
}