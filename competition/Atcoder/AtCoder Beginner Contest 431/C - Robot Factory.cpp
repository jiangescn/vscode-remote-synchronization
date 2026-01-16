#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> h(n);
    vector<int> b(m);

    for (int i = 0; i < n; i++)
    {
        cin >> h[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    
    sort(h.begin(), h.end());
    sort(b.begin(), b.end());

    // for (int i = 0; i < n; i++)
    // {
    //     cout << h[i] << " ";
    // }cout << endl;
    // for (int i = 0; i < m; i++)
    // {
    //     cout << b[i] << " ";
    // }cout << endl;

    int i = 0, j = 0;
    int count = 0;
    while(i < n && j < m)
    {
        if(h[i] <= b[j])
        {
            count++;
            i++;
            j++;
        }
        else
        {
            j++;
        }
    }

    //cout << count << endl;

    if(count >= k)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}