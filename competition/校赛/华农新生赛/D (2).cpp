#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
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
		for(int i = 0;i < n;i++){
			if(s[i] == '0')
			{
				count0++;
			}
			else if(s[i] == '1')
			{
				count1++;
			}
		}
		
		cout << abs(count0 - count1) << endl;
	}
	
	
	return 0;
}
