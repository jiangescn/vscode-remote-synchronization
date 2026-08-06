#include "DataPoint.h"
#include "strlib.h"
#include <sstream>
#include <iomanip>
using namespace std;

/* 用于读写带引号字符串的实用工具。
 *
 * TODO：一旦满足以下条件，应将此处替换为使用 std::quoted：
 * Windows 上支持 C++14。
 */
namespace {
    string quotedVersionOf(const string& source) {
        ostringstream result;
        result << '"';

        for (char ch: source) {
            /* 转义右引号。 */
            if (ch == '"') result << "\\\"";

            /* 转义斜杠。 */
            else if (ch == '\\') result << "\\\\";

            /* 输出其他所有可打印字符。 */
            else if (isgraph(ch) || ch == ' ') result << ch;

            /* 否则，对其进行转义。 */
            else {
                result << "\\x" << hex << setfill('0') << setw(2) << +static_cast<unsigned char>(ch);
            }
        }

        result << '"';
        return result.str();
    }

    /* 读取带引号的字符串。 */
    bool readQuoted(istream& in, string& out) {
        /* 读取一个字符；它必须是引号。 */
        char read;
        in >> read;

        if (!in || read != '"') return false;

        /* 持续读取，直到遇到右引号。 */
        string result;
        while (true) {
            /* 无法读取？这是个问题！ */
            if (!in.get(read)) return false;

            /* 若这是引号，则处理完成。 */
            else if (read == '"') break;

            /* 否则，如果它是斜杠，则将其视为转义符。 */
            else if (read == '\\') {
                /* 获取下一个字符以确定应执行什么操作。 */
                if (!in.get(read)) return false;

                /* 输出斜杠和引号。 */
                else if (read == '\\' || read == '"') result += read;

                /* 十六进制？读取两个字符并解码。 */
                else if (read == 'x') {
                    string hexCode;
                    in >> setw(2) >> hexCode;
                    if (!in) return false;

                    /* 将其转换为数字。 */
                    try {
                        result += static_cast<char>(stringToInteger(hexCode, 16));
                    } catch (const ErrorException& e) {
                        return false;
                    }
                }
                /* 否则，我们无法判断它是什么。 */
                else return false;
            }

            /* 否则，直接追加它。 */
            else result += read;
        }

        out = result;
        return true;
    }
}

/* 相等性比较。 */
bool operator== (const DataPoint& lhs, const DataPoint& rhs) {
    return lhs.name == rhs.name && lhs.weight == rhs.weight;
}

/* 当两点不相等时，不等关系成立。 */
bool operator!= (const DataPoint& lhs, const DataPoint& rhs) {
    return !(lhs == rhs);
}

/* 将 DataPoint 打印到流。输出格式为
 *
 *   { "数据点名称，\"已正确转义\"": pt.weight }
 */
ostream& operator<< (ostream& out, const DataPoint& pt) {
    ostringstream builder;
    builder << "{ " << quotedVersionOf(pt.name) << ", " << pt.weight << " }";
    return out << builder.str();
}

/* 从流中读取一个 DataPoint。 */
istream& operator>> (istream& in, DataPoint& result) {
    istream::sentry sentry(in);
    if (sentry) {
        /* 获取下一个字符；它应当是左花括号。 */
        char expected;
        in >> ws >> expected;
        if (!in || expected != '{') {
            in.setstate(ios::failbit);
            return in;
        }

        /* 提取字符串。 */
        DataPoint read;
        in >> ws;
        if (!readQuoted(in, read.name) || !in) {
            in.setstate(ios::failbit);
            return in;
        }

        /* 确认这里有逗号。 */
        in >> ws >> expected;
        if (!in || expected != ',') {
            in.setstate(ios::failbit);
            return in;
        }

        /* 读取权重。 */
        in >> ws >> read.weight;
        if (!in) {
            in.setstate(ios::failbit);
            return in;
        }

        /* 读取右花括号。 */
        in >> ws >> expected;
        if (!in || expected != '}') {
            in.setstate(ios::failbit);
            return in;
        }

        result = read;
    }
    return in;
}
