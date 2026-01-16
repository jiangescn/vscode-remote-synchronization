#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main(void)
{
    int n;
    cin >> n;
    double data[500] = {0};

    for (int i = 0; i < n; i++)
    {
        cin >> data[i];
    }

    double max=0,min=data[0];
    for (int i = 0; i < n; i++)
    {
        if(max<data[i])max=data[i];
        if(min>data[i])min=data[i];
    }

    double sum=0;
    for (int i = 0; i < n; i++)
    {
        sum+=data[i];
    }

    double arv=(sum-max-min)/(n-2);

    double arv_max = 0;
    int brr_max=1,brr_min=1;
    for (int i = 0; i < n; i++)
    {
        if(data[i]==max&&brr_max)
        {
        brr_max=0;
        continue;
        }
        if(data[i]==min&&brr_min)
        {
        brr_min=0;
        continue;
        }
        if(abs(data[i]-arv)>arv_max)arv_max=abs(data[i]-arv);
    }
    

    
    cout<<fixed<<setprecision(2)<<arv<<" "<<arv_max<<endl;
    
    
}