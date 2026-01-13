#include <iostream>
#include <string>
using namespace std;

int score(string s)
{
    int sum = 1;

    for (int i = 0; i < s.length(); i++)
    {
        int a = s[i] - '@';
        sum *= a;
    }
    return sum;
}

int main ()
{
    string s1,s2;
    cin >> s1;
    cin >> s2;

    int score1 = score(s1);
    int score2 = score(s2);

    if(score1%47==score2%47)cout << "GO" <<endl;
    else cout << "STAY" <<endl;

    return 0;
}