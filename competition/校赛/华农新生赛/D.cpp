#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		string s;
		cin >> s;
		int count0 = 0;
		int count1 = 0;
		for(int i = 0; i < n; i++)
		{
			if(s[i] == '0')
			{
				count0++;
			} 
			else if(s[i] == '1')
			{
				count1++;
			}
		}
		int ans = abs(count0 - count1);
		cout << ans << endl;
	}
	
	
	return 0;
}
