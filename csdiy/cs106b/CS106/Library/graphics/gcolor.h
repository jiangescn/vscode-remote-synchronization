/*
 * 文件：gcolor.h
 * --------------
 *
 * @author Marty Stepp
 * @version 2019/05/05
 * - 添加 getLuminance
 * @version 2018/09/16
 * - 添加 splitRGB/ARGB、hasAlpha；改进 ARGB 支持
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gcolor.h，以替代 Java 版本
 * @version 2018/06/30
 * - 初始版本
 */


#ifndef _gcolor_h
#define _gcolor_h

#include <string>
#include <QColor>

#include "map.h"

/**
 * 此类提供处理颜色的静态方法。
 *
 * 许多图形交互控件和对象接受以字符串指定的颜色
 * 或 RGB 整数。RGB 整数是包含红、绿、蓝分量的整数
 * 按如下方式打包到各位中的 0–255 值：
 *
 * <pre>
 * 00000000 00000000 00000000 00000000
 *    ^        ^        ^        ^
 *    |        |        |        |
 *  alpha     红      绿       蓝
 * </pre>
 *
 * 颜色也可以指定为字符串。
 * 颜色字符串可以是以下预定义颜色名称之一：
 *
 *    <code>BLACK</code>，
 *    <code>BLUE</code>，
 *    <code>CYAN</code>，
 *    <code>DARK_GRAY</code>，
 *    <code>GRAY</code>，
 *    <code>GREEN</code>，
 *    <code>LIGHT_GRAY</code>，
 *    <code>MAGENTA</code>，
 *    <code>ORANGE</code>，
 *    <code>PINK</code>，
 *    <code>RED</code>，
 *    <code>WHITE</code>，以及
 *    <code>YELLOW</code>。
 *
 * 颜色名称中各字母的大小写会被忽略，正如
 * 是空格和下划线，因此颜色 <code>DARK_GRAY</code>
 * 可以写成 <code>"Dark Gray"</code>。
 *
 * 最后，颜色也可以使用以下形式的字符串指定
 * <code>"#rrggbb"</code>，其中 <code>rr</code>、<code>gg</code> 和
 * <code>bb</code> 是表示以下内容的十六进制数字对：
 * 分别表示颜色的红、绿、蓝分量。
 * 还可以通过编写十六进制字符串加入 alpha（不透明度）通道
 * 以 ARGB 形式表示为 <code>"#aarrggbb"</code>。
 */
class GColor {
public:
    /**
     * 表示常见系统颜色名称的常量。
     */
    enum {
        BLACK = 0x000000,
        BLUE = 0x0000FF,
        BROWN = 0x926239,
        CYAN = 0x00FFFF,
        DARKGRAY = 0x595959,
        GRAY = 0x999999,
        GREEN = 0x00FF00,
        LIGHTGRAY = 0xBFBFBF,
        MAGENTA = 0xFF00FF,
        ORANGE = 0xFFC800,
        PINK = 0xFFAFAF,
        PURPLE = 0xFF00FF,
        RED = 0xFF0000,
        WHITE = 0xFFFFFF,
        YELLOW = 0xFFFF00
    } Color;

    /**
     * 将四个 0-255 的整数 RGB 值转换为以下形式的颜色名称：
     * 形式 <code>"#aarrggbb"</code>。其中 <code>aa</code>、<code>rr</code> 等
     * <code>gg</code> 和 <code>bb</code> 的值均为两位
     * 表示该颜色分量强度的十六进制数。
     * 若 a、r、g、b 中任一值超出 0-255，则抛出错误。
     */
    static std::string convertARGBToColor(int a, int r, int g, int b);

    /**
     * 将给定 ARGB 整数转换为以下形式的颜色名称：
     * 形式 <code>"#aarrggbb"</code>。
     */
    static std::string convertARGBToColor(int argb);

    /**
     * 将四个 0-255 的整数 RGB 值转换为 ARGB 整数
     * 形式 <code>0xaarrggbb</code>。其中 <code>aa</code>、<code>rr</code> 等
     * <code>gg</code> 和 <code>bb</code> 的值均为两位
     * 表示该颜色分量强度的十六进制数。
     * 若 a、r、g、b 中任一值超出 0-255，则抛出错误。
     */
    static int convertARGBToARGB(int a, int r, int g, int b);

    /**
     * 将颜色名称转换为编码以下内容的 ARGB 整数：
     * 颜色的 alpha（不透明度）、红、绿、蓝分量。
     */
    static int convertColorToARGB(const std::string& colorName);

    /**
     * 将颜色名称转换为编码该颜色的整数
     * 颜色的红、绿、蓝分量。
     * 此函数也兼容 ARGB 颜色。
     */
    static int convertColorToRGB(const std::string& colorName);

    /**
     * 将 Qt RGB 颜色对象转换为颜色字符串。
     * 不保留 alpha 透明度。
     */
    static std::string convertQColorToColor(const QColor& color);

    /**
     * 将 Qt 颜色对象转换为 RGB 整数。
     * 不保留 alpha 透明度。
     */
    static int convertQColorToRGB(const QColor& color);

    /**
     * 将 RGB 整数值转换为以下形式的颜色名称：
     * 形式 <code>"#rrggbb"</code>。
     * 不保留 alpha 透明度。
     */
    static std::string convertRGBToColor(int rgb);

    /**
     * 将三个 0-255 的整数 RGB 值转换为以下形式的颜色名称：
     * 格式为 <code>"#rrggbb"</code>。其中 <code>rr</code>、
     * <code>gg</code> 和 <code>bb</code> 的值均为两位
     * 表示该颜色分量强度的十六进制数。
     * 若 r、g、b 中任一值超出 0-255，则抛出错误。
     */
    static std::string convertRGBToColor(int r, int g, int b);

    /**
     * 将三个 0-255 的整数 RGB 值转换为单个 RGB 整数。
     * <code>rr</code>、<code>gg</code> 和 <code>bb</code> 的值均
     * 表示该分量强度的两位十六进制数。
     * 若 r、g、b 中任一值超出 0-255，则抛出错误。
     */
    static int convertRGBToRGB(int r, int g, int b);

    /**
     * 将给定整数的 'alpha'（高位）设为 ff。
     * 如果 RGB 并非全黑，但 alpha 为 0，则假定
     * 客户端原本想使用不透明颜色，并添加 ff 作为 alpha 通道。
     */
    static int fixAlpha(int argb);

    /**
     * 返回给定 RGB 整数的光度亮度，
     * 它衡量颜色的明亮程度。
     * 使用以下公式计算：
     * https://en.wikipedia.org/wiki/Relative_luminance
     */
    static double getLuminance(int rgb);

    /**
     * 返回给定颜色的光度亮度，
     * 它衡量颜色的明亮程度。
     * 使用以下公式计算：
     * https://en.wikipedia.org/wiki/Relative_luminance
     */
    static double getLuminance(const std::string& color);

    /**
     * 如果给定颜色字符串采用 8 个十六进制字符的形式，则返回 true
     * 在最高两个字符中包含 alpha 通道，
     * 前面带井号，例如 "#aaff0033"。
     */
    static bool hasAlpha(const std::string& color);

    /**
     * 将给定 ARGB 整数拆分为四个 0-255 的整数分量。
     * <code>aa</code>、<code>rr</code> 等每一项
     * <code>gg</code> 和 <code>bb</code> 的值均为两位
     * 表示该颜色分量强度的十六进制数。
     */
    static void splitARGB(int argb, int& a, int& r, int& g, int& b);

    /**
     * 将给定 RGB 整数拆分为三个 0-255 的整数分量。
     * <code>rr</code>、<code>gg</code> 和 <code>bb</code> 的值均
     * 表示该分量强度的两位十六进制数。
     * 忽略 alpha 透明度。
     */
    static void splitRGB(int rgb, int& r, int& g, int& b);

    /**
     * 将颜色字符串转换为 Qt 颜色对象。
     * 如果颜色字符串包含 alpha 分量，则保留 alpha 透明度。
     */
    static QColor toQColor(const std::string& color);

    /**
     * 将 ARGB 整数转换为 Qt 颜色对象。
     * 保留 QColor 对象中的 alpha 透明度。
     */
    static QColor toQColorARGB(int argb);

private:
    GColor();   // 禁止构造

    /**
     * 移除大小写差异和标点；例如 "Dark Gray" => "darkgray"
     */
    static std::string canonicalColorName(const std::string& str);

    /**
     * 返回常用颜色表的引用，
     * 从名称到 RGB 整数的映射。
     */
    static const Map<std::string, int>& colorTable();

    /**
     * 返回常用颜色表的引用，
     * 从名称到颜色字符串的映射。
     */
    static const Map<std::string, std::string>& colorNameTable();

    // 内部颜色表
    static Map<std::string, int> _colorTable;
    static Map<std::string, std::string> _colorNameTable;
};

#endif // _gcolor_h
