#include <iostream>
#include <vector>
using namespace std;

int main()
{
    long long n, p; // stu  plus
    cin >> n >> p;

    vector<long long> s(n + 5, 0);
    vector<long long> ori(n + 5, 0);
    for (long long i = 0; i < n; i++)
    {
        cin >> ori[i];
    }

    while(p--)
    {
        long long l, r, x;
        cin >> l >> r >> x;
        
        s[l - 1] += x;
        s[r] -= x;
    }

    long long Min = s[0] + ori[0];

    for (long long i = 1; i < n; i++)
    {
        s[i] += s[i - 1];
    }


    for (int i = 0; i < n; i++)
    {
        s[i] += ori[i];
        Min = min(s[i], Min);
    }
    
    
    cout << Min << endl;
    return 0;
}