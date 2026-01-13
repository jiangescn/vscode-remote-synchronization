#include <iostream>
#include <vector>
using namespace std;

int main ()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int data[1000] = {0};

        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            data[a]++;
        }
        
        int max_ans = 0;

        for (int j = 1; j <= n; j++)
        {
            int k = 0;
            for (int l = 0; l < 1000; l++)
            {
                if(data[l] >= j)k++;
            }

            int ans = k * j;
            if(ans > max_ans)max_ans =ans;
        }
        cout << max_ans << endl;
    }
    return 0;
}