#include <bits/stdc++.h>
using namespace std;


void solv()
{
    int n, k;
    cin >> n >> k;
    unordered_set<int> S;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        S.insert(a);
    }

    vector<int> s;
    for (auto it : S)
    {
        s.push_back(it);
    }
    sort(s.begin(), s.end());

    // cout << "::::::" << endl;
    // for (int i = 0; i < s.size(); i++)
    // {
    //     cout << s[i];
    // }cout << endl;
    // cout << "^^^^^^" << endl;

    n = s.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            vector<int> ss;
            for (int k = i; k <= j; k++)
            {
                ss.push_back(s[k]);
            }
            vector<int> temp = s;

            auto f = [ss, s]()->bool {
                int n = s.size(), m = ss.size();

                for (int l = 0; l < n; l++)
                {
                    bool valid = 0;
                    for (int h = 0; h < m; h++)
                    {
                        if (s[l] % ss[h] == 0)
                        {
                            valid = 1;
                            break;
                        }
                    }
                    if (valid == 0)
                    {
                        return false;
                    }
                }
                return true;
            };
            // for (int z = 0; z < ss.size(); z++)
            // {
            //     cout << ss[z] << " ";
            // }cout << endl;

            // cout << (allk(s, ss) ? "isvalid": "notvalid") << endl;


        }
    }
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        

        


        cout << "------------------" << endl;


        
    }
}