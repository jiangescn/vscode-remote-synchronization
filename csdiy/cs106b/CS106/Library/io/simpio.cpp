/*
 * 文件：simpio.cpp
 * ----------------
 * 此文件实现 simpio.h 接口。
 * 
 * @version 2016/09/29
 * - 添加 getDouble 方法
 * @version 2015/07/05
 * - 提高各类 I/O 使用的 appendSpace 函数的可见性
 *   提示函数（不再是静态函数）
 * @version 2014/10/19
 * - 按字母顺序排列函数
 * - 为提高效率，将许多函数的参数由 string 改为 const string&
 * @version 2014/10/08
 * - 移除“using namespace”语句
 */

#include "simpio.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "error.h"
#include "strlib.h"
#include "private/static.h"

STATIC_CONST_VARIABLE_DECLARE(std::string, GETCHAR_DEFAULT_PROMPT, "Enter a character: ")
STATIC_CONST_VARIABLE_DECLARE(std::string, GETCHAR_DEFAULT_REPROMPT, "You must type a single character. Try again.")
STATIC_CONST_VARIABLE_DECLARE(std::string, GETINTEGER_DEFAULT_PROMPT, "Enter an integer: ")
STATIC_CONST_VARIABLE_DECLARE(std::string, GETINTEGER_DEFAULT_REPROMPT, "Illegal integer format. Try again.")
STATIC_CONST_VARIABLE_DECLARE(std::string, GETREAL_DEFAULT_PROMPT, "Enter a number: ")
STATIC_CONST_VARIABLE_DECLARE(std::string, GETREAL_DEFAULT_REPROMPT, "Illegal numeric format. Try again.")
STATIC_CONST_VARIABLE_DECLARE(std::string, GETYESORNO_DEFAULT_PROMPT, "Try again: ")
STATIC_CONST_VARIABLE_DECLARE(std::string, GETYESORNO_DEFAULT_REPROMPT, "Please type a word that starts with 'Y' or 'N'.")

/*
 * 实现说明：getChar、getDouble、getInteger、getReal
 * -------------------------------------------------------------
 * 这些函数中的每一个都会读取完整输入行，然后使用
 * 使用 <sstream> 库将该行解析为所需类型的值。
 * 如果失败，实现会要求用户输入新值。
 */

char getChar(const std::string& prompt,
             const std::string& reprompt) {
    std::string promptCopy = prompt;
    appendSpace(promptCopy);
    char value = '\0';
    while (true) {
        std::cout << promptCopy;
        std::string line;
        if (!getline(std::cin, line)) {
            error("getChar: End of input reached while waiting for character value.");
        }
        if (line.length() == 1) {
            value = line[0];
            break;
        }

        std::cout.flush();
        std::cerr << (reprompt.empty() ? STATIC_VARIABLE(GETCHAR_DEFAULT_REPROMPT) : reprompt) << std::endl;
        std::cerr.flush();
        if (promptCopy.empty()) {
            promptCopy = STATIC_VARIABLE(GETCHAR_DEFAULT_PROMPT);
        }
    }
    return value;
}

double getDouble(const std::string& prompt,
                 const std::string& reprompt) {
    return getReal(prompt, reprompt);
}

double getDoubleBetween(const std::string& prompt, double min, double max) {
    return getRealBetween(prompt, min, max);
}

int getInteger(const std::string& prompt,
               const std::string& reprompt) {
    std::string promptCopy = prompt;
    appendSpace(promptCopy);
    int value = 0;
    while (true) {
        std::cout << promptCopy;
        std::string line;
        if (!getline(std::cin, line)) {
            error("getInteger: End of input reached while waiting for integer value.");
        }
        trimInPlace(line);
        std::istringstream stream(line);
        stream >> value;
        if (!stream.fail() && stream.eof()) {
            break;
        }
        std::cout.flush();
        std::cerr << (reprompt.empty() ? STATIC_VARIABLE(GETINTEGER_DEFAULT_REPROMPT) : reprompt) << std::endl;
        std::cerr.flush();
        if (promptCopy.empty()) {
            promptCopy = STATIC_VARIABLE(GETINTEGER_DEFAULT_PROMPT);
        }
    }
    return value;
}

int getIntegerBetween(const std::string& prompt, int min, int max) {
    int value = 0;
    while (true) {
        value = getInteger(prompt);
        if (value < min || value > max) {
            std::cout.flush();
            std::cerr << "Please type a value between " << min
                      << " and " << max << "." << std::endl;
            std::cerr.flush();
        } else {
            break;
        }
    }
    return value;
}

/*
 * 实现说明：getLine
 * -----------------------------
 * getLine 函数只是将显示
 * 提示并读取一行输入合并为一次调用。主要
 * 在库中包含此函数的原因是确保
 * 使读取整数、浮点数和
 * 使字符串尽可能保持一致。
 */
std::string getLine(const std::string& prompt) {
    std::string line;
    getLine(prompt, line);
    return line;
}

void getLine(const std::string& prompt,
             std::string& out) {
    std::string promptCopy = prompt;
    appendSpace(promptCopy);
    std::cout << promptCopy;
    if (!getline(std::cin, out)) {
        error("getLine: End of input reached while waiting for line.");
    }
}

void getLine(std::istream& input,
             std::string& out) {
    if (!getline(input, out)) {
        error("getLine: End of input reached while waiting for line.");
    }
}

double getReal(const std::string& prompt,
               const std::string& reprompt) {
    std::string promptCopy = prompt;
    appendSpace(promptCopy);
    double value = 0.0;
    while (true) {
        std::cout << promptCopy;
        std::string line;
        if (!getline(std::cin, line)) {
            error("getReal: End of input reached while waiting for real value.");
        }
        trimInPlace(line);
        std::istringstream stream(line);
        stream >> value;
        if (!stream.fail() && stream.eof()) {
            break;
        }
        std::cout.flush();
        std::cerr << (reprompt.empty() ? STATIC_VARIABLE(GETREAL_DEFAULT_REPROMPT) : reprompt) << std::endl;
        std::cerr.flush();
        if (promptCopy.empty()) {
            promptCopy = STATIC_VARIABLE(GETREAL_DEFAULT_PROMPT);
        }
    }
    return value;
}

double getRealBetween(const std::string& prompt, double min, double max) {
    double value = 0;
    while (true) {
        value = getReal(prompt);
        if (value < min || value > max) {
            std::cout.flush();
            std::cerr << "Please type a value between " << min
                      << " and " << max << "." << std::endl;
            std::cerr.flush();
        } else {
            break;
        }
    }
    return value;
}

bool getYesOrNo(const std::string& prompt,
                const std::string& reprompt,
                const std::string& defaultValue) {
    std::string promptCopy = prompt;
    appendSpace(promptCopy);
    bool value = false;
    while (true) {
        std::cout << promptCopy;
        std::string line;
        if (!getline(std::cin, line)) {
            error("getYesOrNo: End of input reached while waiting for yes/no value.");
        }
        if (line.empty()) {
            line = defaultValue;
        }
        if ((int) line.length() > 0) {
            char first = tolower(line[0]);
            if (first == 'y') {
                value = true;
                break;
            } else if (first == 'n') {
                value = false;
                break;
            }
        }
        std::cout.flush();
        std::cerr << (reprompt.empty() ? STATIC_VARIABLE(GETYESORNO_DEFAULT_REPROMPT) : reprompt) << std::endl;
        std::cerr.flush();
        if (promptCopy.empty()) {
            promptCopy = STATIC_VARIABLE(GETYESORNO_DEFAULT_PROMPT);
        }
    }
    return value;
}

void appendSpace(std::string& prompt) {
    if (!prompt.empty() && !isspace(prompt[prompt.length() - 1])) {
        prompt += ' ';
    }
}
