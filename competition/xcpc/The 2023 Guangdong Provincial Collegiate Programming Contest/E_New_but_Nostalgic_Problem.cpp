#include <bits/stdc++.h>
using namespace std;

struct Trie
{
    struct Node
    {
        int ch[26];
        int endCnt;
        int childCnt;
        Node()
        {
            memset(ch, 0, sizeof(ch));
            endCnt = 0;
            childCnt = 0;
        }
    };

    vector<Node> t;

    Trie(int maxNodes = 1)
    {
        t.reserve(maxNodes);
        t.push_back(Node());
    }

    void add(const string &s)
    {
        int u = 0;
        for (char c : s)
        {
            int x = c - 'a';
            if (!t[u].ch[x])
            {
                t[u].ch[x] = (int)t.size();
                t.push_back(Node());
                t[u].childCnt++;
            }
            u = t[u].ch[x];
        }
        t[u].endCnt++;
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<string> w(n);
    int totalLen = 1;
    for (int i = 0; i < n; i++)
    {
        cin >> w[i];
        totalLen += w[i].size();
    }

    Trie trie(totalLen + 5);
    for (auto &s : w)
    {
        trie.add(s);
    }

    long long cur = trie.t[0].childCnt;

    if (cur >= k)
    {
        cout << "EMPTY" << endl;
        return;
    }

    struct Frame
    {
        int u;
        int nxt;
    };

    vector<Frame> st;
    st.reserve(trie.t.size());
    st.push_back({0, 0});

    string path;
    path.reserve(totalLen);

    while (!st.empty())
    {
        auto &top = st.back();
        int u = top.u;

        if (top.nxt < 26)
        {
            int c = top.nxt++;
            int v = trie.t[u].ch[c];
            if (!v)
            {
                continue;
            }

            path.push_back(char('a' + c));

            long long delta = 1LL * trie.t[v].endCnt + trie.t[v].childCnt - 1;
            cur += delta;

            if (cur >= k)
            {
                cout << path << endl;
                return;
            }

            st.push_back({v, 0});
        }
        else
        {
            st.pop_back();
            if (!path.empty())
                path.pop_back();
        }
    }

    cout << "EMPTY" << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--)
    {
        solve();
    }

    return 0;
}
