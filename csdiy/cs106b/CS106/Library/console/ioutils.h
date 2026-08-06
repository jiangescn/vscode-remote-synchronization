/*
 * 文件：ioutils.h
 * ---------------
 * 此文件包含用于帮助捕获、重定向
 * 并向 cin/cout/err 提供输入。
 * 
 * @author Marty Stepp
 * @version 2014/10/14
 * @since 2014/03/01
 */

#ifndef _ioutils_h
#define _ioutils_h

#include <string>

namespace ioutils {
void captureStderrBegin();
std::string captureStderrEnd();
void captureStdoutBegin(bool alsoStderr = false);
std::string captureStdoutEnd();

/*
 * 函数：getConsoleEchoUserInput
 * 用法：bool echo = getConsoleEchoUserInput();
 * ---------------------------------------------
 * 返回 Stanford 图形控制台的输入是否
 * 控制台窗口内容正在镜像到操作系统标准终端
 * 窗口。初始值为 false，除非之前调用以下方法将其设为 true：
 * setConsoleEchoUserInput(true)。
 */
bool getConsoleEchoUserInput();
int getConsoleOutputLimit();

void redirectStdinBegin(std::string userInput = "");
void redirectStdinFeedInput(std::string userInput);
void redirectStdinEnd();

/*
 * 函数：setConsoleEchoUserInput
 * 用法：setConsoleEchoUserInput(true);
 * -------------------------------------
 * 启用或禁用回显来自 Stanford 的输入
 * 将控制台窗口内容镜像到操作系统标准终端窗口。
 * 通常不需要这种回显，但如果你希望能够复制
 * 并将控制台交互粘贴到另一个窗口时，此功能很有用。
 */
void setConsoleEchoUserInput(bool echo);

/*
 * 设置控制台：如果总打印字符数超过 'limit'，则抛出错误。
 * 用于停止输出无限或近似无限内容的学生程序。
 * 如果 limit <= 0，则不设限制。
 */
void setConsoleOutputLimit(int limit = 0);
} // 命名空间 ioutils

#endif // _ioutils_h
