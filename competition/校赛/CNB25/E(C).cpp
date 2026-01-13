#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char a[1005], b[1005];
    scanf("%s%s", a, b);

    if (strcmp(a, b) == 0)
    {
        printf("ni shi dui de\n");
        return 0;
    }

    char aa[1005] = "", bb[1005] = "";
    int ia = 0, ib = 0;
    int fir = 1;

    // 提取a的整数部分
    for (ia = 0; a[ia] != '.' && a[ia] != '\0'; ia++)
    {
        if (fir && a[ia] == '0')
        {
            continue;
        }
        char temp[2] = {a[ia], '\0'};
        strcat(aa, temp);
        fir = 0;
    }

    // 提取b的整数部分
    fir = 1;
    for (ib = 0; b[ib] != '.' && b[ib] != '\0'; ib++)
    {
        if (fir && b[ib] == '0')
        {
            continue;
        }
        char temp[2] = {b[ib], '\0'};
        strcat(bb, temp);
        fir = 0;
    }

    if (strcmp(aa, bb) != 0)
    {
        printf("ni shi dui de\n");
        return 0;
    }

    // 小数部分
    char x[1005] = "", y[1005] = "";
    char zx[1005] = "", zy[1005] = "";

    // 提取a的小数部分
    fir = 1;
    if (a[ia] == '.')
    {
        for (int i = ia + 1; a[i] != '\0'; i++)
        {
            char temp[2] = {a[i], '\0'};
            strcat(zx, temp);
            if (fir && a[i] == '0')
            {
                continue;
            }
            strcat(x, temp);
            fir = 0;
        }
    }

    // 提取b的小数部分
    fir = 1;
    if (b[ib] == '.')
    {
        for (int i = ib + 1; b[i] != '\0'; i++)
        {
            char temp[2] = {b[i], '\0'};
            strcat(zy, temp);
            if (fir && b[i] == '0')
            {
                continue;
            }
            strcat(y, temp);
            fir = 0;
        }
    }

    // 正确比较大小
    char xx[2005] = "", yy[2005] = "";
    strcpy(xx, zx);
    strcpy(yy, zy);

    int len_xx = strlen(xx);
    int len_yy = strlen(yy);

    // 补零到相同长度
    if (len_xx > len_yy)
    {
        for (int i = len_yy; i < len_xx; i++)
        {
            yy[i] = '0';
        }
        yy[len_xx] = '\0';
    }
    else if (len_xx < len_yy)
    {
        for (int i = len_xx; i < len_yy; i++)
        {
            xx[i] = '0';
        }
        xx[len_yy] = '\0';
    }

    int zhengque;
    int cmp = strcmp(xx, yy);
    if (cmp > 0)
    {
        zhengque = 1;
    }
    else if (cmp < 0)
    {
        zhengque = 2;
    }
    else
    {
        zhengque = 3;
    }

    // 数字王国比较大小
    int shuzi = 1;
    int cmp_xy = strcmp(x, y);

    if (cmp_xy > 0)
    {
        shuzi = 1;
    }
    else if (cmp_xy < 0)
    {
        shuzi = 2;
    }
    else
    {
        shuzi = 3;
    }

    int len_x = strlen(x);
    int len_y = strlen(y);

    if (len_x > len_y)
    {
        shuzi = 1;
    }
    else if (len_x < len_y)
    {
        shuzi = 2;
    }

    if (shuzi == zhengque)
    {
        printf("ni shi dui de\n");
        return 0;
    }

    // 输出结果
    if (shuzi == 1)
    {
        printf("ni cuo le, ying gai shi >\n");
    }
    else if (shuzi == 2)
    {
        printf("ni cuo le, ying gai shi <\n");
    }
    else
    {
        printf("ni cuo le, ying gai shi =\n");
    }

    return 0;
}