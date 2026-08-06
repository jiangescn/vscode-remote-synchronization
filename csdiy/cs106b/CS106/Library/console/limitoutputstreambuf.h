/*
 * 文件：limitoutputstreambuf.h
 * ----------------------------
 * 此文件定义 <code>LimitOutputStreambuf</code> 类，该类
 * 表示一个统计已产生输出量的流缓冲区
 * 如果超过给定最大值，则抛出异常。
 * 这主要用于评分程序中，以停止失控的学生代码。
 *
 * @version 2016/10/04
 * - 初始版本
 */


#ifndef _limitoutputstreambuf_h
#define _limitoutputstreambuf_h

#include <exception>
#include <iostream>
#include <streambuf>

namespace stanfordcpplib {

/*
 * 统计写入字符数量的输出流缓冲区。
 * 供自动评分器用于限制那些会
 * 打印过多输出。
 *
 * 灵感来源：http://gabisoft.free.fr/articles/fltrsbf1.html
 */
class LimitOutputStreambuf : public std::streambuf {
public:
    LimitOutputStreambuf(std::streambuf* source, int max) : m_source(source), m_count(0), m_max(max) {
        // 空
    }

    virtual ~LimitOutputStreambuf() {
        sync();
    }

    /*
     * 这是关键函数；向
     * 底层流缓冲区（cout）。我们对它们计数，以便可以抛出
     * 如果打印过多，则产生错误。
     */
    virtual int overflow(int ch) {
        if (m_count >= 0) {
            m_count++;
            if (m_count > m_max) {
                m_count = -1;   // 禁用后续调用检查，以便我可以再次打印
                std::ostringstream os;
                os << std::endl;
                os << "*** ERROR: Excessive output produced! (over " << m_max << " chars)" << std::endl;
                os << "***        Halting program." << std::endl;
                std::string str = os.str();
                m_source->sputn(str.c_str(), (int) str.length());
                throw std::exception();
            }
        }

        return m_source->sputc(ch);
    }

    virtual int underflow() {
        return EOF;
    }

    virtual int sync() {
        return m_source->pubsync();
    }

    virtual std::streambuf* setbuf(char* p, std::streamsize len) {
        return m_source->pubsetbuf(p, len);
    }

private:
    std::streambuf* m_source;
    int m_count;
    int m_max;
};

} // namespace stanfordcpplib

#endif // _limitoutputstreambuf_h
