#include <bits/stdc++.h>
using namespace std;

bool duiying(char a, char b)
{
    if(a > b)swap(a, b);
    if(a==40 && b==41) return true;
    if(a==91 && b==93) return true;
    if(a==123 && b==125) return true;
    return false;
}

int main()
{
    string s;
    getline(cin, s);
    int n = s.size();

    int l = 0, r = 1;


    for (int l = 0; l < n; l++)
    {
        if (s[l] == 41 || s[l] == 93 || s[l] == 125)continue;
        r = l + 1;
        int val = 1;
        vector<int> count(128, 0);
        while(r < n)
        {
            if (!duiying(s[l], s[r]))
            {
                count[s[r]]++;
                r++;

                //cout << count[40] << count[41] << count[91] << count[93] << count[123] << count[125] << endl;
            }
            else
            {
                //cout << "!!!!" << endl;
                if (count[40] != count[41])
                    val = 0;
                if (count[91] != count[93])
                    val = 0;
                if (count[123] != count[125])
                    val = 0;

                if (!val)
                {
                    cout << "No" << endl;
                    return 0;
                }
                break;
            }
        }
    }
    cout << "Yes" << endl;
}