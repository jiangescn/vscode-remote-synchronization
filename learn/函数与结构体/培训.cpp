#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct stu
{
    string name;
    int age;
    int noip;
};


int main()
{
    int n;
    cin >> n;

    vector<stu> s(n);

    for (int i = 0; i < n; i++)
    {
        cin >> s[i].name >> s[i].age >> s[i].noip;
        int noip_now = s[i].noip * 1.2;
        //cout << s[i].name << " " << ++s[i].age << " " << min(600, noip_now) << endl;
    }
    
}