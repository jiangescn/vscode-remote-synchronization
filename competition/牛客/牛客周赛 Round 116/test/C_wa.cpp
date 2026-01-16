#include <bits/stdc++.h>
using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> s;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        s.push_back(a);
    }

    int max_ = 1;
    int ji = 1;
    int begin = 0;
    for (begin = 0; begin < k; begin++)
    {
        if(s[begin] == 0)break;
       ji *= s[begin];
    }
    max_ = ji;


    for (int i = k; i < n; i++)
    {
        ad:
        if(s[i] == 0)
        {
            //cout << "0position:" << i + 1 << endl;
            ji = 1;
            for (int j = i + 1; j < i + k + 1; j++)
            {
                if(s[j] == 0)
                {
                    i = j + 1;
                    goto ad;
                }
                ji *= s[j];
                //cout << j + 1 << " " << ji << "     ";
            }//cout << endl;
            i += k;
            //cout << ji << endl;
            //cout << "skip to :" << i + 1 << endl;
        }
        else
        {
            ji = ji * s[i];
            if(i >= k)ji = ji / s[i - k];
        }

        max_ = max(ji % 998244353, max_);
    }
    
    cout << max_ << endl;
    
    return 0;
}