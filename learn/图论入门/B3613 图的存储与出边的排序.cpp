#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> s(n);
        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            s[a-1].push_back(b);
        }

        for (int i = 0; i < n; i++)
        {
            sort(s[i].begin(), s[i].end());
            for (int j = 0; j < s[i].size(); j++)
            {
                if(j != 0) cout << " ";
                cout << s[i][j];
            }
            cout << endl;
        }
                
    }
    return 0;
}