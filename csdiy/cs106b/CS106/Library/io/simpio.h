/*
 * 文件：simpio.h
 * --------------
 * 此文件导出一组简化输入/输出的函数
 * C++ 中的操作，并对控制台输入提供一些错误检查。
 *
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 * @version 2016/09/29
 * - 添加 getDouble 方法
 * @version 2015/07/05
 * - 提高各类 I/O 使用的 appendSpace 函数的可见性
 *   提示函数（不再是静态函数）
 * @version 2014/10/19
 * - 按字母顺序排列函数
 * - 为提高效率，将许多函数的参数由 string 改为 const string&
 */


#ifndef _simpio_h
#define _simpio_h

#include <iostream>
#include <string>

/**
 * 如果给定字符串末尾没有空格，则通过引用在末尾添加一个空格。
 * @private
 */
void appendSpace(std::string& prompt);

/**
 * 从 <code>cin</code> 读取完整一行，期望用户输入一个
 * 单个字符。如果是这种情况，则返回该字符值。
 * 如果用户输入的不是仅含一个字符的一行，
 * 让用户有机会重新输入该值。
 *
 * 若提供，可选的 <code>prompt</code> 字符串会在以下内容之前输出：
 * 读取该值。
 * 如果未传入提示文本，默认为“必须输入单个字符。请重试。”。
 *
 * 可选的 <code>reprompt</code> 参数用于提供输出消息
 * 用户输入无效时显示。如果没有重新提示文本
 * 如果传入，默认值为 prompt。
 */
char getChar(const std::string& prompt = "",
             const std::string& reprompt = "");

/**
 * 从 <code>cin</code> 读取完整一行，并将其扫描为
 * 浮点数。若扫描成功，则该浮点
 * 会返回该值。若输入不是合法数字，或
 * 字符串中出现多余字符（空白除外），
 * 让用户有机会重新输入该值。
 *
 * 若提供，可选的 <code>prompt</code> 字符串会在以下内容之前输出：
 * 读取该值。
 *
 * 可选的 <code>reprompt</code> 参数用于提供输出消息
 * 在用户输入无效内容时显示。
 * 如果未传入提示文本，默认为“数字格式非法。请重试。”。
 *
 * 等价于 getReal。
 */
double getDouble(const std::string& prompt = "",
                 const std::string& reprompt = "");

/**
 * 从 <code>cin</code> 读取完整一行，并将其扫描为
 * 浮点数。若扫描成功，则该浮点
 * 会返回该值。若输入不是合法数字，或
 * 它不在 min 和 max 之间，或出现多余字符
 * 字符串中出现除空白以外的内容，
 * 让用户有机会重新输入该值。
 *
 * 读取值前会输出必需的 <code>prompt</code> 字符串。
 *
 * 等价于 getRealBetween。
 */
double getDoubleBetween(const std::string& prompt, double min, double max);


/**
 * 从 <code>cin</code> 读取完整的一行，并将其解析为
 * 整数。若扫描成功，则返回整数值。若
 * 参数不是合法整数，或包含多余字符
 * 如果字符串中出现（空白以外的）其他内容，则会要求用户
 * 重新输入该值的机会。
 *
 * 若提供，可选的 <code>prompt</code> 字符串会在以下内容之前输出：
 * 读取该值。
 *
 * 可选的 <code>reprompt</code> 参数用于提供输出消息
 * 在用户输入无效内容时显示。
 * 如果未传入值，默认为“整数格式非法。请重试。”。
 */
int getInteger(const std::string& prompt = "",
               const std::string& reprompt = "");

/**
 * 从 <code>cin</code> 读取完整的一行，并将其解析为
 * 整数。若扫描成功，则返回整数值。若
 * 参数不是合法整数、不在 min 和 max 之间，
 * 或字符串中出现空白以外的多余字符时，
 * 让用户有机会重新输入该值。
 *
 * 读取值前会输出必需的 <code>prompt</code> 字符串。
 */
int getIntegerBetween(const std::string& prompt, int min, int max);

/**
 * 从 <code>cin</code> 读取一行文本并返回该行
 * 作为字符串。终止输入的换行符会被
 * 不作为返回值的一部分存储。如果提供，可选的
 * 在读取值之前打印 <code>prompt</code> 字符串。
 */
std::string getLine(const std::string& prompt = "");

/**
 * getLine 的替代版本，接受提示并填充给定输出
 * 变量，并存入其结果。
 */
void getLine(const std::string& prompt,
             std::string& out);

/**
 * getLine 的替代版本，接受要读取的输入流。
 * 旨在直接替代标准 C++ getline（小写 L）
 * 函数。
 */
void getLine(std::istream& input,
             std::string& out);

/**
 * 从 <code>cin</code> 读取完整一行，并将其扫描为
 * 浮点数。若扫描成功，则该浮点
 * 会返回该值。若输入不是合法数字，或
 * 字符串中出现多余字符（空白除外），
 * 让用户有机会重新输入该值。
 *
 * 若提供，可选的 <code>prompt</code> 字符串会在以下内容之前输出：
 * 读取该值。
 *
 * 可选的 <code>reprompt</code> 参数用于提供输出消息
 * 在用户输入无效内容时显示。
 * 如果未传入值，默认为“数字格式非法。请重试。”。
 *
 * 等价于 getDouble。
 */
double getReal(const std::string& prompt = "",
               const std::string& reprompt = "");

/**
 * 从 <code>cin</code> 读取完整一行，并将其扫描为
 * 浮点数。若扫描成功，则该浮点
 * 会返回该值。若输入不是合法数字，或
 * 它不在 min 和 max 之间，或出现多余字符
 * 字符串中出现除空白以外的内容，
 * 让用户有机会重新输入该值。
 *
 * 读取值前会输出必需的 <code>prompt</code> 字符串。
 *
 * 等价于 getDoubleBetween。
 */
double getRealBetween(const std::string& prompt, double min, double max);

/**
 * 从 <code>cin</code> 读取完整一行，并将其视为
 * 对问题的是/否回答。如果该行
 * 输入内容以 'y' 或 'Y' 开头时返回 true；如果以
 * 以 'n' 或 'N' 开头。否则，用户有机会重新输入
 * 值。
 *
 * 若提供，可选的 <code>prompt</code> 字符串会在以下内容之前输出：
 * 读取该值。
 *
 * 可选的 <code>reprompt</code> 参数用于提供输出消息
 * 在用户输入无效内容时显示。
 * 如果未传入值，则默认为
 * “请输入以‘Y’或‘N’开头的单词。”。
 *
 * 同样可选的 <code>defaultValue</code> 参数表示
 * 如果用户直接按 Enter 而不是输入 Y 或 N，应发生的情况。
 * 默认情况下会再次提示用户；但如果此处传入 defaultValue，
 * 按 Enter 等同于输入该值。
 * 当默认 Y/N 答案为 Yes 或 No，而你希望
 * 让用户免于输入。
 */
bool getYesOrNo(const std::string& prompt = "",
                const std::string& reprompt = "",
                const std::string& defaultValue = "");

#endif // _simpio_h
