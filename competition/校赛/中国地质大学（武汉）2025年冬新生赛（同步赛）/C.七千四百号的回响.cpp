#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> s(n+1);
    vector<int> op(n+1);

    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    

    int x;
    cin >> x;
    for (int i = 0; i < x; i++)
    {
        int a, b;
        cin >> a >> b;

        op[a]++;
        op[b+1]--;
    }

    for (int i = 1; i <= n; i++)
    {
        op[i] += op[i-1];
    }
    

    long long sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if(op[i]%2)
        {
            s[i] *= -1;
        }
        //cout << s[i] << ' ';
        sum += s[i];
    }
    //cout << endl;
    cout <<sum << endl;
    return 0;
}