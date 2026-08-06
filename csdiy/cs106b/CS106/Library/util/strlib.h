/*
 * 文件：strlib.h
 * --------------
 * 此文件导出若干有用但未
 * 包含在 C++ 字符串库中。
 *
 * @version 2018/11/14
 * - 为 bool、char、指针和通用模板类型 T 添加 std::to_string
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/02
 * - 添加 padLeft、padRight
 * @version 2016/11/09
 * - 向 writeGenericValue 添加 boolalpha（改进 bool 输出，位于
 *   集合的 toString 输出）
 * @version 2016/10/30
 * - 添加接受 char 类型而非 string 的重载：
 *   stringContains、stringIndexOf、stringJoin、stringLastIndexOf、stringReplace、
 *   stringSplit、toLowerCase、toUpperCase
 * @version 2016/10/26
 * - 修复 stringLastIndexOf 默认索引参数的错误
 * @version 2016/10/13
 * - 修改 writeGenericValue、writeQuotedString，使其返回 ostream
 * @version 2016/08/03
 * - 修改 readGenericValue，使其解析失败时不调用 error()
 *   （用于支持符合惯用法、静默失败的 >> 运算符）
 * @version 2015/10/26
 * - 添加 charToInteger/integerToChar 函数
 * @version 2015/08/02
 * - 添加 htmlEncode/Decode 函数（并非完全完善，但适用于常见情况）
 * @version 2014/10/19
 * - 按字母顺序排列函数
 * - 为若干现有返回字符串的函数添加“inPlace”原地版本
 * @version 2014/10/08
 * - 移除对“using namespace”语句的依赖
 */


#ifndef _strlib_h
#define _strlib_h

#include <iostream>
#include <sstream>
#include <string>

#include "vector.h"

/**
 * 如果 b 为 true，则返回字符串“true”；否则返回“false”。
 */
std::string boolToString(bool b);

/**
 * 如果 b 非零，返回字符串 "true"；如果 b 为 0，返回 "false"。
 */
std::string boolToString(int b);

/**
 * 返回与给定数字字符等价的整数。
 * 例如，charToInteger('3') 返回 int 3。
 * 如果字符不在 '0' 到 '9' 之间，则抛出错误。
 */
int charToInteger(char c);

/**
 * 返回包含给定字符的单字符字符串。
 * 例如，charToString('Q') 返回字符串 "Q"。
 */
std::string charToString(char c);

/**
 * 将浮点数转换为对应字符串形式。
 * 例如，调用 <code>doubleToString(23.45)</code> 返回
 * 字符串 <code>"23.45"</code>。
 * 等价于 realToString。
 */
std::string doubleToString(double d);

/**
 * 如果字符串 <code>str</code> 以指定内容结尾，则返回 <code>true</code>
 * 指定的后缀。
 */
bool endsWith(const std::string& str, const std::string& suffix);

/**
 * 如果字符串 <code>str</code> 以指定内容结尾，则返回 <code>true</code>
 * 指定字符。
 */
bool endsWith(const std::string& str, char suffix);

/**
 * 如果 <code>s1</code> 和 <code>s2</code> 满足以下条件，则返回 <code>true</code>
 * 相等，忽略大小写差异。
 */
bool equalsIgnoreCase(const std::string& s1, const std::string& s2);

/**
 * 将给定字符串从 HTML 编码版本转换为解码后的
 * 等价操作；与 htmlEncode 相反。任何转义的 HTML 字符实体
 * 会替换为其取消转义后的等价内容。
 * 例如，<code>htmlEncode("&lt;p class=&quot;abc&quot;&gt;我爱你和我&lt;/p&gt;")
 * 返回 "<p class=\"abc\">I love you & me</p>"。
 */
std::string htmlDecode(const std::string& s);

/**
 * 将给定字符串转换为 HTML 编码的等价版本，其中
 * 将任何相关 HTML 字符实体替换为转义后的等价形式。
 * 例如，<code>htmlEncode("<p class=\"abc\">我爱你和我</p>") 返回
 * “&lt;p class=&quot;abc&quot;&gt;我爱你和我&lt;/p&gt;”。
 */
std::string htmlEncode(const std::string& s);

/**
 * 将整数转换为对应的数字字符。
 * 例如，调用 <code>integerToChar(3)</code> 返回
 * 字符 <code>'3'</code>。
 * @throw 如果给定整数不是 0-9（含）之间的单个数字，则抛出 ErrorException
 */
char integerToChar(int n);

/**
 * 将整数转换为对应的数字字符串。
 * 例如，调用 <code>integerToString(123)</code> 返回
 * 字符串 <code>"123"</code>。
 */
std::string integerToString(int n, int radix = 10);

/**
 * 将整数转换为对应的数字字符串。
 * 例如，调用 <code>longToString(123)</code> 返回
 * 字符串 <code>"123"</code>。
 */
std::string longToString(long n, int radix = 10);

/**
 * 在给定字符串开头插入空格，直到其长度至少为
 * 给定长度。
 * 可以选择传入填充字符（空格以外）作为第三个参数。
 *
 * 请注意，如果你正在打印字符串并希望输出对齐
 * 若需要按给定字符数处理，使用内置功能可能更合适
 * C++ ostream 操纵器，例如 iomanip 中定义的 setw(int)、left 和 right
 * iomanip 库。
 */
std::string padLeft(const std::string& s, int length, char fill = ' ');

/**
 * 在给定字符串末尾插入空格，直到其长度至少为
 * 给定长度。
 * 可以选择传入填充字符（空格以外）作为第三个参数。
 *
 * 请注意，如果你正在打印字符串并希望输出对齐
 * 若需要按给定字符数处理，使用内置功能可能更合适
 * C++ ostream 操纵器，例如 iomanip 中定义的 setw(int)、left 和 right
 * iomanip 库。
 */
std::string padRight(const std::string& s, int length);

/**
 * 返回给定指针的十六进制字符串，例如“0x3f0427b”。
 * 如果 p 是空指针，则返回“nullptr”。
 */
std::string pointerToString(void* p);

/**
 * 将浮点数转换为对应字符串形式。
 * 例如，调用 <code>realToString(23.45)</code> 返回
 * 字符串 <code>"23.45"</code>。
 */
std::string realToString(double d);

/**
 * 如果字符串 <code>str</code> 以指定内容开头，则返回 <code>true</code>
 * 指定的前缀。
 */
bool startsWith(const std::string& str, char prefix);

/**
 * 如果字符串 <code>str</code> 以指定内容开头，则返回 <code>true</code>
 * 指定字符。
 */
bool startsWith(const std::string& str, const std::string& prefix);

/**
 * 如果给定字符出现在 s 中，则返回 true。
 */
bool stringContains(const std::string& s, char ch);

/**
 * 如果给定子字符串出现在 s 中，则返回 true。
 */
bool stringContains(const std::string& s, const std::string& substring);

/**
 * 返回给定字符第一次出现位置的起始索引
 * 若它出现在 s 中，则返回它在 s 中的位置；若未出现，则返回 -1。
 * 此函数与 string.find 非常相似，但 find 返回 string::npos
 * 当找不到该字符串时。
 */
int stringIndexOf(const std::string& s, char ch, int startIndex = 0);

/**
 * 返回给定子字符串第一次出现位置的起始索引
 * 若它出现在 s 中，则返回它在 s 中的位置；若未出现，则返回 -1。
 * 此函数与 string.find 非常相似，但 find 返回 string::npos
 * 当找不到该字符串时。
 */
int stringIndexOf(const std::string& s, const std::string& substring, int startIndex = 0);

/**
 * 如果给定字符串是 "true" 或 "false"，则返回 true。
 */
bool stringIsBool(const std::string& str);

/**
 * 如果给定字符串可以转换为实数，则返回 true
 * 能够由 stringToReal 函数成功转换；如果可以，则为 true
 * 字符串具有实数格式，例如“3.14”或“-46”。
 * 等价于 stringIsReal。
 */
bool stringIsDouble(const std::string& str);   // 别名

/**
 * 如果给定字符串可转换为整数，则返回 true
 * 可由 stringToInteger 函数成功转换；在以下情况下为 true
 * 字符串具有整数格式，例如“1234”或“-8”。
 * 如果不希望使用十进制，可选择接受 radix（基数）参数。
 */
bool stringIsInteger(const std::string& str, int radix = 10);

/**
 * 如果给定字符串可转换为 long，则返回 true
 * 可由 stringToLong 函数成功转换；在以下情况下为 true
 * 字符串具有整数格式，例如“1234”或“-8”。
 * 如果不希望使用十进制，可选择接受 radix（基数）参数。
 */
bool stringIsLong(const std::string& str, int radix = 10);

/**
 * 如果给定字符串可以转换为实数，则返回 true
 * 能够由 stringToReal 函数成功转换；如果可以，则为 true
 * 字符串具有实数格式，例如“3.14”或“-46”。
 */
bool stringIsReal(const std::string& str);

/**
 * 将给定 Vector 的元素合并为单个字符串，
 * 使用给定分隔符分隔相邻元素，并将其返回。
 * 例如，连接向量中的元素
 * {"Hi", "there", "", "Jim"} 使用分隔符 '?' 时返回 "Hi?there??Jim"。
 */
std::string stringJoin(const Vector<std::string>& v, char delimiter = '\n');

/**
 * 将给定 Vector 的元素合并为单个字符串，
 * 使用给定分隔符分隔相邻元素，并将其返回。
 * 例如，连接向量中的元素
 * {"Hi", "there", "", "Jim"} 使用分隔符 "??" 时返回 "Hi??there????Jim"。
 */
std::string stringJoin(const Vector<std::string>& v, const std::string& delimiter = "\n");

/**
 * 返回给定字符最后一次出现位置的起始索引
 * 若它出现在 s 中，则返回它在 s 中的位置；若未出现，则返回 -1。
 * 此函数与 string.rfind 非常相似，但 rfind 返回 string::npos
 * 当找不到该字符串时。
 */
int stringLastIndexOf(const std::string& s, char ch, int startIndex = (int) std::string::npos);

/**
 * 返回给定子字符串最后一次出现位置的起始索引
 * 若它出现在 s 中，则返回它在 s 中的位置；若未出现，则返回 -1。
 * 此函数与 string.rfind 非常相似，但 rfind 返回 string::npos
 * 当找不到该字符串时。
 */
int stringLastIndexOf(const std::string& s, const std::string& substring, int startIndex = (int) std::string::npos);

/**
 * 返回一个新字符串，其中给定“old”的所有出现位置均被替换
 * 将“str”中的字符替换为给定替代字符。
 * 请注意，这不是正则表达式替换；它会查找
 * 字面量“old”字符串。若要使用正则表达式，请参阅 regexpr.h。
 * “inPlace”变体会修改现有字符串，而不是返回新字符串，
 * 并返回被替换的“old”出现次数。
 */
std::string stringReplace(const std::string& str, char old, char replacement, int limit = -1);

/**
 * 返回一个新字符串，其中给定“old”的所有出现位置均被替换
 * 用 'str' 中给定替换文本替换文本。
 * 请注意，这不是正则表达式替换；它会查找
 * 字面量“old”字符串。若要使用正则表达式，请参阅 regexpr.h。
 * “inPlace”变体会修改现有字符串，而不是返回新字符串，
 * 并返回被替换的“old”出现次数。
 */
std::string stringReplace(const std::string& str, const std::string& old, const std::string& replacement, int limit = -1);

/**
 * stringReplace 的变体，但它通过引用接收字符串
 * 并就地修改它，而不是返回新字符串。
 */
int stringReplaceInPlace(std::string& str, char old, char replacement, int limit = -1);

/**
 * stringReplace 的变体，但它通过引用接收字符串
 * 并就地修改它，而不是返回新字符串。
 */
int stringReplaceInPlace(std::string& str, const std::string& old, const std::string& replacement, int limit = -1);

/**
 * 返回一个向量，其元素是通过拆分以下内容形成的字符串：
 * 使用给定分隔字符拆分给定字符串“str”。
 * 相邻分隔符会合并。
 * 例如，以分隔符 " " 拆分 "Hi there    Jim!" 会返回
 * {"Hi", "there", "Jim!"}。
 */
Vector<std::string> stringSplit(const std::string& str, char delimiter, int limit = -1);

/**
 * 返回一个向量，其元素是通过拆分以下内容形成的字符串：
 * 使用给定分隔文本拆分给定字符串“str”。
 * 相邻分隔符会合并。
 * 例如，以分隔符 " " 拆分 "Hi there    Jim!" 会返回
 * {"Hi", "there", "Jim!"}。
 */
Vector<std::string> stringSplit(const std::string& str, const std::string& delimiter, int limit = -1);

/**
 * 若 str 为 "true"，返回 bool 值 true。
 * 若 str 为 "false"，返回 bool 值 false。
 * @throw 如果 str 不是 "true" 或 "false"，则抛出 ErrorException
 */
bool stringToBool(const std::string& str);

/**
 * 将单字符字符串转换为对应 char 值。
 * 例如，stringToChar("hello") 返回 char 'h'。
 * @throw 如果给定字符串不恰好包含 1 个字符，则抛出 ErrorException
 */
char stringToChar(const std::string& str);

/**
 * 将表示实数的字符串转换为对应的
 * 值。
 * 等价于 stringToReal。
 * @throw 如果字符串不是合法浮点数，则抛出 ErrorException
 *        或包含空白以外的多余字符
 */
double stringToDouble(const std::string& str);   // 别名

/**
 * 将数字字符串转换为整数。
 * 该函数接受可选的 radix（基数）；例如，
 * stringToInteger("234", 16) 假定字符串采用 16 进制，并
 * 返回 2*16*16 + 3*16 + 4 = 564。
 * @throw 如果字符串不是合法整数或包含以下内容，则抛出 ErrorException
 *        除空白外的多余字符
 */
int stringToInteger(const std::string& str, int radix = 10);

/**
 * 将数字字符串转换为 long。
 * 该函数接受可选的 radix（基数）；例如，
 * stringToLong("234", 16) 假定字符串采用 16 进制，并
 * 返回 2*16*16 + 3*16 + 4 = 564。
 * @throw 如果字符串不是合法 long 或包含以下内容，则抛出 ErrorException
 *        除空白外的多余字符
 */
long stringToLong(const std::string& str, int radix = 10);

/**
 * 将表示实数的字符串转换为对应的
 * 值。
 * 等价于 stringToDouble。
 * @throw 如果字符串不是合法浮点数或存在以下情况，则抛出 ErrorException
 * 包含空白以外的多余字符
 */
double stringToReal(const std::string& str);

/**
 * 返回一个新字符，其中给定大写字符已被
 * 转换为对应的小写形式。
 */
char toLowerCase(char ch);

/**
 * 返回一个新字符串，其中所有大写字符均已转换
 * 转换为对应的小写形式。
 */
std::string toLowerCase(const std::string& str);

/**
 * 就地修改给定字符串，使所有大写字符都已
 * 已转换为对应的小写形式。
 */
void toLowerCaseInPlace(std::string& str);

/**
 * 返回一个新字符，其中给定小写字符已被
 * 转换为对应的大写形式。
 */
char toUpperCase(char ch);

/**
 * 返回一个新字符串，其中所有小写字符均已转换
 * 转换为对应的大写形式。
 */
std::string toUpperCase(const std::string& str);

/**
 * 就地修改给定字符串，使所有小写字符都已
 * 已转换为对应的大写形式。
 */
void toUpperCaseInPlace(std::string& str);

/**
 * 移除所有空白字符后返回新字符串
 * 从参数开头和末尾。
 */
std::string trim(const std::string& str);

/**
 * 就地修改给定字符串，将其中所有空白字符
 * 移除参数开头和末尾的内容。
 */
void trimInPlace(std::string& str);

/**
 * 移除所有空白字符后返回新字符串
 * 从参数末尾。
 */
std::string trimEnd(const std::string& str);

/**
 * 就地修改给定字符串，移除其中所有空白字符
 * 从其末尾。
 */
void trimEndInPlace(std::string& str);

/**
 * 移除所有空白字符后返回新字符串
 * 从参数开头。
 */
std::string trimStart(const std::string& str);

/**
 * 就地修改给定字符串，移除尾部的所有空白字符
 * 从其开头。
 */
void trimStartInPlace(std::string& str);

/**
 * 返回给定字符串的 URL 解码版本，其中任何 %xx 字符
 * 编码会被转换回对应字符。
 */
std::string urlDecode(const std::string& str);

/**
 * 就地修改给定字符串，将其转换为 URL 解码版本，
 * 其中任何 %xx 字符码都会转换回对应字符。
 */
void urlDecodeInPlace(std::string& str);

/**
 * 返回给定字符串的 URL 编码版本，其中大多数非
 * 字母字符会被替换为 %xx 字符代码。
 */
std::string urlEncode(const std::string& str);

/**
 * 就地修改给定字符串，将其转换为 URL 编码版本，
 * 其中大多数非字母字符会替换为 %xx 字符码。
 */
void urlEncodeInPlace(std::string& str);

// 为 C++ 标准中缺失的一些常见类型添加 to_string 重载
namespace std {
/**
 * 字符串到 bool 的转换函数。
 * 若 str 为 "true"，返回 bool 值 true。
 * 若 str 为 "false"，返回 bool 值 false。
 * @throw 如果 str 不是 "true" 或 "false"，则抛出 ErrorException
 */
bool stob(const std::string& str);

/**
 * 字符串到 char 的转换函数。
 * 将单字符字符串转换为对应 char 值。
 * 例如，stringToChar("hello") 返回 char 'h'。
 * @throw 如果给定字符串不恰好包含 1 个字符，则抛出 ErrorException
 */
char stoc(const std::string& str);

/**
 * 如果 b 为 true，则返回字符串“true”；否则返回“false”。
 */
std::string to_string(bool b);

/**
 * 返回包含给定字符的单字符字符串。
 * 例如，charToString('Q') 返回字符串 "Q"。
 */
std::string to_string(char c);

/**
 * 返回给定指针的十六进制字符串，例如“0x3f0427b”。
 * 如果 p 是空指针，则返回“nullptr”。
 */
std::string to_string(void* p);

/**
 * 适用于任何具有 operator << 的类型的通用 to_string 函数。
 */
template <typename T>
std::string to_string(const T& value) {
    std::ostringstream out;
    out << value;   // 如果这里出现错误，你的类型可能没有定义 << 运算符
    return out.str();
}
} // namespace std

#endif // _strlib_h
