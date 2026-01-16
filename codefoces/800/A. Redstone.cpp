#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// int main ()
// {
//     int t;
//     cin >> t;
//     while (t--)
//     {
//         int n;
//         cin >> n;
//         vector<int> s(n);
//         for (int i = 0; i < n; i++)
//         {
//             cin >> s[i];
//         }

//         // for (int i = 0; i < n; i++)
//         // {
//         //     cout << s[i] << " ";
//         // }cout << endl;
        

//         int found = 0;
//         for (int i = 0; i < n; i++)
//         {
//             for (int j = i + 1; j < n; j++)
//             {
//                 if(s[i] == s[j])found = 1;
//             }
//         }
        
//         if(found)
//         {
//             cout << "YES" << endl;
//         }
//         else
//         {
//             cout << "NO" << endl;
//         }
        
//     }
// }

bool chongfu(vector<int>& nums)
{
    unordered_set<int> seen;
    for (int num : nums)
    {
        if(!seen.insert(num).second)return 1;
    }
    return 0;
}


int main ()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;

        int found = 0;

        vector<int> s(n);
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
        }

        if(chongfu(s))cout << "YES" << endl;
        else cout << "NO" << endl;
        
    }
}