#include "TextUtils.h"
#include <sstream>
#include <iomanip>
using namespace std;

namespace {
    /* 使用指定的转义字符为给定对象加引号。 */
    string quotedVersionOf(const string& str, char quoteChar) {
        ostringstream result;
        result << quoteChar;

        for (char ch: str) {
            /* 转义右引号。 */
            if (ch == '\"') result << "\\\"";
            if (ch == '\'') result << "\\\'";

            /* 转义斜杠。 */
            else if (ch == '\\') result << "\\\\";

            /* 输出其他所有可打印字符。 */
            else if (isgraph(ch) || ch == ' ') result << ch;

            /* 否则，对其进行转义。 */
            else {
                result << "\\x" << hex << setfill('0') << setw(2) << +static_cast<unsigned char>(ch);
            }
        }

        result << quoteChar;
        return result.str();
    }
}


/* TODO：待 C++14 得到更广泛支持后，替换为 std::quoted。 */
string quotedVersionOf(const string& source) {
    return quotedVersionOf(source, '"');
}
string quotedVersionOf(char source) {
    return quotedVersionOf(string(1, source), '\'');
}

/* 递归基例。 */
string format(const string& pattern) {
    /* 若存在替换位置，则说明出现了问题。 */
    if (pattern.find("%s") != string::npos) {
        error("Unmatched pattern string?");
    }
    return pattern;
}
