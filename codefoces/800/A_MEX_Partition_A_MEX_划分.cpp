#include <iostream>
#include <vector>
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
        vector<int> c(101);
        for(int i = 0; i < n; i++)
        {
            cin >> s[i];
            c[s[i]]++;
        }

        for (int i = 0; i <= 100; i++)
        {
            if(c[i] == 0)
            {
                cout << i << endl;
                break;
            }
        }
        
    }
}