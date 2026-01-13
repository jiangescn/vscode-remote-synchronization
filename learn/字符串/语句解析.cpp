#include <iostream>
#include <cctype>
using namespace std;

int main ()
{
    char m,n;;
    int ans[3]={0};
    while (scanf("%c:=%c;", &m, &n) == 2)
    {
        if(isdigit(n))ans[m-'a']=n-'0';
        else if(isalpha(n))ans[m-'a']=ans[n-'a'];
    }

    for (int i = 0; i < 3; i++)
    {
        if(i!=0)cout << " ";
        cout << ans[i];
    }
    
    return 0;
}