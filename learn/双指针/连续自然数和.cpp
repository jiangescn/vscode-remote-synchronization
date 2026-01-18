#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int M;
    cin >> M;

    int i = 1, j = 1;
    int sum = 1;

    while(i <= M / 2)
    {
        if(sum < M)
        {
            j++;
            sum += j;
        }
        else if(sum > M)
        {
            sum -= i;
            i++;
        }
        else
        {
            cout << i << " " << j << endl;
            sum -= i;
            i++;
        }
    }
    return 0;
}