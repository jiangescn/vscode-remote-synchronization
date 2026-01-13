#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> s(n + 5);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }

    long long sum = 0;
    for (int i = 1; i <= n; i++)
    {
        int a = s[i] - s[i - 1];
        if(a > 0) sum += a;
    }
    
    cout << sum << endl;
    return 0;    
}