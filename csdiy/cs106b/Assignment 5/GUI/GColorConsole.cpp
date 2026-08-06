#include "GColorConsole.h"
#include "gthread.h"
#include "strlib.h"
using namespace std;

namespace {
    /* HTML 页眉和页脚。*/
    const string kHTMLHeader = R"(
         <html>
            <head></head>
            <body style="background-color:white;color:black;">
                <pre>)";

    const string kHTMLFooter = R"(</pre>
            </body>
        </html>
    )";
}

GColorConsole::GColorConsole() : ostream(new ConsoleStreambuf(this)) {
    // 已在初始化列表中处理
}

GColorConsole::~GColorConsole() {
    delete rdbuf();
}

/* 清除所有内容。调用 updateDisplay 之前不会更新显示。 */
void GColorConsole::clearDisplay() {
    /* 输出所有剩余内容，然后清空内容。 */
    flushBuffer();
    mContents.clear();
}

/* 每当 streambuf 同步时，取出缓冲区内容并将其推送
 * 加入内容列表。
 */
int GColorConsole::ConsoleStreambuf::sync() {
    mOwner->updateDisplay();
    return 0;
}

/* 输出 streambuf 中保存的所有文本，并将其添加到文本项列表
 * 用于显示。
 */
void GColorConsole::flushBuffer() {
    /* 获取缓冲区当前内容。若为空，则无需
     * 任何内容。
     */
    auto* buffer = static_cast<ConsoleStreambuf *>(rdbuf());

    auto contents = buffer->str();
    if (contents.empty()) return;

    /* 否则，清空缓冲区并追加此文本。 */
    buffer->str("");
    mContents.emplace_back(mStyle, contents);
}

/* 同步到显示区域。
 *
 * TODO：构造显示字符串需要 O(n) 时间。我认为这不太可能
 * 不会成为严重问题，因为复制字符本来就需要执行 O(n) 工作
 * 到显示区域。若速度过慢，请更新此实现。
 */
void GColorConsole::updateDisplay() {
    /* 刷新缓冲区中的所有内容，确保 contents 数组包含
     * 我们需要的所有内容。
     */
    flushBuffer();

    /* 写出所有内容。 */
    stringstream toShow;
    toShow << kHTMLHeader;

    for (const auto& line: mContents) {
        /* 启用该样式。 */
        toShow << "<span style=\"";
        toShow << "color:" << line.first.color << ";";
        if (line.first.fontStyle & BOLD)   toShow << "font-weight:bold;";
        if (line.first.fontStyle & ITALIC) toShow << "font-style:italic;";
        toShow << "font-size:" << line.first.fontSize.size() << "pt;";
        toShow << "\">";

        /* 写出文本，并按需转义所有内容。 */
        toShow << htmlEncode(line.second);

        /* 结束该样式。 */
        toShow << "</span>";
    }

    /* 完成并关闭它。 */
    toShow << kHTMLFooter;

    /* 更改文本内容并向下滚动。 */
    GThread::runOnQtGuiThread([&, this] {
        readTextFromFile(toShow);
        scrollToBottom();
    });
}

void GColorConsole::setStyle(const string& color, FontStyle style, FontSize size) {
    flushBuffer();
    mStyle.color = color;
    mStyle.fontStyle = style;
    mStyle.fontSize = size;
}

GColorConsole::FontStyle GColorConsole::style() const {
    return mStyle.fontStyle;
}
string GColorConsole::color() const {
    return mStyle.color;
}
FontSize GColorConsole::fontSize() const {
    return mStyle.fontSize;
}

void GColorConsole::doWithStyle(const string& newColor, FontStyle newStyle, FontSize newSize, std::function<void ()> fn) {
    auto oldColor = color();
    auto oldStyle = style();
    auto oldSize  = fontSize();

    setStyle(newColor, newStyle, newSize);

    /* 执行给定回调。若它抛出异常，则在返回前撤销所有更改。 */
    try {
        fn();
    } catch (...) {
        setStyle(oldColor, oldStyle);
        throw;
    }

    /* 成功了！恢复之前的样式设置。 */
    setStyle(oldColor, oldStyle, oldSize);
}

void GColorConsole::doWithStyle(const string& color, FontStyle style, std::function<void ()> fn) {
    doWithStyle(color, style, fontSize(), fn);
}

void GColorConsole::doWithStyle(const string& color, std::function<void ()> fn) {
    doWithStyle(color, style(), fontSize(), fn);
}

void GColorConsole::doWithStyle(FontStyle style, std::function<void ()> fn) {
    doWithStyle(color(), style, fontSize(), fn);
}

void GColorConsole::doWithStyle(FontStyle style, FontSize size, std::function<void()> fn) {
    doWithStyle(color(), style, size, fn);
}
void GColorConsole::doWithStyle(const std::string& color, FontSize size, std::function<void()> fn) {
    doWithStyle(color, style(), size, fn);
}
void GColorConsole::doWithStyle(FontSize size, std::function<void()> fn) {
    doWithStyle(color(), style(), size, fn);
}

/**** FontSize 实现。 ****/
FontSize::FontSize(size_t size): mSize(size) {
    // 已在初始化列表中处理
}

size_t FontSize::size() const {
    return mSize;
}
