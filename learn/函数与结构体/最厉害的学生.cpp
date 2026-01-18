#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct student
{
    string name;
    int chin;
    int math;
    int en;
    int sum;
};


int main()
{
    int n;
    cin >> n;
    vector<student> stu(n);

    int max = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> stu[i].name >> stu[i].chin >> stu[i].math >> stu[i].en;
        stu[i].sum = stu[i].chin + stu[i].math + stu[i].en;

        if(stu[i].sum > stu[max].sum)
        {
            max = i;
            //cout << "curr MAX = " << max << endl;
        }
    }

    cout << stu[max].name << " " << stu[max].chin << " " << stu[max].math << " " << stu[max].en;
}