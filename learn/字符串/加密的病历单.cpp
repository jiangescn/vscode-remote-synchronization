#include <iostream>
#include <cctype>
#include <vector>
using namespace std;

int main ()
{
    char a;
    vector<char> data_temp;
    while((a = getchar())!=EOF&&a!='\n')
    {
        data_temp.push_back(a);
    }

    vector<char> data = data_temp;
    for (int i = 0; i < data.size(); i++)
    {
        data[data_temp.size()-1-i]=data_temp[i];
    }
    
    for (int i = 0; i < data.size(); i++)
    {
        if(isupper(data[i]))data[i] = tolower(data[i]);
        else data[i]= toupper(data[i]);
    }

    for (int i = 0; i < data.size(); i++)
    {
        char ans;
        if(isupper(data[i]))
        {
            if(data[i]+3<='Z')ans = data[i] + 3;
            else ans = (data[i] + 3 -'A')% 26 +'A';
        }
        else
        {
            if(data[i]+3<='Z')ans = data[i] + 3;
            else ans = (data[i] + 3 - 'a')% 26 + 'a';
        }
        
        cout << ans;
    }
    
    return 0; 
}