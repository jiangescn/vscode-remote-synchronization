#include <iostream>
#include <vector>
using namespace std;

int main () 
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        int valid = 1;

        vector<int> s(n);
        int maxposi;

        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
            if(s[i] == n)maxposi = i;
        }

        for (int i = 0; i < maxposi; i++)
        {
            if(s[i] > s[i+1])valid = 0;
        }
        for (int i = maxposi; i < n - 1; i++)
        {
            if(s[i] < s[i+1])valid = 0;
        }
        
        if(valid)cout << "YES" << endl;
        else cout << "NO" << endl;
        
    }
}