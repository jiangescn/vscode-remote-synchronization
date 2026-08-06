/*
 * 文件：ioutils.cpp
 * ---------------
 * 此文件包含用于帮助捕获、重定向
 * 并向 cin/cout/err 提供输入。
 * 每个函数的文档见 ioutils.h。
 * 
 * @author Marty Stepp
 * @version 2016/10/28
 * - 修复输出限制静态变量的错误
 * @version 2016/10/22
 * - 移除所有静态变量（改用 STATIC_VARIABLE 宏）
 * @version 2014/10/14
 * @since 2014/03/01
 */

#include "ioutils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "consoletext.h"
#include "error.h"
#include "echoinputstreambuf.h"
#include "limitoutputstreambuf.h"
#include "private/static.h"

namespace ioutils {
STATIC_VARIABLE_DECLARE_BLANK(std::stringstream, bufferOut)
STATIC_VARIABLE_DECLARE(std::streambuf*, oldOut, nullptr)
STATIC_VARIABLE_DECLARE_BLANK(std::stringstream, bufferErr)
STATIC_VARIABLE_DECLARE(std::streambuf*, oldErr, nullptr)
STATIC_VARIABLE_DECLARE_BLANK(std::stringstream, bufferIn)
STATIC_VARIABLE_DECLARE(std::streambuf*, oldIn, nullptr)
STATIC_VARIABLE_DECLARE(bool, consoleEchoUserInput, false)
STATIC_VARIABLE_DECLARE(int, consoleOutputLimit, 0)



void captureStderrBegin() {
    STATIC_VARIABLE(bufferErr).str(std::string());
    std::streambuf* newBuf;
    int limit = getConsoleOutputLimit();
    if (limit > 0) {
        newBuf = new stanfordcpplib::LimitOutputStreambuf(STATIC_VARIABLE(bufferErr).rdbuf(), limit);
    } else {
        newBuf = STATIC_VARIABLE(bufferErr).rdbuf();
    }
    STATIC_VARIABLE(oldErr) = std::cerr.rdbuf(newBuf);
}

std::string captureStderrEnd() {
    std::cerr.flush();
    if (STATIC_VARIABLE(oldErr)) {
        std::cerr.rdbuf(STATIC_VARIABLE(oldErr));
        STATIC_VARIABLE(oldErr) = nullptr;
    }
    return STATIC_VARIABLE(bufferErr).str();
}

void captureStdoutBegin(bool alsoStderr) {
    STATIC_VARIABLE(bufferOut).str(std::string());
    std::streambuf* newBuf;
    int limit = getConsoleOutputLimit();
    if (limit > 0) {
        newBuf = new stanfordcpplib::LimitOutputStreambuf(STATIC_VARIABLE(bufferOut).rdbuf(), limit);
    } else {
        newBuf = STATIC_VARIABLE(bufferOut).rdbuf();
    }
    
    STATIC_VARIABLE(oldOut) = std::cout.rdbuf(newBuf);
    if (alsoStderr) {
        STATIC_VARIABLE(bufferErr).str(std::string());
        STATIC_VARIABLE(oldErr) = std::cerr.rdbuf(newBuf);
    }
}

std::string captureStdoutEnd() {
    std::cout.flush();
    if (STATIC_VARIABLE(oldOut)) {
        std::cout.rdbuf(STATIC_VARIABLE(oldOut));
        STATIC_VARIABLE(oldOut) = nullptr;
    }
    std::cerr.flush();
    if (STATIC_VARIABLE(oldErr)) {
        std::cerr.rdbuf(STATIC_VARIABLE(oldErr));
        STATIC_VARIABLE(oldErr) = nullptr;
    }
    return STATIC_VARIABLE(bufferOut).str();
}

bool getConsoleEchoUserInput() {
    return STATIC_VARIABLE(consoleEchoUserInput);
}

int getConsoleOutputLimit() {
    return STATIC_VARIABLE(consoleOutputLimit);
}
        
void redirectStdinBegin(std::string userInput) {
    STATIC_VARIABLE(bufferIn).str(std::string());
    std::streambuf* newBuf;
    if (getConsoleEchoUserInput()) {
        newBuf = new stanfordcpplib::EchoInputStreambuf(STATIC_VARIABLE(bufferIn).rdbuf());
    } else {
        newBuf = STATIC_VARIABLE(bufferIn).rdbuf();
    }
    STATIC_VARIABLE(oldIn) = std::cin.rdbuf(newBuf);
    redirectStdinFeedInput(userInput);
}

void redirectStdinFeedInput(std::string userInput) {
    if (!userInput.empty()) {
        STATIC_VARIABLE(bufferIn) << userInput << std::endl;
    }
}

void redirectStdinEnd() {
    if (STATIC_VARIABLE(oldIn)) {
        std::cin.rdbuf(STATIC_VARIABLE(oldIn));
        STATIC_VARIABLE(oldIn) = nullptr;
    }
}

void setConsoleEchoUserInput(bool echo) {
    STATIC_VARIABLE(consoleEchoUserInput) = echo;
}

void setConsoleOutputLimit(int limit) {
    STATIC_VARIABLE(consoleOutputLimit) = limit;
}
} // 命名空间 ioutils
