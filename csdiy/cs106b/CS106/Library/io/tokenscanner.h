/*
 * 文件：tokenscanner.h
 * --------------------
 * 此文件导出一个 <code>TokenScanner</code> 类，用于拆分
 * 将字符串拆分为称为<b><i>标记</i></b>的独立逻辑单元。
 *
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/23
 * - 将 TokenType 枚举移入 TokenScanner 类内部，以避免命名空间冲突
 *   （可能破坏部分客户端代码）
 * - 移除 private/tokenpatch.h
 * @version 2016/11/26
 * - 添加 getInput 方法
 * - 为提高效率，将 string 出现处替换为 const string&
 * - 按字母顺序排列方法
 * - 添加用于输出扫描器的 operator <<
 */


#ifndef _tokenscanner_h
#define _tokenscanner_h

#include <iostream>
#include <string>

/**
 * 此类将字符串拆分为单独的标记。典型的
 * 以下代码演示 <code>TokenScanner</code> 类的用法
 * 以下模式会读取字符串变量中的标记
 * <code>input</code>：
 *
 *<pre>
 *    TokenScanner scanner(input);
 *    while (scanner.hasMoreTokens()) {
 *       string token = scanner.nextToken();
 *       ... 处理标记 ...
 *    }
 *</pre>
 *
 * <code>TokenScanner</code> 类导出多个附加方法
 * 使客户端能更精细控制其行为。这些方法
 * 在文档中分别说明。
 */
class TokenScanner {
public:
    /**
     * 此枚举类型定义
     * <code>getTokenType</code> 方法。
     */
    enum TokenType {SEPARATOR, WORD, NUMBER, STRING, OPERATOR};

    /**
     * 使用空令牌流初始化扫描器对象。
     */
    TokenScanner();

    /**
     * 初始化扫描器对象。初始词元流来自
     * 指定的输入流。
     */
    TokenScanner(std::istream& infile);

    /**
     * 初始化扫描器对象。初始词元流来自
     * 指定的字符串。
     */
    TokenScanner(const std::string& str);

    /**
     * 释放与此扫描器关联的存储空间。
     */
    virtual ~TokenScanner();

    /**
     * 定义新的多字符运算符。每当调用
     * 当输入流包含运算符时调用 <code>nextToken</code>
     * 对于字符，扫描器返回尽可能长的运算符
     * 可在该位置读取的字符串。
     */
    void addOperator(const std::string& op);

    /**
     * 将 <code>str</code> 中的字符添加到字符集合
     * 在 <code>WORD</code> 令牌中合法。例如，调用
     * <code>addWordCharacters("_")</code> 将下划线添加到
     * 可作为单词一部分的字符集合。
     */
    void addWordCharacters(const std::string& str);

    /**
     * 从扫描器输入流读取下一个字符。
     */
    int getChar();

    /**
     * 返回用作此扫描器输入缓冲区的字符串，
     * 如果有的话。如果此扫描器是使用 istream 而不是
     * 字符串，则返回空字符串。
     */
    std::string getInput() const;

    /**
     * 返回扫描器在输入流中的当前位置。
     * 如果已调用 <code>saveToken</code>，此位置对应于
     * 回到已保存标记的开头。如果 <code>saveToken</code>
     * 多次调用时，<code>getPosition</code> 返回 -1。
     */
    int getPosition() const;

    /**
     * 返回令牌的字符串值。此值通过移除以下内容形成
     * 任何外围引号，并将转义序列替换为
     * 适当的字符。
     */
    std::string getStringValue(const std::string& token) const;

    /**
     * 返回此令牌的类型。此类型将匹配以下之一
     * 以下枚举类型常量：<code>EOF</code>、
     * <code>SEPARATOR</code>、<code>WORD</code>、<code>NUMBER</code>、
     * <code>STRING</code> 或 <code>OPERATOR</code>。
     */
    TokenType getTokenType(const std::string& token) const;

    /**
     * 如果此扫描器还有其他令牌，则返回 <code>true</code>
     * 供扫描器读取。
     */
    bool hasMoreTokens();

    /**
     * 指示扫描器忽略注释。扫描器包能够识别
     * C 系语言中的斜杠星号和双斜杠两种注释格式
     * 语言家族。调用：
     *
     *<pre>
     *    scanner.ignoreComments();
     *</pre>
     *
     * 设置解析器忽略注释。
     */
    void ignoreComments();

    /**
     * 指示扫描器忽略空白字符。默认情况下，
     * <code>nextToken</code> 方法将空白字符视为
     * （通常为空格和制表符），与其他标点符号一样
     * 并将它们作为单字符标记返回。
     * 调用方式：
     *
     *<pre>
     *    scanner.ignoreWhitespace();
     *</pre>
     *
     * 更改此行为，使扫描器忽略空白字符。
     */
    void ignoreWhitespace();

    /**
     * 如果字符在单词中合法，则返回 <code>true</code>。
     */
    bool isWordCharacter(char ch) const;

    /**
     * 从此扫描器返回下一个令牌。如果 <code>nextToken</code>
     * 在没有可用令牌时调用，会返回空字符串。
     */
    std::string nextToken();

    /**
     * 将指定令牌推回此扫描器的输入流。
     * 下一次调用 <code>nextToken</code> 时，扫描器将返回
     * 保存的标记，而无需从
     * 标记流。
     */
    void saveToken(const std::string& token);

    /**
     * 控制扫描器如何处理以数字开头的标记。默认情况下
     * 默认情况下，<code>nextToken</code> 方法会将数字和字母
     * 以相同方式处理，因此不提供任何特殊处理
     * 数字。调用：
     *
     *<pre>
     *    scanner.scanNumbers();
     *</pre>
     *
     * 更改此行为，使 <code>nextToken</code> 返回
     * 可解释为实数的最长子字符串。
     */
    void scanNumbers();

    /**
     * 控制扫描器如何处理用引号括起的标记。默认情况下
     * 默认情况下，引号（单引号或双引号）与其他字符一样处理
     * 任何其他标点字符。调用：
     *
     *<pre>
     *    scanner.scanStrings();
     *</pre>
     *
     * 更改此假设，使 <code>nextToken</code> 返回单个
     * 由直到匹配右引号为止的所有字符组成的标记。
     * 引号会作为扫描到的标记的一部分返回，因此
     * 客户端可将字符串与其他标记类型区分开。
     */
    void scanStrings();

    /**
     * 将此扫描器的令牌流设置为指定输入流。
     * 丢弃之前的所有词元流。
     */
    void setInput(std::istream& infile);

    /**
     * 将此扫描器的令牌流设置为指定字符串。
     * 丢弃之前的所有词元流。
     */
    void setInput(const std::string& str);

    /**
     * 将字符 <code>ch</code> 推回扫描器流。
     * 字符必须与读取的字符匹配。
     */
    void ungetChar(int ch);

    /**
     * 读取下一个令牌并确保其与字符串匹配
     * <code>expected</code>。如果不匹配，<code>verifyToken</code>
     * 抛出错误。
     * @throw 如果下一个标记与给定字符串不匹配，则抛出 ErrorException
     */
    void verifyToken(const std::string& expected);

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

private:
    /*
     * 私有类型：StringCell
     * ------------------------
     * 此类型用于构造单元格链表，这些链表用于
     * 同时表示已保存标记的栈和已定义项的集合
     * 运算符。这些类型不能使用 Stack 和 Lexicon 类
     * 直接使用，因为 tokenscanner.h 是非常底层的接口，
     * 否则会在 .h 文件中产生循环依赖。
     */
    struct StringCell {
        std::string str;
        StringCell *link;
    };

    enum NumberScannerState {
        INITIAL_STATE,
        BEFORE_DECIMAL_POINT,
        AFTER_DECIMAL_POINT,
        STARTING_EXPONENT,
        FOUND_EXPONENT_SIGN,
        SCANNING_EXPONENT,
        FINAL_STATE
    };

    std::string buffer;              /* 原始参数字符串 */
    std::istream* isp;               /* 标记的输入流  */
    bool stringInputFlag;            /* 表示字符串输入的标志 */
    bool ignoreWhitespaceFlag;       /* 扫描器忽略空白   */
    bool ignoreCommentsFlag;         /* 扫描器忽略注释     */
    bool scanNumbersFlag;            /* 扫描器解析数字       */
    bool scanStringsFlag;            /* 扫描器解析字符串       */
    std::string wordChars;           /* 其他单词字符   */
    StringCell* savedTokens;         /* 已保存令牌的栈        */
    StringCell* operators;           /* 多字符运算符列表  */

    /* 私有方法原型 */
    void initScanner();
    bool isOperator(const std::string& op);
    bool isOperatorPrefix(const std::string& op);
    std::string scanNumber();
    std::string scanString();
    std::string scanWord();
    void skipSpaces();

    friend std::ostream& operator <<(std::ostream& out, const TokenScanner& scanner);
};

/**
 * 将令牌扫描器打印到给定输出流。
 */
std::ostream& operator <<(std::ostream& out, const TokenScanner& scanner);

#endif // _tokenscanner_h
