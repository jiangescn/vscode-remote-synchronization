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
		int n, x;
		cin >> n >> x;
		vector<int> s(n + 1);
		for (int i = 1; i <= n; i++) cin >> s[i];
		
		vector<int> pre(n + 1);
		for (int i = 1; i <= n; i++)
			pre[i] = s[i] - s[i - 1];

		int sum = 0;

		for(int i = 1; i <= n; i++)
		{
			if(pre[i] < 0)
			{
				int add = 0 - pre[i];
				sum += add;
				if(i + x <= n)
				{
					pre[i + x] -= add;
				}
			}
		}
		
		cout << sum << endl;
	}
	
	
	return 0;
}
