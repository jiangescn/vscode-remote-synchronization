#include <iostream>
#include <vector>
using namespace std;

int main () 
{
    int a;
    vector<int> s;
    while ((a=getchar())!=EOF&&a!='\n')
    {
        s.push_back(a);
    }
    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        char c;
        if(i<n-1)c=s[i]+s[i+1];
        else c=s[i]+s[0];

        cout << c;
    }
    

}