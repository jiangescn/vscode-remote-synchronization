// https://atcoder.jp/contests/abc156/tasks/abc156_c
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    int Min = INT_MAX;
    for (int i = 1; i <= 100; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += pow((i - s[j]), 2);
        }
        Min = min(Min, sum);
    }
    cout << Min << endl;
    return 0;
}