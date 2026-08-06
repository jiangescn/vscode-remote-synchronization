#ifndef GColorConsole_Included
#define GColorConsole_Included

#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <memory>
#include "gbrowserpane.h"

/* 表示字号的类型。 */
class FontSize {
public:
    /* 默认字号。 */
    static constexpr std::size_t DEFAULT_FONT_SIZE = 11;

    explicit FontSize(std::size_t size = DEFAULT_FONT_SIZE);
    std::size_t size() const;

private:
    std::size_t mSize;
};

/* 表示可渲染文本的图形文本控制台类型
 * 使用不同颜色和样式。对象本身是一个流，因此可以
 * 可使用标准格式化操作进行读写，并且还可独立地
 * 作为 GInteractor 安装到 GWindow 中。
 */
class GColorConsole: public std::ostream, public GBrowserPane {
public:
    GColorConsole();
    ~GColorConsole();

    enum FontStyle {
        NORMAL = 0,
        BOLD   = 1,
        ITALIC = 2,
        BOLD_ITALIC = 3 // BOLD | ITALIC
    };

    /* 样式设置。 */
    void setStyle(const std::string& color = "black",
                  FontStyle style = NORMAL,
                  FontSize  size = FontSize{});
    std::string color() const;
    FontStyle style() const;
    FontSize  fontSize() const;

    /* 清除之前渲染的所有文本。此操作不会更新显示；若要更新，
     * 随后刷新流。
     */
    void clearDisplay();

    /* 在更改控制台样式后执行指定代码块
     * 改为指定值。例如，当你想临时
     * 更改颜色或字体样式。
     */
    void doWithStyle(const std::string& color, FontStyle style, std::function<void()> fn);
    void doWithStyle(const std::string& color, FontStyle style, FontSize size, std::function<void()> fn);
    void doWithStyle(FontStyle style, FontSize size, std::function<void()> fn);
    void doWithStyle(const std::string& color, FontSize size, std::function<void()> fn);
    void doWithStyle(FontSize size, std::function<void()> fn);
    void doWithStyle(const std::string& color, std::function<void()> fn);
    void doWithStyle(FontStyle style, std::function<void()> fn);

private:
    /* std::stringbuf 的子类型，保存了对所属对象的反向引用
     * 对象。每当发生同步时，它会将内容输出到所挂接的
     * 显示。
     */
    struct ConsoleStreambuf: public std::stringbuf {
        GColorConsole* mOwner;

        ConsoleStreambuf(GColorConsole* owner) : mOwner(owner) {}

        /* 更新显示。 */
        virtual int sync() override;
    };

    /* 将 stringbuf 中所有缓冲文本刷新到内容列表。
     * 通常用于确保样式设置正确完成。
     */
    void flushBuffer();

    /* 更新显示，使其与保存的文本同步。 */
    void updateDisplay();

    /* 到目前为止已渲染的文本块，每块都带有样式标记。 */
    struct Style {
        std::string color = "black";
        FontStyle   fontStyle = NORMAL;
        FontSize    fontSize = FontSize{};
    };

    Style mStyle;
    std::vector<std::pair<Style, std::string>> mContents;

    /* 抱歉，不允许复制！ */
    GColorConsole(const GColorConsole &) = delete;
    GColorConsole(GColorConsole &&) = delete;
    void operator= (GColorConsole) = delete;
};

#endif
