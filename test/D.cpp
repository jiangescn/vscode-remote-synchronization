#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
    

    int a[5][5];
    int *p = a[0];

    printf("%d", *(p + 10));

    map<int, int> mp;

    for (auto f = mp.begin(); f != mp.end(); f++) 
    {
        int a = (*f).first;
        f->first;
    }
    for (auto f: mp) 
    {
        f.first;
    }
}
