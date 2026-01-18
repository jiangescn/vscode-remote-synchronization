#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    int sum = 0;
    queue<pair<int, int>> s;
    for (int min = 1; min <= n; min++)
    {
        string op;
        int x;
        cin >> op >> x;

        while(!s.empty() && s.front().first <= min - m)
        {
            sum -= s.front().second;
            s.pop();
        }

        if(op == "cook")
        {
            s.push({min, x});
            sum += x;
        }
        else
        {
            if(sum >= x)
            {
                cout << "xie xie ni" << endl;
                while(x)
                {
                    if(s.front().second > x)
                    {
                        s.front().second -= x;
                        sum -= x;
                        x = 0;
                    }
                    else
                    {
                        x -= s.front().second;
                        sum -= s.front().second;
                        s.pop();
                    }
                }
            }
            else
            {
                cout << "wu wu wu" << endl;
            }
        }

    }
    
}