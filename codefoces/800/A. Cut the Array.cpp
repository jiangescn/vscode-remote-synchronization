#include <iostream>
#include <string>
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

        vector<int> s(n);
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
        }

        vector<int> perf(n + 1, 0);
        for (int i = 0; i < n; i++)
        {
            perf[i + 1] = perf[i] + s[i];
        }
        

        bool found = 0;
        int ans_l = 0, ans_r = 0;

        for (int l = 1; l <= n - 2; l++)
        {
            for (int r = l + 1; r <= n - 1; r++)
            {
                int s1 = perf[l] % 3;
                int s2 = (perf[r] - perf[l]) % 3;
                int s3 = (perf[n] - perf[r]) % 3;

                if((s1 == s2 && s2 == s3) || (s1 != s2 && s1 != s3 && s2 != s3))
                {
                    found = true;
                    ans_l = l;
                    ans_r = r;
                    break;
                }
            }
            if(found) break;
        }
        if(found)
        {
            cout << ans_l << " " << ans_r << endl;
        }
        else 
        {
            cout << "0 0" << endl;
        }
    }
    return 0;
}