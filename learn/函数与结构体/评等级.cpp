#include <iostream>
#include <vector>
using namespace std;

struct stu
{
    int id;
    int acd;
    int quali;

    double compos;
};

 
int main()
{
    int n;
    cin >> n;

    vector<stu> s(n);
    
    for (int i = 0; i < n; i++)
    {
        cin >> s[i].id >> s[i].acd >> s[i].quali; 
        s[i].compos = s[i].acd * 7 + s[i].quali * 3;

        if(s[i].acd + s[i].quali > 140 && s[i].compos >= 800)
        {
            cout << "Excellent" << endl;
        }
        else
        {
            cout << "Not excellent" << endl;
        }
    }
    return 0;
}