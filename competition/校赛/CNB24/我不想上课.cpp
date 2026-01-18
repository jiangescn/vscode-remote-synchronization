#include <iostream>
#include <vector>
using namespace std;

int con(vector<int>& s)
{
    int Max = 0;

    for (int begin = 0; begin < 31; begin++)
    {
        int count = 0;
        for (int i = begin; i < 31; i++)
        {
            if(s[i] == 0)count++;
            else break;
        }
        Max = max(Max, count);
    }
    return Max;
}

int main()
{
    vector<int> s;
    for (int i = 0; i < 31; i++)
    {
        int a;
        cin >> a;
        s.push_back(a);
    }

    vector<int> temp = s;

    // for (int i = 0; i < temp.size(); i++)
    // {
    //     cout << temp[i] << " ";
    // }cout << endl;
    

    int Max = 0;
    for (int change = 0; change < 31; change++)
    {
        vector<int> temp = s;
        temp[change] = 0;
        int Max_temp = con(temp); 
        Max = max(Max_temp, Max);
    }
    
    cout << Max << endl;
    return 0;    
}