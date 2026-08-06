/*
 * 文件：echoinputstreambuf.h
 * --------------------------
 * 此文件定义 <code>EchoInputStreambuf</code> 类，该类
 * 表示一个将所有用户输入回显到 stdout 的流缓冲区。
 * 这主要用于从文件重定向输入时显示控制台输入。
 *
 * @version 2016/10/30
 * - 添加接受输入字符串的构造函数
 * @version 2016/10/04
 * - 初始版本
 */

#ifndef _echoinputstreambuf_h
#define _echoinputstreambuf_h

#include <iostream>
#include <sstream>
#include <streambuf>

namespace stanfordcpplib {

/*
 * 读取字符时将其回显的输入流缓冲区。
 * 用于回显 cin 控制台输入，以便捕获后比较测试用例差异
 * 自动评分器向 cin 提供固定输入时。
 *
 * 灵感来源：http://gabisoft.free.fr/articles/fltrsbf1.html
 */
class EchoInputStreambuf : public std::streambuf {
public:
    EchoInputStreambuf(std::streambuf* source) : m_source(source), m_buffer('\0') {
        // 空
    }

    EchoInputStreambuf(const std::string& input) : m_buffer('\0') {
        std::istringstream* istream = new std::istringstream(input);
        m_source = istream->rdbuf();
    }

    virtual ~EchoInputStreambuf() {
        sync();
    }

    virtual int overflow(int) {
        return EOF;
    }

    /*
     * 这是关键函数；读取
     * 底层流缓冲区（cin）。我们将其捕获到单字符 m_buffer 中
     * 以便稍后返回它。
     */
    virtual int underflow() {
        int result(EOF);
        if (gptr() < egptr()) {
            result = *gptr();
        } else {
            result = m_source->sbumpc();
            if (result != EOF) {
                m_buffer = result;
                setg(&m_buffer, &m_buffer, &m_buffer + 1);

                // 将字符回显到 stdout
                std::cout.put(result);
                std::cout.flush();
            }
        }
        return result;
    }

    virtual int sync() {
        int result(0);
        if (gptr() < egptr()) {
            result = m_source->sputbackc(*gptr());
            setg(nullptr, nullptr, nullptr);
        }
        if (m_source->pubsync() == EOF) {
            result = EOF;
        }
        return result;
    }

    virtual std::streambuf* setbuf(char* p, std::streamsize len) {
        return m_source->pubsetbuf(p, len);
    }

private:
    std::streambuf* m_source;
    char m_buffer;
};

} // namespace stanfordcpplib

#endif // _echoinputstreambuf_h
