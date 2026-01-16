#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct stu
{
    double a;
    double b;
    double c;
    double d;
    double e;

    double sum;
    int num;
};

int main()
{
    cout << fixed << setprecision(2);
    int n;
    cin >> n;
    vector<stu> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i].num >> s[i].a >> s[i].b >> s[i].c >> s[i].d >> s[i].e;
        s[i].sum = s[i].a + s[i].b + s[i].c + s[i].d + s[i].e;
    }

    for (int i = 0; i < n; i++)
    {
        cout << s[i].num << ":" << s[i].sum << " " << s[i].sum / 5 << endl;
    }

    sort(s.begin(), s.end(), [](stu x, stu y){
        if(x.a == y.a)
        {
            return x.num < y.num;
        }
        return x.a > y.a; 
    }
    );
    int k = 0;
    printf("%.2llf:%d", s[k].a, s[k].num);
    while(s[k].a == s[k+1].a)
    {
        printf(" %d", s[k+1].num);
        k++;
    }
    cout << endl;

    sort(s.begin(), s.end(), [](stu x, stu y){
        if(x.b == y.b)
        {
            return x.num < y.num;
        }
        return x.b > y.b; 
    }
    );
    k = 0;
    printf("%.2lf:%d", s[k].b, s[k].num);
    while(s[k].b == s[k+1].b)
    {
        printf(" %d", s[k+1].num);
        k++;
    }
    cout << endl;


    sort(s.begin(), s.end(), [](stu x, stu y){
        if(x.c == y.c)
        {
            return x.num < y.num;
        }
        return x.c > y.c; 
    }
    );
    k = 0;
    printf("%.2lf:%d", s[k].c, s[k].num);
    while(s[k].c == s[k+1].c)
    {
        printf(" %d", s[k+1].num);
        k++;
    }
    cout << endl;


    sort(s.begin(), s.end(), [](stu x, stu y){
        if(x.d == y.d)
        {
            return x.num < y.num;
        }
        return x.d > y.d; 
    }
    );
    k = 0;
    printf("%.2lf:%d", s[k].d, s[k].num);
    while(s[k].d == s[k+1].d)
    {
        printf(" %d", s[k+1].num);
        k++;
    }
    cout << endl;


    sort(s.begin(), s.end(), [](stu x, stu y){
        if(x.e == y.e)
        {
            return x.num < y.num;
        }
        return x.e > y.e; 
    }
    );
    k = 0;
    printf("%.2lf:%d", s[k].e, s[k].num);
    while(s[k].e == s[k+1].e)
    {
        printf(" %d", s[k+1].num);
        k++;
    }
    cout << endl;
    
    
}