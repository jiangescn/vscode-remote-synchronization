#include <bits/stdc++.h>
using namespace std;
#define N 500000
int num[N] = {0};
char e[N];
char t[N];
int main()
{
    int n;
    int d = 0;
    scanf("%d", &n);
    scanf("%s", e);
    int len = strlen(e);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", t);
        int lent = strlen(t);

        if (len == lent && strcmp(e, t) == 0)
        {
            d++;
            num[i] = 1;
        }

        else if (len == lent)
        {
            int x = 0;
            for (int j = 0; j < len; j++)
            {

                if (e[j] != t[j])
                    x++;
            }
            if (x <= 1)
            {
                d++;
                num[i] = 1;
            }
        }

        else if (len == lent - 1)
        {
            int ei = 0, ti = 0;
            int diff = 0;
            while (ei < len && ti < lent)
            {
                if (e[ei] == t[ti])
                {
                    ei++;
                    ti++;
                }
                else
                {
                    ti++;
                    diff++;
                    if (diff > 1)
                    {
                        break;
                    }
                }
            }
            if (diff <= 1)
            {
                d++;
                num[i] = 1;
            }
        }

        else if (len == lent + 1)
        {
            int ei = 0, ti = 0;
            int diff = 0;
            while (ei < len && ti < lent)
            {
                if (e[ei] == t[ti])
                {
                    ei++;
                    ti++;
                }
                else
                {
                    ei++;
                    diff++;
                    if (diff > 1)
                    {
                        break;
                    }
                }
            }
            if (diff <= 1)
            {
                d++;
                num[i] = 1;
            }
        }
    }
    printf("%d\n", d);
    if (d > 0)
    {
        for (int o = 0; o < n; o++)
        {
            if (num[o] == 1)
            {
                printf("%d ", o + 1);
            }
        }
        printf("\n");
    }
    return 0;
}