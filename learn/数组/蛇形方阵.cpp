#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main(void){
	int n;
	int data[10][10]={0};

	cin >> n;
	int count = 1;
	
	int i = 0;
	while(i < (n + 1) / 2)
	{
		for (int j = i; j < n - i - 1; j++)
		{
			data[i][j] = count++;
		}
		for (int j = i; j < n - i - 1; j++)
		{
			data[j][n-1-i] = count++;
		}
		for (int j = i; j < n - i - 1; j++)
		{
			data[n-1-i][n-1-j] = count++;
		}
		for (int j = i; j < n - i - 1; j++)
		{
			data[n-1-j][i] = count++;
		}
		i += 1;
	}
		if(n % 2 == 1)
	{
		data[n/2][n/2]=count;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(3) << setfill(' ') << data[i][j];
		}
		cout << endl;
	}


	
	return 0;
}