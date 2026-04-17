#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n, c;
    cin >> n >> c;

    vector<string> name(n);
    vector<int> ans(n, 0);

    unordered_map<string, int> id;

    auto cmp = [](const pair<string, int> &a, const pair<string, int> &b)
    {
        if (a.second != b.second)
            return a.second < b.second;
        return a.first > b.first;
    };
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> s(cmp);

    for (int i = 0; i < n; i++)
    {
        string str;
        int x;
        cin >> name[i] >> id[str];
        name[i] = str;
        id[str] = i;
        s.push({name[i], id[str]});
    }

    vector<set<int>> bucket(c);

    int ans_cnt = 0;

    while (!s.empty())
    {
        auto [sch, cnt] = s.top();
        s.pop();

        if (cnt >= c)
        {
            ans_cnt++;
            ans[id[sch]]++;

            cnt -= c;
            if (cnt > 0)
            {
                s.push({sch, cnt});
            }
        }
        else
        {
            int chooseRoom = -1;
            int chooseFree = -1;

            for (int freeSeat = cnt; freeSeat <= c - 1; freeSeat++)
            {
                if (!bucket[freeSeat].empty())
                {
                    int roomId = *bucket[freeSeat].begin();
                    if (chooseRoom == -1 || roomId < chooseRoom)
                    {
                        chooseRoom = roomId;
                        chooseFree = freeSeat;
                    }
                }
            }

            if (chooseRoom == -1)
            {
                ans_cnt++;
                ans[id[sch]]++;

                int left = c - cnt;
                if (left > 0)
                {
                    bucket[left].insert(ans_cnt);
                }
            }
            else
            {
                bucket[chooseFree].erase(chooseRoom);
                ans[id[sch]]++;

                int newFree = chooseFree - cnt;
                if (newFree > 0)
                {
                    bucket[newFree].insert(chooseRoom);
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << name[i] << ' ' << ans[i] << endl;
    }
    cout << ans_cnt << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}