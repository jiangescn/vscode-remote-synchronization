#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
     
    vector<int> s(n);
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    sort(s.begin(), s.end());
    long long sum = 0;
    int j = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int arr = s[i] - j++;
        //cout <<"arr" << arr << endl; 
        sum += max(arr, 0);
        s[i] = 0;
    }
    
    cout << sum << endl;

    return 0;
}