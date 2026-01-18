#include <bits/stdc++.h>
using namespace std;
#define int long long

int f(int x)
{
	string s = to_string(x);
	int n = s.size();
	for(int i = 0; i < n; i++)
	{
		int Max = -1;
		int Maxpo = 0;
		for(int j = i + 1; j < n; j++)
		{
			if(s[j] > Max)
			{
				Max = s[j];
				Maxpo = j;
			}
		}
		if(Max > s[i])
		{
			swap(s[i], s[Maxpo]);
			int ans = stoll(s);
			return ans;
		}
	}
	int ans = stoll(s);
	return ans;
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
		vector<int> s(n);
		int sum = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> s[i];
			sum += f(s[i]);
		}
		cout << sum << endl;
	}
	
	
	
	return 0;
}
