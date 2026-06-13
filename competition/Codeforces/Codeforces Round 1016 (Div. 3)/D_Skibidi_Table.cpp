// 递归填表 左上右下
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define itn int

int get_num(int n, int x, int y)
{
    int ans = 1;

    for (int k = n; k >= 1; k--)
    {
        int len = 1ll << k;
        int half = len / 2;

        int block = half * half;

        if (x <= half && y <= half)
        {
            // 左上
            ans += 0 * block;
        }
        else if (x > half && y > half)
        {
            // 右下
            ans += 1 * block;
            x -= half;
            y -= half;
        }
        else if (x > half && y <= half)
        {
            // 左下
            ans += 2 * block;
            x -= half;
        }
        else
        {
            // 右上
            ans += 3 * block;
            y -= half;
        }
    }

    return ans;
}


pair<int, int> get_pos(int n, int d)
{
    d--;
    int x = 1, y = 1;

    for (int k = n; k >= 1; k--)
    {
        int len = 1LL << k;
        int half = len / 2;
        int block = half * half;

        int id = d / block;
        d %= block;

        if (id == 0)
        {
            // 左上
        }
        else if (id == 1)
        {
            // 右下
            x += half;
            y += half;
        }
        else if (id == 2)
        {
            // 左下
            x += half;
        }
        else
        {
            // 右上
            y += half;
        }
    }

    return {x, y};
}

void solve()
{
    int n, q;
    cin >> n >> q;

    while(q--)
    {
        string s;
        cin >> s;
        if(s == "->")
        {
            int x, y;
            cin >> x >> y;

            cout << get_num(n, x, y) << endl;
        }
        else
        {
            int d;
            cin >> d;
            auto [x, y] = get_pos(n, d);
            cout << x << " " << y << endl;
        }
    }

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

// vector<vector<int>> s;

// void fill_table(int x, int y, int len, int start)
// {
//     if (len == 2)
//     {
//         s[x][y] = start;             // 左上
//         s[x + 1][y + 1] = start + 1; // 右下
//         s[x + 1][y] = start + 2;     // 左下
//         s[x][y + 1] = start + 3;     // 右上
//         return;
//     }

//     int half = len / 2;
//     int block = half * half;

//     // 填充顺序：
//     // 1. 左上
//     fill_table(x, y, half, start);

//     // 2. 右下
//     fill_table(x + half, y + half, half, start + block);

//     // 3. 左下
//     fill_table(x + half, y, half, start + 2 * block);

//     // 4. 右上
//     fill_table(x, y + half, half, start + 3 * block);
// }