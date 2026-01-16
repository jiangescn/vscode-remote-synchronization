#include <bits/stdc++.h>
using namespace std;

struct s
{
    int l;
    int r;
    int i;
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<s> qj(n);

    for (int i = 0; i < n; i++)
    {
        cin >> qj[i].l >> qj[i].r;
        qj[i].i = i + 1;
    }

    sort(qj.begin(), qj.end(), [](const s& a, const s& b){
        return a.l < b.l;
    });


    for (int i = 0; i < q; i++)
    {
        int x;
        cin >> x;
        int pos = n;

        int left = 0, right = n - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 3;
            if (qj[mid].l >= x)
            {
                right = mid - 1;
                pos = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        if(x <= qj[pos - 1].r && pos > 0) cout << qj[pos - 1].i << endl;
        else cout << -1 << endl;
    }
    
    return 0;
}