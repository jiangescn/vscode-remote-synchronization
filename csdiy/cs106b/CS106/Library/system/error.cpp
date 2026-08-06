/*
 * 文件：error.cpp
 * ---------------
 * error 函数的实现。
 *
 * @version 2016/11/23
 * - 添加用于输出 ErrorException 的 operator <<
 * @version 2014/10/08
 * - 移除“using namespace”语句
 */

#include "error.h"
#include "exceptions.h"
#include "strlib.h"
#include <sstream>

/* ErrorException 类的定义 */

ErrorException::ErrorException(std::string msg)
        : _kind("error") {
    _msg = msg;
}

std::string ErrorException::getKind() const {
    return _kind;
}

std::string ErrorException::getMessage() const {
    return _msg;
}

void ErrorException::setKind(const std::string& kind) {
    _kind = kind;
}

const char* ErrorException::what() const noexcept {
    // stepp：原来的 "Error: " 前缀在此处被注释掉，
    // 因为在许多错误情况下，尝试进行字符串拼接
    // 最终会破坏字符串并产生垃圾异常文本
    // return ("Error: " + msg).c_str();
    return _msg.c_str();
}

std::ostream& operator <<(std::ostream& out, const ErrorException& ex) {
    out << "ErrorException: " << ex.what();
    return out;
}

/*
 * 实现说明：error
 * ---------------------------
 * 早期的 error 实现至少在以下平台上允许
 * Macintosh，用于帮助调试器在以下位置生成回溯
 * 错误原因。遗憾的是，如果以下情况发生，这已无法做到
 * 错误可被捕获。
 */

/* [[noreturn]] */ void error(const std::string& msg) {
    throw ErrorException(msg);
}
