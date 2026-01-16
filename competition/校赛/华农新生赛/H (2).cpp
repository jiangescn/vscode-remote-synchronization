#include <bits/stdc++.h>
using namespace std;
#define int long long

int power(string s)
{
	int n = s.size();
	string tar1 = "fire";
	string tar2 = "water";
	string tar3 = "wind";
	
	int fair = 0, water = 0, wind = 0;
	
    int a = 0, b = 0, c = 0;
	
	for(int i = 0; i < n; i++)
	{
		if(s[i] == tar1[a])
		{
			a++;
			if(a == 4)
			{
				fair++;
				a = 0;
			}
		}
		
		if(s[i] == tar2[b]) 
		{
			b++;
			if(b == 5)
			{
				water++;
				b = 0;
			}
		}
		
		if(s[i] == tar3[c])
		{
			c++;
			if(c == 4)
			{
				wind++;
				c = 0;
			}
		}
	}
	//cout << "f:" << fair << " wa:" << water << " wi:" << wind << endl;
	int ans = fair + water * wind;
	return ans;
}

signed main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int m, n;
		cin >> m >> n;
		string s, t;
		cin >> s;
		cin >> t;
		
		int a = power(s);
		int b = power(t);
		
		//cout << a << " " << b << endl;
		if(a > b)
		{
			cout << "YES" << endl;
		}
		else{
			cout << "NO" << endl;
		}
	}
	
	
	
	
	return 0;
}
