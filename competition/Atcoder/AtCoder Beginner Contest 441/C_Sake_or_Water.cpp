#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int N, K;
    long long X;
    cin >> N >> K >> X;
    vector<long long> s(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> s[i];
    }

    sort(s.begin(), s.end(), [](int a, int b)
         { return a > b; });

    vector<long long> pref(N + 1, 0);
    for (int i = 1; i <= N; ++i)
    {
        pref[i] = pref[i - 1] + s[i - 1];
    }

    int bx = N - K;
    long long base = pref[bx];

    if (pref[N] - base < X)
    {
        cout << -1 << '\n';
        return;
    }

    for (int m = bx + 1; m <= N; ++m)
    {
        if (pref[m] - base >= X)
        {
            cout << m << '\n';
            return;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
