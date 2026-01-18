#include <iostream>
using namespace std;
#define int long long

signed main()
{
    int t;
    cin >> t;
    string last = "";
    string s = "";
    while(t--)
    {
        cin >> s;
        if(s == "a")
        {
            last = s;
            int a, b;
            cin >> a >> b;
            int ans = a + b;
            int count = 0;
            printf("%d+%d=%d\n", a, b, ans);
            if (a == 0)
                count++;
            if (b == 0)
                count++;
            if (ans == 0)
                count++;
            while(a != 0)
            {
                a /= 10;
                count++;
            }
            while(b != 0)
            {
                b /= 10;
                count++;
            }
            while(ans != 0)
            {
                ans /= 10;
                count++;
            }
            cout << count + 2 << endl;
        }
        else if(s == "b")
        {
            last = s;
            int a, b;
            cin >> a >> b;
            int ans = a - b;
            int count = 0;
            if(ans < 0)count++;
            printf("%d-%d=%d\n", a, b, ans);
            if (a == 0)
                count++;
            if (b == 0)
                count++;
            if (ans == 0)
                count++;
            while(a != 0)
            {
                a /= 10;
                count++;
            }
            while(b != 0)
            {
                b /= 10;
                count++;
            }
            while(ans != 0)
            {
                ans /= 10;
                count++;
            }
            cout << count + 2 << endl;
        }
        else if(s == "c")
        {
            last = s;
            int a, b;
            cin >> a >> b;
            int ans = a * b;
            int count = 0;
            printf("%d*%d=%d\n", a, b, ans);
            if (a == 0)
                count++;
            if (b == 0)
                count++;
            if (ans == 0)
                count++;
            while(a != 0)
            {
                a /= 10;
                count++;
            }
            while(b != 0)
            {
                b /= 10;
                count++;
            }
            while(ans != 0)
            {
                ans /= 10;
                count++;
            }
            cout << count + 2 << endl;
        }
        else
        {
            if(last == "a")
            {
                int a = 0;
                for (int i = 0; i < s.size(); i++)
                {
                    a *= 10;
                    a += s[i] - '0';
                }
                int b;
                cin >> b;
                int ans = a + b;
                int count = 0;
                printf("%d+%d=%d\n", a, b, ans);
                if (a == 0)
                    count++;
                if (b == 0)
                    count++;
                if (ans == 0)
                    count++;
                while (a != 0)
                {
                    a /= 10;
                    count++;
                }
                while (b != 0)
                {
                    b /= 10;
                    count++;
                }
                while (ans != 0)
                {
                    ans /= 10;
                    count++;
                }
                cout << count + 2 << endl;
            }

            else if (last == "b")
            {
                int a = 0;
                for (int i = 0; i < s.size(); i++)
                {
                    a *= 10;
                    a += s[i] - '0';
                }
                int b;
                cin >> b;
                int ans = a - b;
                int count = 0;
                if (ans < 0)
                    count++;
                printf("%d-%d=%d\n", a, b, ans);
                if (a == 0)
                    count++;
                if (b == 0)
                    count++;
                if (ans == 0)
                    count++;
                while (a != 0)
                {
                    a /= 10;
                    count++;
                }
                while (b != 0)
                {
                    b /= 10;
                    count++;
                }
                while (ans != 0)
                {
                    ans /= 10;
                    count++;
                }
                cout << count + 2 << endl;
            }

            else if(last == "c")
            {
                int a = 0;
                for (int i = 0; i < s.size(); i++)
                {
                    a *= 10;
                    a += s[i] - '0';
                }
                int b;
                cin >> b;
                int ans = a * b;
                int count = 0;
                printf("%d*%d=%d\n", a, b, ans);
                if (a == 0)
                    count++;
                if (b == 0)
                    count++;
                if (ans == 0)
                    count++;
                while (a != 0)
                {
                    a /= 10;
                    count++;
                }
                while (b != 0)
                {
                    b /= 10;
                    count++;
                }
                while (ans != 0)
                {
                    ans /= 10;
                    count++;
                }
                cout << count + 2 << endl;
            }
        }
    }
    return 0;
}