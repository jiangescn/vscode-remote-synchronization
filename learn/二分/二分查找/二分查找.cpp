#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> num(n + 1);
    vector<int> target(m);

    for (int i = 1; i <= n; i++)
    {
        cin >> num[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> target[i];
    }



    for (int i = 0; i < m; i++)
    {
        int left = 1, right = n;
        int result = -1; 

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (num[mid] >= target[i])
            {
                if (num[mid] == target[i])
                {
                    result = mid;
                }
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        if (result != -1)
        {
            cout << result << " ";
        }
        else
        {
            cout << "-1 ";
        }
    }

    return 0;
}