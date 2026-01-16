#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
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
		int i = 0;
		while(i < k)
		{
			int yuxia = k - i - 1;
			cout << "    yuxia:"  << yuxia << endl;
			if(j + 1 < n )
			{
				if(sum < s[j + 1])
				{
					int nextleveneed = s[j + 1] - sum;
					int round = nextleveneed / s[j];
					if(nextleveneed % s[j]) round++;
					
					sum += min(yuxia, round) * s[j];
					i += min(yuxia, round);
					
					//cout << "___________________________" << endl;
					//cout << "goleve : " << min(yuxia, round) << endl;
					//cout << endl;
				}
				else
				{
					j++;
					i++;
					if(i >= k)
					{
						break;
					}
					sum += s[j];
				}
			}
			else
			{
				sum += yuxia * s[n - 1];
				i = k;
			}
		}
		cout << sum << endl;
		
	}
	
	return 0;
}
