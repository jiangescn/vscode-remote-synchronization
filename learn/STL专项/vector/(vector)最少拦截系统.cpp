#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;

    while (cin >> n)
    {
        vector<int> height(n);

        for (int i = 0; i < n; i++)
        {
            cin >> height[i];
        }

        vector<int> systems;
        for (int i = 0; i < n; i++)
        {
            bool found = 0;
            for (int j = 0; j < systems.size(); j++)
            {
                if (height[i] <= systems[j])
                {
                    found = 1;
                    systems[j] = height[i];
                    break;
                }
            }

            if (!found)
            {
                systems.push_back(height[i]);
            }
        }

        cout << systems.size() << endl;
    }
    
    return 0;
    
}