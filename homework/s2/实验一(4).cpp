    #include <bits/stdc++.h>
    #include <ctime>
    using namespace std;

    class date
    {
    public: 
        date(string s);
        date(int NewY, int NewM, int NewD);
        date();

        void show();
    private:
        int y, m, d;
    };

    date::date(int NewY, int NewM, int NewD)
    {
        y = NewY;
        m = NewM;
        d = NewD;
    }

    date::date(string s)
    {
        string sY = s.substr(0, 4);
        string sM = s.substr(5, 2);
        string sD = s.substr(8, 2);

        y = stoll(sY);
        m = stoll(sM);
        d = stoll(sD);
    }

    date::date()
    {
        time_t now = time(0);
        tm *localTime = localtime(&now);

        y = localTime->tm_year + 1900;
        m = localTime->tm_mon + 1;
        d = localTime->tm_mday;
    }

    void date::show()
    {
        printf("%04d年 %02d月 %02d日\n", y, m, d);
        // cout << y << "年 " << m << "月 " << d << "日" << endl;
    }

    int main()
    {
        date d1, d2(2011, 3, 8), d3("2011-03-19");

        d1.show();
        d2.show();
        d3.show();

        return 0;
    }