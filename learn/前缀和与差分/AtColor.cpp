#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> s(1000005, 0);

    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        s[l]++;
        s[r + 1]--;
    }

    int Max = s[0];
    for (int i = 1; i <= 1000000; i++)
    {
        s[i] += s[i - 1];
        Max = max(Max, s[i]);
    }
    cout << Max << endl;
}