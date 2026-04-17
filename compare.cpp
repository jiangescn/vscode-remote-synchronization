#include <bits/stdc++.h>
using namespace std;

int L, N;
long long ans = 0;
vector<int> col, rowv;

// 枚举第 r 行的内容
void genRow(int r, int pos, int rest)
{
    if (pos == N - 1)
    {
        // 最后一个位置由剩余值决定
        if (rest <= col[pos])
        {
            rowv[pos] = rest;
            for (int j = 0; j < N; j++)
                col[j] -= rowv[j];

            // 继续填下一行
            if (r == N - 2)
            {
                // 前 N-1 行填完，最后一行唯一确定
                ans++;
            }
            else
            {
                genRow(r + 1, 0, L);
            }

            for (int j = 0; j < N; j++)
                col[j] += rowv[j];
        }
        return;
    }

    for (int x = 0; x <= min(rest, col[pos]); x++)
    {
        rowv[pos] = x;
        genRow(r, pos + 1, rest - x);
    }
}

int main()
{
    cin >> L >> N;

    col.assign(N, L);
    rowv.assign(N, 0);

    if (N == 1)
    {
        cout << 1 << "\n";
        return 0;
    }

    genRow(0, 0, L);

    cout << ans << "\n";
    return 0;
}
