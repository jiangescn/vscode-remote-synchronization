#include <stdio.h>

int main()
{
	int n, i, index, k, s;
	scanf("%d", &n);
	int arr[10] = {0};
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	for (k = 0; k < n - 1; k++)
	{
		index = k;
		for (s = n - 1; s >= k; s--)
		{
			if (arr[s] < arr[index])
				index = s;
		}
		int temp = arr[index];
		arr[index] = arr[k];
		arr[k] = temp;
	}
	for (int i = 0; i < n; i++)
	{
		printf("%d%c", arr[i], " \n"[i == n - 1]);
	}
	return 0;
}