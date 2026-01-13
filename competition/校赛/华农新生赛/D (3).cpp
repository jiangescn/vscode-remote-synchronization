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
		int a = 0;
		int b = 0;
		for(int i = 0; i < n; i++)
		{
			if(s[i] == '0')
			{
				a++;
			} 
			else if(s[i] == '1')
			{
				b++;
			}
		}
		int ans = a - b;
		if(ans < 0) ans *= -1;
		cout << ans << endl;
	}
	
	return 0;
}
