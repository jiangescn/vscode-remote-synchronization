    #include <bits/stdc++.h>
    using namespace std;
    #define int long long

    void solve()
    {
        int n, t;
        cin >> n >> t;
        vector<int> s(n + 1);
        stack<int> st;
        vector<int> ans;

        int sum = 0;

        for (int i = 1; i <= n; i++)
        {
            cin >> s[i];
        }
        for (int i = 1; i <= n; i++)
        {
            if (s[i] <= t)
            {
                ans.push_back(i);
            }
            else
            {
                st.push(i);
                sum += s[i];
            }
        }

        vector<int> yuxia;
        while(!st.empty())
        {
            yuxia.push_back(st.top());
            st.pop();
        }

        if(yuxia.size() == 0)
        {
            goto Aa;
        }
        t = sum / (int)yuxia.size();

        while (!yuxia.empty())
        {
            sum = 0;

            for (int i = 0; i < yuxia.size(); i++)
            {
                if(s[yuxia[i]] <= t)
                {
                    ans.push_back(yuxia[i]);
                }
                else
                {
                    st.push(yuxia[i]);
                    sum += s[yuxia[i]];
                }
            }

            vector<int> ss;
            while (!st.empty())
            {
                ss.push_back(st.top());
                st.pop();
            }

            yuxia = ss;

            if(yuxia.size() == 0) break;
            t = (int)sum / (int)yuxia.size();
        }

        // cout << ans.size() << endl;

        Aa:

        for (int i = 0; i < ans.size(); i++)
        {
            if(i != 0)
            {
                cout << " ";
            }
            cout << ans[i];
        }
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