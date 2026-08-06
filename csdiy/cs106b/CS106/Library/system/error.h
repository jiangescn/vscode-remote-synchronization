/*
 * 文件：error.h
 * -------------
 * 此文件定义 <code>ErrorException</code> 类以及
 * <code>error</code> 函数。
 *
 * @version 2018/10/18
 * - 为包装其他错误类型的 ErrorException 添加 getKind
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 * @version 2017/11/29
 * - 修复 Windows 系统上未定义 SIGUSR1 的问题
 * @version 2016/11/29
 * - 将 error() 改为接受 const string& 而不是 string
 * @version 2016/11/23
 * - 添加用于输出 ErrorException 的 operator <<
 */


#ifndef _error_h
#define _error_h

#include <csignal>
#include <exception>
#include <iostream>
#include <string>

// 修复某些 Windows 系统上缺失信号的问题
#ifndef SIGUSR1
#define SIGUSR1 10
#endif // SIGUSR1

/**
 * 调用 <code>error</code> 时会抛出此异常
 * 函数。捕获错误的典型代码如下：
 *
 *<pre>
 *    try {
 *       ... 可能发生错误的代码 ...
 *    } catch (ErrorException& ex) {
 *       ... 处理错误情况的代码 ...
 *    }
 *</pre>
 *
 * 如果在执行过程中的任何位置抛出 <code>ErrorException</code>，
 * <code>try</code> 的范围内（包括由其调用的函数中
 * 该代码），控制将立即跳转到错误处理程序。
 */
class ErrorException : public std::exception {
public:
    /**
     * 使用给定错误消息创建新的 ErrorException。
     */
    ErrorException(std::string msg);

    /**
     * 释放异常分配的任何内存。
     */
    virtual ~ErrorException() noexcept = default;

    /**
     * 返回此异常的类型。
     * 通常这会返回 "error"，但在某些情况下我们会捕获其他类型
     * 其他异常（例如抛出的 int 或字符串），并将它们包装为
     * ErrorException。在这种情况下，kind 将为“int”或“string”等。
     */
    virtual std::string getKind() const;

    /**
     * 返回传给异常构造函数的错误消息。
     */
    virtual std::string getMessage() const;

    /**
     * 设置此异常的类型。
     * 默认为“error”。
     */
    void setKind(const std::string& kind);

    /**
     * 以 C 字符串返回异常的错误消息。
     */
    virtual const char* what() const noexcept;

private:
    std::string _kind;
    std::string _msg;
};

/**
 * 将错误异常打印到给定输出流。
 */
std::ostream& operator <<(std::ostream& out, const ErrorException& ex);

/**
 * 通过抛出一个异常来表示程序中的错误条件
 * 带有指定消息的 <code>ErrorException</code>。
 */
[[noreturn]] void error(const std::string& msg);

#endif // _error_h
