#include <iostream>
#include <vector>
#include <string>
using namespace std;

void processGame(const vector<char> &s, int points)
{
    int scoreW = 0, scoreL = 0;

    for (char ch : s)
    {
        if (ch == 'W')
            scoreW++;
        else if (ch == 'L')
            scoreL++;

        if ((scoreW >= points || scoreL >= points) && abs(scoreW - scoreL) >= 2)
        {
            cout << scoreW << ":" << scoreL << endl; 
            scoreW = 0;
            scoreL = 0;
        }
    }

    cout << scoreW << ":" << scoreL << endl;
}

int main()
{
    char c;
    vector<char> s;

    while ((c = getchar()) != 'E')
    {
        if (c == 'W' || c == 'L')
        {
            s.push_back(c);
        }
    }

    processGame(s, 11);
    cout << endl; 

    processGame(s, 21);

    return 0;
}