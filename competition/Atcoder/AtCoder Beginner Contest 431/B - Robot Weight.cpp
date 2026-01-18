#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int ori;
    cin >> ori;

    int n;
    cin >> n;
    vector<int> a(n+5);
    vector<int> vab(n+5);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    int m;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int x;
        cin >> x;
        vab[x]++;
        if(vab[x]%2)
        {
            ori += a[x];
            cout << ori << endl;
        }
        else
        {
            ori -= a[x];
            cout << ori << endl;
        }
    }    
}