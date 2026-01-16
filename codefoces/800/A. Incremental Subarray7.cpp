#include <iostream>
#include <vector>
#pragma GCC optimize(3)
using namespace std;


int seem(vector<int> s,vector<int> sub)
{
    int count = 0;
    for (int i = 0; i <= s.size() - sub.size() ; ++i)
    {
        bool found = 1;
        for (int j = 0; j < sub.size(); ++j)
        {
            if(s[i+j] != sub[j])
            {
                found = 0;
                break;
            }
        }
        
        if(found)count++;
    }
    
    return count;
}

int main ()
{
    int o;
    cin >> o;

    for (int l = 0; l < o; l++)
    {
        int m, n;
        cin >> m >> n;

        vector<int> num;
        vector<int> sub;

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                num.push_back(j+'0');
            }
        }

        //cout << l << "num:" << num << endl;

        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            sub.push_back(a+'0');
        }

        //cout << l << "sub:" << sub << endl;
        
        cout << seem(num,sub) << endl;
    }
    return 0;
}