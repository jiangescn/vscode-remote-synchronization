#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<string> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    sort(s.begin() + 1, s.end(), [](string a, string b){
        if(a.size() == b.size()) return a < b;
        return a.size() < b.size();
    });

    for (int i = 2; i <= n; i++)
    {
        int pos = s[i].find(s[i - 1]);
        if(pos == -1)
        {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
    for (int i = 1; i<= n; i++)
    {
        cout << s[i] << endl;
    }
    return 0;
}