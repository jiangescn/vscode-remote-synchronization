#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

class String
{
private:
    char *p;
    int len;

    void copyFrom(const char *s)
    {
        if (s == nullptr)
            s = "";

        len = (int)strlen(s);
        p = new char[len + 1];
        strcpy(p, s);
    }

public:
    String()
    {
        copyFrom("");
    }

    String(const char *s)
    {
        copyFrom(s);
    }

    String(const String &s)
    {
        copyFrom(s.p);
    }

    ~String()
    {
        delete[] p;
    }

    int Length() const
    {
        return len;
    }

    String &operator=(const char *s)
    {
        if (s == nullptr)
            s = "";

        char *temp = new char[strlen(s) + 1];
        strcpy(temp, s);

        delete[] p;
        p = temp;
        len = (int)strlen(p);

        return *this;
    }

    String &operator=(const String &s)
    {
        if (this != &s)
        {
            *this = s.p;
        }
        return *this;
    }

    String &operator+=(const String &s)
    {
        char *temp = new char[len + s.len + 1];

        strcpy(temp, p);
        strcat(temp, s.p);

        delete[] p;
        p = temp;
        len = (int)strlen(p);

        return *this;
    }

    char &operator[](int index)
    {
        return p[index];
    }

    const char &operator[](int index) const
    {
        return p[index];
    }

    friend String operator+(const String &s1, const String &s2);
    friend bool operator==(const String &s1, const String &s2);
    friend bool operator<(const String &s1, const String &s2);
    friend ostream &operator<<(ostream &out, const String &s);
    friend istream &operator>>(istream &in, String &s);
};

String operator+(const String &s1, const String &s2)
{
    String result;

    delete[] result.p;

    result.len = s1.len + s2.len;
    result.p = new char[result.len + 1];

    strcpy(result.p, s1.p);
    strcat(result.p, s2.p);

    return result;
}

bool operator==(const String &s1, const String &s2)
{
    return strcmp(s1.p, s2.p) == 0;
}

bool operator<(const String &s1, const String &s2)
{
    return strcmp(s1.p, s2.p) < 0;
}

ostream &operator<<(ostream &out, const String &s)
{
    out << s.p;
    return out;
}

istream &operator>>(istream &in, String &s)
{
    char buffer[1000];
    in >> setw(1000) >> buffer;
    s = buffer;
    return in;
}

int main()
{
    String s1("Help!"), s2("Good!"), s3(s2), s4, s5;

    cout << "s1=" << s1 << endl;

    s3 = "Hello!";
    cout << "s3=" << s3 << endl;

    s3 = s2;
    cout << "s3=" << s3 << endl;

    s3 += s2;
    cout << "s3=" << s3 << endl;

    cout << "请输入s4：";
    cin >> s4;

    cout << "s4=" << s4 << endl;

    s5 = s3 + s4;
    cout << "s5=" << s5 << endl;

    s5[0] = 'g';
    cout << "s5=" << s5 << endl;

    cout << "strlen(s5)=" << s5.Length() << endl;

    cout << boolalpha << (s3 == s1) << endl;
    cout << boolalpha << (s3 < s1) << endl;

    return 0;
}