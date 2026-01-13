#include<iostream>
using namespace std;

int main(void)
{
    int n;
    cin >> n;

    int data[30000]={0};

	for (int i = 0; i < n; i++)
	{
		cin >> data[i];
	}

    int num[200]={0};
    for (int i = 0; i < n; i++)
    {
        num[data[i]]++;
    }

    int o[30000] = {0};
    for (int i = 0; i < n; i++)
    {
        if(num[data[i]] <= 1 || o[data[i]] == 0)
        {
            if(i != 0)printf(" ");
            cout << data[i];
            o[data[i]] = 1;
        }
    }
    

    return 0;
}