#include "Font.h"
#include "map.h"
using namespace std;

namespace {
    /* 衬线字体。 */
    const char kSerifFont[] =
        #ifdef __APPLE__
            "Didot"
        #else
            "Serif"
        #endif
    ;

    /* 无衬线字体。 */
    const char kSansSerifFont[] =
        #ifdef __APPLE__
            "Helvetica"
        #else
            "Sans Serif"
        #endif
    ;

    /* 等宽字体。 */
    const char kMonospaceFont[] =
        #ifdef __APPLE__
            "Monaco"
        #else
            "Monospace"
        #endif
    ;

    /* Unicode 衬线字体。 */
    const char kUnicodeSerifFont[] =
        #ifdef __APPLE__
            "Times"
        #elif defined(_WIN32)
            "Times New Roman"
        #else
            "Serif"
        #endif
    ;

    /* Unicode 无衬线字体。 */
    const char kUnicodeSansSerifFont[] =
        #ifdef __APPLE__
            "Lucida Grande"
        #elif defined(_WIN32)
            "Lucida Sans Unicode"
        #else
            "Sans Serif"
        #endif
    ;

    /* Unicode 等宽字体。 */
    const char kUnicodeMonospaceFont[] =
        #ifdef __APPLE__
            "Lucida Grande"
        #elif defined(_WIN32)
            "Lucida Sans Unicode"
        #else
            "Monospace"
        #endif
    ;


    /* 字体族 -> String */
    string to_string(MiniGUI::FontFamily family) {
        if (family == MiniGUI::FontFamily::MONOSPACE) {
            return kMonospaceFont;
        } else if (family == MiniGUI::FontFamily::SANS_SERIF) {
            return kSansSerifFont;
        } else if (family == MiniGUI::FontFamily::SERIF) {
            return kSerifFont;
        } else if (family == MiniGUI::FontFamily::UNICODE_MONOSPACE) {
            return kUnicodeMonospaceFont;
        } else if (family == MiniGUI::FontFamily::UNICODE_SANS_SERIF) {
            return kUnicodeSansSerifFont;
        } else if (family == MiniGUI::FontFamily::UNICODE_SERIF) {
            return kUnicodeSerifFont;
        } else {
            error("Unknown font family.");
        }
    }

    /* 字体样式 -> StanfordCPPLib 字符串。 */
    string to_string(MiniGUI::FontStyle style) {
        if (style == MiniGUI::FontStyle::BOLD) {
            return "BOLD";
        } else if (style == MiniGUI::FontStyle::BOLD_ITALIC) {
            return "BOLDITALIC";
        } else if (style == MiniGUI::FontStyle::ITALIC) {
            return "ITALIC";
        } else if (style == MiniGUI::FontStyle::NORMAL) {
            return "<normal>";
        } else {
            error("Unknown font style.");
        }
    }
}

namespace MiniGUI {
    /* 默认值。 */
    Font::Font() : mFamily(FontFamily::SANS_SERIF),
                   mStyle(FontStyle::NORMAL),
                   mSize(13),
                   mColor("black") {
        // 已在初始化列表中处理。
    }

    Font::Font(FontFamily family, FontStyle style, int size, const string& color)
        : mFamily(family), mStyle(style), mSize(size), mColor(color) {
        // 已在初始化列表中处理。
    }

    FontFamily Font::family() const {
        return mFamily;
    }
    Font Font::family(FontFamily family) const {
        auto result = *this;
        result.mFamily = family;
        return result;
    }

    FontStyle Font::style() const {
        return mStyle;
    }
    Font Font::style(FontStyle style) const {
        auto result = *this;
        result.mStyle = style;
        return result;
    }

    int Font::size() const {
        return mSize;
    }
    Font Font::size(int size) const {
        auto result = *this;
        result.mSize = size;
        return result;
    }

    string Font::color() const {
        return mColor;
    }
    Font Font::color(const string& color) const {
        auto result = *this;
        result.mColor = color;
        return result;
    }

    string Font::stanfordCPPLibFontString() const {
        /* 先处理字体名称。 */
        string result = to_string(family());

        /* 样式（如适用）。 */
        if (style() != FontStyle::NORMAL) {
            result += "-" + to_string(style());
        }

        /* 最后添加字号。 */
        result += "-" + to_string(size());

        return result;
    }
}
