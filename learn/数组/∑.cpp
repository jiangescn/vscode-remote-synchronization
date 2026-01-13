#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <set>
using namespace std;

int main() 
{
    int n;
    cin >> n;

    int data[50][150] = {0};
    for (int i = 0; i < n*3; i++)
    {
        data[0][i] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        data[i][i] = 1;
        if(i<n/2)data[i][3*n-1-i] = 1;
    }
    


    //print
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n*3; j++)
        {
            if(data[i][j])cout << "*";
            else cout << " ";
        }
        cout << endl;
    }

    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = 0; j < n*3; j++)
        {
            if(data[i][j])cout << "*";
            else cout << " ";
        }
        cout << endl;
    }
    
    


    return 0;
}








// #include <bits/stdc++.h>
// using namespace std;

// int main() 
// {
//     int n;
//     cin >> n;

//     int data[100][300] = {0};
//     for (int i = 0; i < n*3; i++)
//     {
//         data[0][i] = 1;
//     }

//     for (int i = 0; i < n; i++)
//     {
//         data[i][i] = 1;
//         if(i<n/2)data[i][3*n-1+i] = 1;
//     }
    
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n*3+n/2; j++)
//         {
//             if(data[i][j])cout << "*";
//             else cout << " ";
//         }
//         for (int j = n*3+n/2-1; j >= 0; j--)
//         {
//             if(data[i][j])cout << "*";
//             else cout << " ";
//         }
//         cout << endl;
//     }

//     for (int i = n - 2; i >= 0; i--)
//     {
//         for (int j = 0; j < n*3+n/2; j++)
//         {
//             if(data[i][j])cout << "*";
//             else cout << " ";
//         }
//         for (int j = n*3+n/2-1; j >= 0; j--)
//         {
//             if(data[i][j])cout << "*";
//             else cout << " ";
//         }
//         cout << endl;
//     }
//     return 0;
// }