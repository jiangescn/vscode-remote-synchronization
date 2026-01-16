#include <bits/stdc++.h>
using namespace std;

#define int long long

struct group
{
    int pos;
    int ti;
    int time;
};

bool cmp(struct group &a, struct group &b)
{
    if (a.ti == b.ti) return a.time < b.time;
    return a.ti > b.ti;
    // if (a.ti > b.ti)
    // {
    //     return true;
    // }
    // else if (b.ti > a.ti)
    // {
    //     return false;
    // }
    // else
    // {
    //     return a.time < b.time;
    // }
}

signed main()
{
    int n;
    cin >> n;

    vector<group> s(n);

    for (int i = 0; i < n; i++)
    {
        cin >> s[i].ti >> s[i].time;
        s[i].pos = i;
    }

    sort(s.begin(), s.end(), cmp);

    // for (int i = 0; i < n; i++)
    // {
    //     cout << s[i].pos << " ";
    // }cout << endl;
    

    int i = 0;
    for (i = 0; i < n; i++)
    {
        if(s[i].pos == 0)break;
    }
    i++;
    
    //cout << "pos :" << i << endl;

    if(i <= n*0.1)
    {
        cout << "gold" << endl;
    }
    else if(i <= n*0.3)
    {
        cout << "silver" << endl;
    }
    else if(i <= n*0.6)
    {
        cout << "bronze" << endl;
    }
    else
    {
        cout << "iron" << endl;
    }
    


    return 0;
}