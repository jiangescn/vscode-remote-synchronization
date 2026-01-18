#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
	int t;
	cin >> t;
	while(t--){
		int x1, y1, x2, y2, x3, y3;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		
		int xx = x2 - x1;
		int yy = y2 - y1;
		
		int x = x3 - xx;
		int y = y3 - yy;
		
		cout << x << " " << y << endl;
	}
	
	return 0;
}
