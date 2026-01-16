#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

struct stu
{
    string name;
    int chin;
    int math;
    int en;

    int sum;
};

bool qg(stu a, stu b)
{
    bool vali = true;
    if(abs(a.chin - b.chin) > 5) vali = false;
    else if(abs(a.math - b.math) > 5) vali = false;
    else if(abs(a.en - b.en) > 5) vali = false;
    else if(abs(a.sum - b.sum) > 10) vali = false;

    return vali;
}


int main()
{
    int n;
    cin >> n;

    vector<stu> s(n + 5);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i].name >> s[i].chin >> s[i].math >> s[i].en;
        s[i].sum = s[i].chin + s[i].math + s[i].en;
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if(qg(s[i], s[j]))
            {
                cout << s[i].name << " " << s[j].name << endl;
            }
        }
        
    }
    
    return 0;
}