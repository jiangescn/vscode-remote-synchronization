#pragma once

#include <string>

namespace MiniGUI {
    /* 可用字体族。 */
    enum class FontFamily {
        SERIF,
        SANS_SERIF,
        MONOSPACE,
        UNICODE_SERIF,
        UNICODE_SANS_SERIF,
        UNICODE_MONOSPACE
    };

    /* 字体样式。 */
    enum class FontStyle {
        NORMAL,
        BOLD,
        ITALIC,
        BOLD_ITALIC
    };

    /* 表示带样式字体的类型，由字体、字体效果和
     * 字号和字体颜色。
     *
     * 考虑到跨平台环境下某些字体可能不受支持，或
     * 某些字体需要满足特定要求，而渲染这些字体的代码
     * 文本应使用此类型，以确保运行时不产生警告。
     *
     * 此类型不可变。
     */
    class Font {
    public:
        /* 默认字体设置。 */
        Font();
        Font(FontFamily family, FontStyle style, int size, const std::string& color);

        /* 访问属性，或生成具有指定属性的新字体。 */
        FontFamily family() const;
        Font family(FontFamily family) const;

        FontStyle style() const;
        Font style(FontStyle style) const;

        int size() const;
        Font size(int size) const;

        std::string color() const;
        Font color(const std::string& color) const;

        /* 原始字体字符串，用于与 StanfordCPPLib 通信。此字符串
         * 主要用于与 MiniGUI 中其他类型通信，并且
         * 不供客户端使用。
         */
        std::string stanfordCPPLibFontString() const;

    private:
        FontFamily  mFamily;
        FontStyle   mStyle;
        int         mSize;
        std::string mColor;
    };
}
