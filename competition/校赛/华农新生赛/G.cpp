#include <bits/stdc++.h>
using namespace std;
#define int long long

bool check(vector<int>& s, int k)
{
	int n = s.size();
	int count = 0;
	for (int i = 1; i < n; i++)
	{
		if(s[i] - s[i - 1] > k)
		{
			count++;
		}
	}
	//cout << "k :" << k << " cut :" << count << endl;
	return count <= 1;
}

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
		vector<int> s;
		int Max = 0;
		for (int i = 0; i < n; i++)
		{
			int a;
			cin >> a;
			s.push_back(a);
			Max = max(Max, a);
		}
		
		sort(s.begin(), s.end());
		
		int l = 1, r = Max;
		while(l <= r)
		{
			int mid = l + (r - l) / 2;
			if(check(s, mid))
			{
				r = mid - 1;
				//l = mid + 1;
			}
			else
			{
				l = mid + 1;
				//r = mid - 1;
			}
		}
		cout << l << endl;
		
		
		
		
	}
	
	
	
	return 0;
}
