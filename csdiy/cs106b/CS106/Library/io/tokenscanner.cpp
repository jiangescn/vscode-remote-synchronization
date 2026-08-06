/*
 * 文件：tokenscanner.cpp
 * ----------------------
 * TokenScanner 类的实现。
 * 
 * @version 2016/11/26
 * - 添加 getInput 方法
 * - 为提高效率，将 string 出现处替换为 const string&
 * - 按字母顺序排列方法
 * - 添加用于输出扫描器的 operator <<
 * @version 2014/10/08
 * - 移除“using namespace”语句
 */

#include "tokenscanner.h"
#include <cctype>
#include <iostream>
#include "error.h"
#include "strlib.h"
#include "stack.h"

TokenScanner::TokenScanner() {
    initScanner();
    setInput("");
}

TokenScanner::TokenScanner(std::istream& infile) {
    initScanner();
    setInput(infile);
}

TokenScanner::TokenScanner(const std::string& str) {
    initScanner();
    setInput(str);
}

TokenScanner::~TokenScanner() {
    if (stringInputFlag) {
        delete isp;
    }
}

void TokenScanner::addOperator(const std::string& op) {
    StringCell* cp = new StringCell;
    cp->str = op;
    cp->link = operators;
    operators = cp;
}

void TokenScanner::addWordCharacters(const std::string& str) {
    wordChars += str;
}

int TokenScanner::getChar() {
    return isp->get();
}

std::string TokenScanner::getInput() const {
    return buffer;
}

int TokenScanner::getPosition() const {
    if (!savedTokens) {
        return int(isp->tellg());
    } else {
        return int(isp->tellg()) - savedTokens->str.length();
    }
}

std::string TokenScanner::getStringValue(const std::string& token) const {
    std::string str = "";
    int start = 0;
    int finish = token.length();
    if (finish > 1 && (token[0] == '"' || token[0] == '\'')) {
        start = 1;
        finish--;
    }
    for (int i = start; i < finish; i++) {
        char ch = token[i];
        if (ch == '\\') {
            ch = token[++i];
            if (isdigit(ch) || ch == 'x') {
                int base = 8;
                if (ch == 'x') {
                    base = 16;
                    i++;
                }
                int result = 0;
                int digit = 0;
                while (i < finish) {
                    ch = token[i];
                    if (isdigit(ch)) {
                        digit = ch - '0';
                    } else if (isalpha(ch)) {
                        digit = toupper(ch) - 'A' + 10;
                    } else {
                        digit = base;
                    }
                    if (digit >= base) {
                        break;
                    }
                    result = base * result + digit;
                    i++;
                }
                ch = char(result);
                i--;
            } else {
                switch (ch) {
                case 'a': ch = '\a'; break;
                case 'b': ch = '\b'; break;
                case 'f': ch = '\f'; break;
                case 'n': ch = '\n'; break;
                case 'r': ch = '\r'; break;
                case 't': ch = '\t'; break;
                case 'v': ch = '\v'; break;
                case '"': ch = '"'; break;
                case '\'': ch = '\''; break;
                case '\\': ch = '\\'; break;
                }
            }
        }
        str += ch;
    }
    return str;
}

TokenScanner::TokenType TokenScanner::getTokenType(const std::string& token) const {
    if (token.empty()) {
        return TokenType(EOF);
    }

    char ch = token[0];
    if (isspace(ch)) {
        return SEPARATOR;
    } else if (ch == '"' || (ch == '\'' && token.length() > 1)) {
        return STRING;
    } else if (isdigit(ch)) {
        return NUMBER;
    } else if (isWordCharacter(ch)) {
        return WORD;
    } else {
        return OPERATOR;
    }
}

bool TokenScanner::hasMoreTokens() {
    std::string token = nextToken();
    saveToken(token);
    return !token.empty();
}

void TokenScanner::ignoreComments() {
    ignoreCommentsFlag = true;
}

void TokenScanner::ignoreWhitespace() {
    ignoreWhitespaceFlag = true;
}

bool TokenScanner::isWordCharacter(char ch) const {
    return isalnum(ch) || wordChars.find(ch) != std::string::npos;
}

std::string TokenScanner::nextToken() {
    if (savedTokens) {
        StringCell* cp = savedTokens;
        std::string token = cp->str;
        savedTokens = cp->link;
        delete cp;
        return token;
    }

    while (true) {
        if (ignoreWhitespaceFlag) {
            skipSpaces();
        }
        int ch = isp->get();
        if (ch == '/' && ignoreCommentsFlag) {
            ch = isp->get();
            if (ch == '/') {
                while (true) {
                    ch = isp->get();
                    if (ch == '\n' || ch == '\r' || ch == EOF) {
                        break;
                    }
                }
                continue;
            } else if (ch == '*') {
                int prev = EOF;
                while (true) {
                    ch = isp->get();
                    if (ch == EOF || (prev == '*' && ch == '/')) {
                        break;
                    }
                    prev = ch;
                }
                continue;
            }
            if (ch != EOF) {
                isp->unget();
            }
            ch = '/';
        }
        if (ch == EOF) {
            return "";
        }
        if ((ch == '"' || ch == '\'') && scanStringsFlag) {
            isp->unget();
            return scanString();
        }
        if (isdigit(ch) && scanNumbersFlag) {
            isp->unget();
            return scanNumber();
        }
        if (isWordCharacter(ch)) {
            isp->unget();
            return scanWord();
        }
        std::string op = std::string(1, ch);
        while (isOperatorPrefix(op)) {
            ch = isp->get();
            if (ch == EOF) {
                break;
            }
            op += ch;
        }
        while (op.length() > 1 && !isOperator(op)) {
            isp->unget();
            op.erase(op.length() - 1, 1);
        }
        return op;
    }
}

void TokenScanner::saveToken(const std::string& token) {
    StringCell* cp = new StringCell;
    cp->str = token;
    cp->link = savedTokens;
    savedTokens = cp;
}

void TokenScanner::scanNumbers() {
    scanNumbersFlag = true;
}

void TokenScanner::scanStrings() {
    scanStringsFlag = true;
}

void TokenScanner::setInput(std::istream& infile) {
    stringInputFlag = false;
    isp = &infile;
    savedTokens = nullptr;
}

void TokenScanner::setInput(const std::string& str) {
    stringInputFlag = true;
    buffer = str;
    isp = new std::istringstream(buffer);
    savedTokens = nullptr;
}

void TokenScanner::ungetChar(int) {
    isp->unget();
}

void TokenScanner::verifyToken(const std::string& expected) {
    std::string token = nextToken();
    if (token != expected) {
        std::string msg = "TokenScanner::verifyToken: Found \"" + token + "\""
                + " when expecting \"" + expected + "\"";
        if (!buffer.empty()) {
            msg += "\ninput = \"" + buffer + "\"";
        }
        error(msg);
    }
}

/* 私有方法 */

void TokenScanner::initScanner() {
    ignoreWhitespaceFlag = false;
    ignoreCommentsFlag = false;
    scanNumbersFlag = false;
    scanStringsFlag = false;
    operators = nullptr;
}

/*
 * 实现说明：isOperator、isOperatorPrefix
 * --------------------------------------------------
 * 这些方法搜索运算符列表，并在
 * 指定运算符是否在列表中，或是否为某个运算符的前缀
 * 分别位于列表中。此代码可以大幅
 * 通过将运算符实现为 trie 来提高效率。
 */
bool TokenScanner::isOperator(const std::string& op) {
    for (StringCell *cp = operators; cp != nullptr; cp = cp->link) {
        if (op == cp->str) {
            return true;
        }
    }
    return false;
}

bool TokenScanner::isOperatorPrefix(const std::string& op) {
    for (StringCell* cp = operators; cp != nullptr; cp = cp->link) {
        if (startsWith(cp->str, op)) {
            return true;
        }
    }
    return false;
}

/*
 * 实现说明：scanNumber
 * --------------------------------
 * 读取字符，直到扫描器到达合法数字末尾。
 * 该函数通过模拟计算机科学家所说的过程运行
 * 称为有限状态机。程序使用变量
 * 使用 <code>state</code> 记录过程历史，并
 * 确定此时哪些字符是合法的。
 */
std::string TokenScanner::scanNumber() {
    std::string token = "";
    NumberScannerState state = INITIAL_STATE;
    while (state != FINAL_STATE) {
        int ch = isp->get();
        switch (state) {
        case INITIAL_STATE:
            if (!isdigit(ch)) {
                error("TokenScanner::scanNumber: internal error: illegal call");
            }
            state = BEFORE_DECIMAL_POINT;
            break;
        case BEFORE_DECIMAL_POINT:
            if (ch == '.') {
                state = AFTER_DECIMAL_POINT;
            } else if (ch == 'E' || ch == 'e') {
                state = STARTING_EXPONENT;
            } else if (!isdigit(ch)) {
                if (ch != EOF) {
                    isp->unget();
                }
                state = FINAL_STATE;
            }
            break;
        case AFTER_DECIMAL_POINT:
            if (ch == 'E' || ch == 'e') {
                state = STARTING_EXPONENT;
            } else if (!isdigit(ch)) {
                if (ch != EOF) {
                    isp->unget();
                }
                state = FINAL_STATE;
            }
            break;
        case STARTING_EXPONENT:
            if (ch == '+' || ch == '-') {
                state = FOUND_EXPONENT_SIGN;
            } else if (isdigit(ch)) {
                state = SCANNING_EXPONENT;
            } else {
                if (ch != EOF) {
                    isp->unget();
                }
                isp->unget();
                state = FINAL_STATE;
            }
            break;
        case FOUND_EXPONENT_SIGN:
            if (isdigit(ch)) {
                state = SCANNING_EXPONENT;
            } else {
                if (ch != EOF) {
                    isp->unget();
                }
                isp->unget();
                isp->unget();
                state = FINAL_STATE;
            }
            break;
        case SCANNING_EXPONENT:
            if (!isdigit(ch)) {
                if (ch != EOF) {
                    isp->unget();
                }
                state = FINAL_STATE;
            }
            break;
        default:
            state = FINAL_STATE;
            break;
        }
        if (state != FINAL_STATE) {
            token += char(ch);
        }
    }
    return token;
}

/*
 * 实现说明：scanString
 * --------------------------------
 * 从扫描器读取并返回带引号字符串，持续到
 * 它会扫描匹配的分隔符。如果
 * 在输入结束前没有右引号。
 */
std::string TokenScanner::scanString() {
    std::string token = "";
    char delim = isp->get();
    token += delim;
    bool escape = false;
    while (true) {
        int ch = isp->get();
        if (ch == EOF) {
            error("TokenScanner::scanString: found unterminated string");
        }
        if (ch == delim && !escape) {
            break;
        }
        escape = (ch == '\\') && !escape;
        token += ch;
    }
    return token + delim;
}

/*
 * 实现说明：scanWord
 * ------------------------------
 * 读取字符，直到扫描器到达一段序列的末尾
 * 单词字符。
 */
std::string TokenScanner::scanWord() {
    std::string token = "";
    while (true) {
        int ch = isp->get();
        if (ch == EOF) {
            break;
        }
        if (!isWordCharacter(ch)) {
            isp->unget();
            break;
        }
        token += char(ch);
    }
    return token;
}

/*
 * 实现说明：skipSpaces
 * --------------------------------
 * 推进扫描器位置，直到当前字符为
 * 不是空白字符。
 */
void TokenScanner::skipSpaces() {
    while (true) {
        int ch = isp->get();
        if (ch == EOF) {
            return;
        }
        if (!isspace(ch)) {
            isp->unget();
            return;
        }
    }
}

std::ostream& operator <<(std::ostream& out, const TokenScanner& scanner) {
    out << "TokenScanner{";
    bool first = true;
    if (!scanner.buffer.empty()) {
        out << "input=\"" << scanner.buffer << "\"";
        first = false;
    }
    out << (first ? "" : ",") << "position=" << scanner.getPosition();
    first = false;

    if (scanner.scanNumbersFlag) {
        out << (first ? "" : ",") << "scanNumbers";
        first = false;
    }
    if (scanner.scanStringsFlag) {
        out << (first ? "" : ",") << "scanStrings";
        first = false;
    }
    if (!scanner.wordChars.empty()) {
        out << (first ? "" : ",") << "wordChars=[" << scanner.wordChars << "]";
        first = false;
    }
    if (scanner.ignoreWhitespaceFlag) {
        out << (first ? "" : ",") << "ignoreWhitespace";
        first = false;
    }
    if (scanner.ignoreCommentsFlag) {
        out << (first ? "" : ",") << "ignoreComments";
        // first = false;
    }
    out << "}";
    return out;
}
