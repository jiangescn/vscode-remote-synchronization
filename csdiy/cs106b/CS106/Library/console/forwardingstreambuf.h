/*
 * 文件：forwardingstreambuf.h
 * ---------------------------
 * 此文件定义 <code>ForwardingStreambuf</code> 类，该类
 * 表示一个仅包装另一个流缓冲区的流缓冲区。
 * 这主要用于将 cout 和 cerr 合并到同一个输出目标。
 *
 * @version 2016/10/04
 * - 初始版本
 */

#ifndef _forwardingstreambuf_h
#define _forwardingstreambuf_h

#include <ios>
#include <iostream>
#include <locale>
#include <streambuf>

#include "consolestreambuf.h"

namespace stanfordcpplib {
/*
 * 仅“包装”另一个流缓冲区的流缓冲区。
 * 这里用它来区分 cout（黑色文本）与 cerr（红色文本）。
 */
class ForwardingStreambuf : public std::streambuf {
private:
    ConsoleStreambuf& delegate;
    bool isStderr;

public:
    ForwardingStreambuf(ConsoleStreambuf& del, bool err = false)
            : delegate(del), isStderr(err) {
        // 空
    }

    virtual bool isBlocked() {
        return delegate.isBlocked();
    }

    virtual int overflow(int ch = EOF) {
        return delegate.overflow(ch, isStderr);
    }

    virtual int overflow(int ch, bool isStderr) {
        return delegate.overflow(ch, isStderr);
    }

    virtual int sync() {
        return delegate.sync(isStderr);
    }

    virtual int sync(bool isStderr) {
        return delegate.sync(isStderr);
    }

    virtual int underflow() {
        return delegate.underflow();
    }

    // 为完整性而重写以下函数，
    // 但都只是委托给底层 ConsoleStreambuf
    virtual std::streamsize in_avail() {
        return delegate.in_avail();
    }

    virtual int snextc() {
        return delegate.snextc();
    }

    virtual int sbumpc() {
        return delegate.sbumpc();
    }

    virtual int sgetc() {
        return delegate.sgetc();
    }

    virtual std::streamsize sgetn(char* s, std::streamsize n) {
        return delegate.sgetn(s, n);
    }

    virtual int sputbackc(char c) {
        return delegate.sputbackc(c);
    }

    virtual int sungetc() {
        return delegate.sungetc();
    }

    virtual int sputc(char c) {
        return delegate.sputc(c);
    }

    virtual std::streamsize sputn(const char* s, std::streamsize n) {
        return delegate.sputn(s, n);
    }

    virtual std::locale pubimbue(const std::locale& loc) {
        return delegate.pubimbue(loc);
    }

    virtual std::locale getloc() const {
        return delegate.getloc();
    }

    virtual std::streambuf* pubsetbuf(char* s, std::streamsize n) {
        return delegate.pubsetbuf(s, n);
    }

    virtual std::streampos pubseekoff(std::streamoff off, std::ios_base::seekdir way,
                          std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) {
        return delegate.pubseekoff(off, way, which);
    }

    virtual std::streampos pubseekpos(std::streampos pos, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) {
        return delegate.pubseekpos(pos, which);
    }

    virtual int pubsync() {
        return delegate.pubsync();
    }
};
} // namespace stanfordcpplib

#endif // _forwardingstreambuf_h
