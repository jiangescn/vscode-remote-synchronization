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
		int k, n;
		cin >> k >> n;
		vector<int> s(n);
		for(int i = 0; i < n; i++)
		{
			cin >> s[i];
		}
		
		int sum = s[0];
		int j = 0;
		for(int i = 1; i < k; i++)
		{
			if(sum >= s[j + 1] && j < n)
			{
				j++;
				sum += s[j];
				//cout << "    +=" << s[j] << endl;
			}
			else{
				sum += s[j];
				//cout << "    +=" << s[j] << endl;
			}
		}
		cout << sum << endl;
		
	}
	
	
	return 0;
}
