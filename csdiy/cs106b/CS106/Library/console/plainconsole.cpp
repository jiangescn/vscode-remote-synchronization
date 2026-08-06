/*
 * 文件：plainconsole.cpp
 * ----------------------
 * 此文件定义用于为
 * C++ 纯文本控制台流：cin/cout/cerr。
 * 每个函数的文档见 plainconsole.h。
 *
 * @author Marty Stepp
 * @version 2017/11/12
 * - 将受限流改为抛出错误而不是触发 SIGABRT，以便更好地显示
 * @version 2017/10/20
 * - 修复关于 0 与 nullptr 的编译器警告
 * @version 2015/10/21
 * @since 2015/10/21
 */

#include "plainconsole.h"
#include <csignal>
#include <iostream>
#include <string>
#include "error.h"

namespace plainconsole {
/*
 * 仅将所有内容转发给委托对象的流缓冲区，
 * 但会回显从中读取的任何用户输入。
 * 用于在从文件重定向输入时（有时）回显控制台输入。
 * http://www.cplusplus.com/reference/streambuf/streambuf/
 */
class EchoingStreambuf : public std::streambuf {
private:
    /* 常量 */
    static const int BUFFER_SIZE = 4096;

    /* 实例变量 */
    char inBuffer[BUFFER_SIZE];
    char outBuffer[BUFFER_SIZE];
    std::istream instream;
    std::ostream& outstream;
    int outputLimit;
    int outputPrinted;

public:
    EchoingStreambuf(std::streambuf& buf, std::ostream& out)
            : instream(&buf),
              outstream(out),
              outputLimit(0),
              outputPrinted(0) {
        // outstream.rdbuf(&buf);
        setg(inBuffer, inBuffer, inBuffer);
        setp(outBuffer, outBuffer + BUFFER_SIZE);
    }

    ~EchoingStreambuf() {
        /* 空 */
    }
    
    virtual void setOutputLimit(int limit) {
        outputLimit = limit;
    }

    virtual int underflow() {
        // “return 0”处理来自 stdin 重定向的输入结束情况
        std::string line;
        if (!getline(instream, line)) {
            return 0;
        }
        
        int n = line.length();
        if (n + 1 >= BUFFER_SIZE) {
            error("EchoingStreambuf::underflow: String too long");
        }
        for (int i = 0; i < n; i++) {
            inBuffer[i] = line[i];
        }
        inBuffer[n++] = '\n';
        inBuffer[n] = '\0';
        setg(inBuffer, inBuffer, inBuffer + n);
        
        // 这里用于回显输入
        // fprintf(stdout, "inBuffer: \"%s\"\n", inBuffer);
        // fflush(stdout);
        outstream << inBuffer;
        outstream.flush();
        
        return inBuffer[0];
    }

    virtual int overflow(int ch = EOF) {
        std::string line = "";
        for (char *cp = pbase(); cp < pptr(); cp++) {
            if (*cp == '\n') {
                // puts(line.c_str());
                outputPrinted += line.length();
                if (outputLimit > 0 && outputPrinted > outputLimit) {
                    error("excessive output printed");
                }
                line = "";
            } else {
                line += *cp;
            }
        }
        if (line != "") {
            // puts(line.c_str());
            outputPrinted += line.length();
            if (outputLimit > 0 && outputPrinted > outputLimit) {
                error("excessive output printed");
            }
        }
        setp(outBuffer, outBuffer + BUFFER_SIZE);
        if (ch != EOF) {
            outBuffer[0] = ch;
            pbump(1);
        }
        return ch != EOF;
    }
    
    virtual int sync() {
        return overflow();
    }
};

/*
 * 限制可打印字符数量的流缓冲区。
 * 如果超过该数量，将抛出 ErrorException。
 */
class LimitedStreambuf : public std::streambuf {
private:
    std::ostream outstream;
    int outputLimit;
    int outputPrinted;

public:
    LimitedStreambuf(std::streambuf& buf, int limit)
            : outstream(&buf),
              outputLimit(limit),
              outputPrinted(0) {
        setp(nullptr, nullptr);   // // 不进行缓冲，每个字符都触发 overflow
    }

    virtual void setOutputLimit(int limit) {
        outputLimit = limit;
    }

    virtual int overflow(int ch = EOF) {
        outputPrinted++;
        if (outputLimit > 0 && outputPrinted > outputLimit) {
            // error("打印了过多输出");
            // outstream.setstate(std::ios::failbit | std::ios::badbit | std::ios::eofbit);
            // 终止程序
            // （使用信号而不是错误/异常
            // 这样学生就不会尝试捕获它）
            // error("打印了过多输出；代码中可能存在无限循环。");
            raise(SIGUSR1);
        } else {
            outstream.put(ch);
        }
        return ch;
    }
};

void setOutputLimit(int limit) {
    if (limit <= 0) {
        error("Platform::setConsoleOutputLimit: limit must be a positive integer");
    }
    LimitedStreambuf* limitedbufOut = new LimitedStreambuf(*std::cout.rdbuf(), limit);
    LimitedStreambuf* limitedbufErr = new LimitedStreambuf(*std::cerr.rdbuf(), limit);
    std::cout.rdbuf(limitedbufOut);
    std::cerr.rdbuf(limitedbufErr);
}

void setEcho(bool value) {
    static EchoingStreambuf* echobufIn = nullptr;
    static std::streambuf* oldBuf = nullptr;
    
    if (!echobufIn && value) {
        // 开始回显从 cin 获取的用户输入
        oldBuf = std::cin.rdbuf();
        echobufIn = new EchoingStreambuf(*std::cin.rdbuf(), std::cout);
        std::cin.rdbuf(echobufIn);
    } else if (echobufIn && !value) {
        // 停止回显
        std::cin.rdbuf(oldBuf);
        oldBuf = nullptr;
        echobufIn = nullptr;
    }
}

} // 命名空间 plainconsole
