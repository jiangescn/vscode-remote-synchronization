#include <stdio.h>
#include <math.h>

int f(int n, int k)
{
    int ans = -1;
    while(n)
    {
        int temp = n % 10;
        n /= 10;
        k--;
        if(k == 0)
        {
            ans = temp;
        }
    }
    return ans;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    printf("%d", f(n, k));

}