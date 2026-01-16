#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main()
{
    int n;
    cin >> n;
    cin.ignore();

    unordered_set<string> lv;

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        string s;
        getline(cin, s);
        lv.insert(s);
    }

    cout << lv.size() << endl;
    
}

// int main()
// {

// }