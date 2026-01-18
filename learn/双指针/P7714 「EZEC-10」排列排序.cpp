#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> s(n+1);
        for (int i = 1; i <= n; i++)
        {
            cin >> s[i];
        }

        int left = 1, right = left;

        // stack<int> st;
        // int count = 0;
        // int i = 1;
        // while(i <= n)
        // {
        //     if(i == s[i])
        //     {
        //         i++;
        //         continue;
        //     }
        //     else
        //     {
        //         int max = s[i];
        //         while(s[i] <= max)
        //         {
        //             i++;
        //             if (s[i] > max)
        //             {
        //                 break;
        //             }
        //             else
        //             {
        //                 count++;
        //             }
        //         }
        //     }
            
        // }
        // cout << count << endl;
        
    }
}