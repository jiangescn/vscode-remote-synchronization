#include <bits/stdc++.h>
using namespace std;

// 线性筛（欧拉筛）
const int N = 1000000;
bool vis[N + 5];
int primes[N + 5], tot;
void sieve(int n)
{
    fill(vis + 1, vis + n + 1, false);
    vis[1] = true;
    tot = 0;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= n; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}