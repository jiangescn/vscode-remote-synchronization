#include<iostream>
#include<cmath>
using namespace std;

bool same(char a[][100],char b[][100],int n){
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if(a[i][j]!=b[i][j])return false;
		}
	}
	return true;
}

int main(void){
	
	int n;
	cin>>n;

	char ori[100][100];
	char tar[100][100];
	char temp[100][100];

	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin>>ori[i][j];
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin>>tar[i][j];
		}
	}

	//90
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[i][j]=ori[n-1-j][i];
		}
	}
	if (same(temp, tar, n)) 
	{
    cout << 1;
    return 0;
	}

	//180
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[i][j]=ori[n-1-i][n-1-j];
		}
	}
	if (same(temp, tar, n)) 
	{
    cout << 2;
    return 0;
	}
	
	//270
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[i][j]=ori[j][n-1-i];
		}
	}
	if (same(temp, tar, n)) 
	{
    cout << 3;
    return 0;
	}

	//ubpk
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[i][j]=ori[i][n-1-j];
		}
	}
	if (same(temp, tar, n)) 
	{
    cout << 4;
    return 0;
	}

	//gjvr
	//90
	char temp2[100][100];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp2[i][j]=temp[n-1-j][i];
		}
	}
	if(same(temp2,tar,n)){
		cout<<5;
		return 0;
	}

	//180
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp2[i][j]=temp[n-1-i][n-1-j];
		}
	}
	if(same(temp2,tar,n)){
		cout<<5;
		return 0;
	}
	
	//270
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp2[i][j]=temp[j][n-1-i];
		}
	}
	if(same(temp2,tar,n)){
		cout<<5;
		return 0;
	}

	//same
	if(same(ori,tar,n)){
		cout<<6;
		return 0;
	}

	cout<<7;

	return 0;
}