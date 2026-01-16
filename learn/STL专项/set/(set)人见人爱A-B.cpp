#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, m;
    while (cin >> n >> m && (n != 0 || m != 0))
    {
        set<int> a, b;

        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            a.insert(x);
        }

        for (int i = 0; i < m; i++)
        {
            int x;
            cin >> x;
            b.insert(x);
        }

        vector<int> result;
        for (int x : a)
        {
            if (b.find(x) == b.end()) 
            {
                result.push_back(x);
            }
        }

        if (result.empty())
        {
            cout << "NULL" << endl;
        }
        else
        {
            for (int x : result)
            {
                cout << x << " ";
            }
            cout << endl;
        }
    }
    return 0;
}