#include <bits/stdc++.h>
using namespace std;

const int MAXL = 1000000 + 5;

int n, k;
char s[MAXL];

// trie
int idx;          // 当前节点总数
int tr[MAXL][26]; // trie 边
int ed[MAXL];     // ed[u]：有多少字符串恰好在 u 结束
int sum[MAXL];    // sum[u]：u 子树里一共有多少字符串

int newNode()
{
    ++idx;
    ed[idx] = 0;
    sum[idx] = 0;
    memset(tr[idx], 0, sizeof(tr[idx]));
    return idx;
}

void insertStr()
{
    int u = 1;
    ++sum[u];
    for (int i = 1; s[i]; i++)
    {
        int c = s[i] - 'a';
        if (!tr[u][c])
            tr[u][c] = newNode();
        u = tr[u][c];
        ++sum[u];
    }
    ++ed[u];
}

void solve()
{
    scanf("%d%d", &n, &k);

    idx = 0;
    newNode(); // root = 1

    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s + 1);
        insertStr();
    }

    int u = 1;

    while (true)
    {
        // 当前前缀本身作为答案时，最多能选多少个串
        int can = ed[u];
        for (int c = 0; c < 26; c++)
        {
            if (tr[u][c] && sum[tr[u][c]] > 0)
                ++can;
        }

        // 如果已经能选够 k 个，那么当前前缀就是答案
        if (can >= k)
        {
            if (u == 1)
                printf("EMPTY");
            printf("\n");
            return;
        }

        // 贪心确定下一位
        for (int c = 0; c < 26; c++)
        {
            int v = tr[u][c];
            if (!v || sum[v] == 0)
                continue;

            // 把当前这个儿子从“最多选 1 个”改成“整棵子树都能选”
            can = can - 1 + sum[v];

            if (can >= k)
            {
                // 外面的串已经够固定了，只需要在这个子树里继续找剩下的
                k -= (can - sum[v]);
                u = v;
                printf("%c", char('a' + c));
                break;
            }
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}