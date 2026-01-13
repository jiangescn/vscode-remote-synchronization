#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

int main()
{
    string input;
    getline(cin, input);

    int right = input.size() - 1;
    string ans = "";

    while(right >= 0)
    {
        string temp = "";

        while(right >= 0 && input[right] == ' ')
        {
            right--;
        }

        if(right < 0)
        {
            break;
        }

        int left = right;

        while(left >= 0 && input[left] != ' ')
        {
            left--;
        }

        string word = input.substr(left + 1, right - left);
        char firstchar = word[0];
        
        if(isdigit(firstchar))
        {
            reverse(word.begin(), word.end());
        }
        else if (isupper(firstchar))
        {
            for (char& c : word)
            {
                c = tolower(c);
            }
            
        }
        else if(islower(firstchar))
        {
            for (char & c : word)
            {
                c = toupper(c);
            }
            
        }

        if (!ans.empty())
        {
            ans += " ";
        }
        ans += word;

        right = left - 1;
    }
    cout << ans << endl;
    return 0;
}