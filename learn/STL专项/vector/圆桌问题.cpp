#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, m;
    bool first_round = true;
    while (cin >> n >> m)
    {
        if(!first_round)
        {
            cout << endl;
        }


        first_round = false;

        int count_bad = 0;
        int count_m = 0;
        vector<char> people(2*n,'G');
        int i = 0;

        while(count_bad < n)
        {
            if(i >= 2 * n)
            {
                i %= (2 * n);
            }//成环


            if(people[i]!='B')
            {
                count_m++;
                if (count_m == m)
                {
                    count_m = 0;
                    people[i] = 'B';
                    count_bad++;
                } // 枪毙
            }
            //跳死
            i++;
        }


        for (int i = 0; i < 2 * n; i++)
        {
            cout << people[i];
            if ((i + 1) % 50 == 0)
            {
                cout << endl;
            }
        }
        if (2 * n % 50 != 0)
        {
            cout << endl;
        }
    }
    return 0;
}