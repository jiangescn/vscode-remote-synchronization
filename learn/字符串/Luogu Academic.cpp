// https://www.luogu.com.cn/problem/B3663
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;
    string lg = "luogu";

    int count = 0;

    for (int k = 0; k < s.size(); k++)
    {
        int found = 1;
        int i = k;
        int j = 0;
        while(j < 5)
        {
            if(s[i] != lg[j])
                found = 0;
            i++, j++;
        }
        if(found)
            count++;
    }
    cout << count << endl;
    return 0;
}