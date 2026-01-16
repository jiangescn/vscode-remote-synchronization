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

        int count = 0;

        vector<int> s(n);
        vector<int> m(n,1);

        int max_money = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
            if(s[i] > max_money)max_money = s[i];
        }

        // for (int i = 0; i < n; i++)
        // {
        //     cout << s[i] << " ";
        // }
        

        for (int i = 1; i <= max_money; i++)
        {
            //cout << "money : "<< i << endl;
            for (int j = 0; j < n; j++)
            {
                if(i >= s[j])
                {
                    m[j] = 0;
                    //cout << "solve : " << j + 1 << endl;
                    break;
                }
            }            
        }

        for (int i = 0; i < n; i++)
        {
            if(m[i])count++;
        }
        

        cout << count << endl;
        int first = 0;
        for (int i = 0; i < n; i++)
        {
            if(m[i])
            {
                if(first)cout << " ";
                cout << i+1;
                first = 1;
            }
        }
        cout << endl;
        
    }
    return 0;
}