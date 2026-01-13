#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        vector<int> s;
        for (int i = n; i >= 1; i -= 2)
        {
            s.push_back(i);
        }
        for (int i = n % 2 + 1; i <= n; i += 2)
        {
            s.push_back(i);
        }

        vector<int> ans(n + 1);
        for (int i = 0; i < n; i++)
        {
            ans[s[i]] = a[i];
        }
        for (int i = 1; i <= n; i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
}