#include <iostream>
#include <iomanip>
using namespace std;

class Clock
{
private:
    int hour, minute, second;

    int toSeconds() const
    {
        return hour * 3600 + minute * 60 + second;
    }

    static Clock fromSeconds(int total)
    {
        total %= 24 * 3600;
        if (total < 0)
            total += 24 * 3600;
        return Clock(total / 3600, total % 3600 / 60, total % 60);
    }

public:
    Clock(int h = 0, int m = 0, int s = 0)
    {
        int total = h * 3600 + m * 60 + s;
        total %= 24 * 3600;
        if (total < 0)
            total += 24 * 3600;

        hour = total / 3600;
        minute = total % 3600 / 60;
        second = total % 60;
    }

    Clock operator+(int s) const
    {
        return fromSeconds(toSeconds() + s);
    }

    Clock operator-(int s) const
    {
        return fromSeconds(toSeconds() - s);
    }

    Clock &operator++()
    {
        *this = *this + 1;
        return *this;
    }

    Clock operator++(int)
    {
        Clock old = *this;
        ++(*this);
        return old;
    }

    Clock &operator--()
    {
        *this = *this - 1;
        return *this;
    }

    Clock operator--(int)
    {
        Clock old = *this;
        --(*this);
        return old;
    }

    void show() const
    {
        cout << setfill('0') << setw(2) << hour << ":"
             << setw(2) << minute << ":"
             << setw(2) << second << setfill(' ') << endl;
    }
};

int main()
{
    Clock c(23, 59, 59);

    cout << "原时间：";
    c.show();

    cout << "c + 2 秒：";
    (c + 2).show();

    cout << "c - 60 秒：";
    (c - 60).show();

    cout << "++c：";
    (++c).show();

    cout << "c++ 返回：";
    (c++).show();

    cout << "c++ 后 c：";
    c.show();

    cout << "--c：";
    (--c).show();

    cout << "c-- 返回：";
    (c--).show();

    cout << "c-- 后 c：";
    c.show();

    return 0;
}