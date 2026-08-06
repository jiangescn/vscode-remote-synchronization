/*
 * 文件：exceptions.h
 * ------------------
 * 此文件包含顶层异常处理程序，用于打印抛出的异常
 * 由学生代码输出到控制台。
 * 它还包含一些技巧，尝试在以下情况下获取堆栈跟踪
 * 会抛出异常，不过很难在所有平台上一致地做到这一点。
 *
 * @author Marty Stepp
 * @version 2018/09/25
 * - 为 setTopLevelExceptionHandlerEnabled 添加“force”参数
 *   （有助于在线程环境下更好地工作）
 * - 添加用于生成新文档的文档注释
 * @version 2016/11/07
 * - 添加 cleanupFunctionNameForStackTrace
 * @version 2016/10/30
 * - 将递归函数移到 recursion.h/cpp
 * @version 2014/11/12
 * - 公开提供 printStackTrace 函数
 * - 添加顶层信号处理程序（用于空指针解引用等）
 * @since 2014/11/05
 */


#ifndef _exceptions_h
#define _exceptions_h

#include <string>

namespace exceptions {

/**
 * 由 C++ 库的 main 包装器调用，使堆栈跟踪知道程序名称。
 * （取自 argv[0]。）
 */
std::string& getProgramName();

/**
 * 返回顶层异常处理程序是否已启用。
 */
bool getTopLevelExceptionHandlerEnabled();

/**
 * 由 C++ 库的 main 包装器调用，使堆栈跟踪知道程序名称。
 * （取自 argv[0]。）
 */
void setProgramName(char* programName);

/**
 * 设置顶层异常处理程序是否启用。
 */
void setTopLevelExceptionHandlerEnabled(bool enabled);

/**
 * 如果在调试器下运行，将中断程序并把控制权交还给调试器（就像你
 * 按下“中断”按钮）。如果未在调试器下运行，则不执行任何操作。
 */
void interruptIfDebug();

}

#endif // _exceptions_h
