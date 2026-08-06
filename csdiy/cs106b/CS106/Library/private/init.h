/*
 * 文件：init.h
 * ------------
 * 这些函数用于设置/清理 Stanford C++ 库。
 *
 * 最初，必要设置通过静态初始化器启动。这要求
 * 通过精心安排 include 和保护宏，此方式已不再使用，因为前置/后置工作
 * 被插入到包围学生 main 的包装器 "main" 函数中。
 *
 * @version 2018/08/28
 * - 重构以使用 stanfordcpplib 命名空间和 init.cpp
 * @version 2018/07/03
 * - 添加处理 Qt GUI 库初始化的代码
 * @version 2017/04/25
 * - 用 #ifndef 包装库初始化器，以避免重复声明
 *
 */

#ifndef _init_h
#define _init_h

#include <string>

namespace stanfordcpplib {

/**
 * 如果 std::exit 函数已启用，则返回 true。
 * 除非被自动评分器等禁用，否则此值为 true。
 */
bool exitEnabled();

/**
 * 初始化 Stanford C++ 库。
 * 在学生的 main() 运行之前插入对此函数的调用。
 * 这应从 Qt GUI（主）线程运行。
 */
void initializeLibrary(int argc, char** argv);

/**
 * 用于在学生线程中执行所需的任何初始化
 * 而不是在 Qt GUI 主线程上。
 * 目前主要用于为以下对象设置异常处理程序：
 * 由学生线程捕获并报告错误。
 */
void initializeStudentThread();

/**
 * 设置是否启用 std::exit 函数。
 * 如果禁用，学生尝试调用 exit() 时将抛出 error()。
 */
void setExitEnabled(bool enabled);

/**
 * 关闭 Stanford C++ 库。
 * 在学生的 main() 之后插入对此函数的调用。
 */
void shutdownLibrary();



} // namespace stanfordcpplib

// 绕过 std::exit 函数
namespace std {
void __stanfordcpplib__exitLibrary(int status);
} // namespace std

#define STD_EXIT __std_exit_function_
#define exit __stanfordcpplib__exitLibrary

#ifdef SPL_HEADLESS_MODE
#include "headless.h"
#endif // SPL_HEADLESS_MODE

#endif // _init_h
