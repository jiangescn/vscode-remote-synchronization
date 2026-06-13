#include <iostream>
#include <string>
#include <algorithm>
#include <cctype> // 用于 isalpha 函数
#include <vector>
#include <map>
using namespace std;

int main()
{
    string s;
    getline(cin, s);
    map<char, int> data;

    int i = 0;
    while (i < s.size() && s[i] != '?')
    {
        if (isalpha(s[i]))
        {
            data[s[i]]++; 
        }
        i++;
    }

    vector<pair<char, int>> vec(data.begin(), data.end());

    sort(vec.begin(), vec.end(), [](const pair<char, int> &s, const pair<char, int> &b)
         {
        if (s.second != b.second) {
            return s.second > b.second;
        } else {
            return s.first < b.first;  
        } });

    for (const auto &p : vec)
    {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}