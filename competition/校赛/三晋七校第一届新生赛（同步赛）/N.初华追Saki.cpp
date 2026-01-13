#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;

    int l = 0;
    int r = s.size() - 1;

    vector<int> ans(s.size());

    while(l <= r)
    {
        if(s[l] > s[r])
        {
            ans[r] = s[l] - s[r];
            ans[l] = 0;
        }
        else if(s[l] < s[r])
        {
            ans[l] = s[r] - s[l];
            ans[r] = 0;
        }
        else
        {
            ans[l] = 0;
            ans[r] = 0;
        }
        l++;
        r--;
    }

    bool first = true;
    for (int i = 0; i < s.size(); i++)
    {
        if(first && ans[i] == 0)continue;
        cout << ans[i];
        first = false;
    }

    if(first)cout << "0";

    cout << endl;
    
    return 0;
}