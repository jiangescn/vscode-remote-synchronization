/*
 * 文件：gfont.h
 * -------------
 *
 * @author Marty Stepp
 * @version 2019/04/30
 * - 为 GText* 添加 changeFontSize
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gfont.h，以替代 Java 版本
 * @version 2018/07/05
 * - 初始版本
 */


#ifndef _gfont_h
#define _gfont_h

#include <string>
#include <QFont>

#include "ginteractor.h"
#include "gobjects.h"

/**
 * 此类包含在 GUI 系统中处理字体的静态方法。
 * 字体字符串具有以下格式：
 *
 * <pre>
 * "字体族-样式-大小"
 * </pre>
 *
 * 其中 <code>style</code> 和 <code>size</code> 都是可选的。
 * 若缺少任一元素，或以星号指定，
 * 保留现有值。
 */
class GFont {
public:
    /**
     * 将给定交互控件的字体设为粗体。
     * 字体名称和大小保持不变。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    static void boldFont(GInteractor* interactor);

    /**
     * 修改给定交互控件的字体，将字号改变给定的
     * 点的数量。大小变化量可以为正，也可以为负。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    static void changeFontSize(GInteractor* interactor, int dsize);

    /**
     * 修改给定标签的字体，将字号改变给定的
     * 点的数量。大小变化量可以为正，也可以为负。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    static void changeFontSize(GText* label, int dsize);

    /**
     * 修改给定 Qt 字体对象的大小，将字号改变给定的
     * 点数，并返回修改后的新字体。
     * 大小变化可以为正或负。
     */
    static QFont changeFontSize(const QFont& font, int dsize);

    /**
     * 修改给定字体对象，将其粗细和/或大小更改为
     * 给定值，并返回修改后的新字体。
     */
    static QFont deriveQFont(const QFont& font, QFont::Weight weight = QFont::Normal, int size = -1);

    /**
     * 修改给定字体对象，更改其字体族、粗细和/或
     * 将大小改为给定值，并返回修改后的新字体。
     */
    static QFont deriveQFont(const QFont& font, const std::string& fontFamily, QFont::Weight weight = QFont::Normal, int size = -1);

    /**
     * 修改给定字体对象，将其粗细和/或大小更改为
     * 给定值，并返回修改后的新字体。
     * 传入的字体应为类似“Helvetica-12-Bold”的字体字符串。
     */
    static QFont deriveQFont(const std::string& font, QFont::Weight weight = QFont::Normal, int size = -1);

    /**
     * 修改给定字体对象，更改其字体族、粗细和/或
     * 将大小改为给定值，并返回修改后的新字体。
     * 传入的字体应为类似“Helvetica-12-Bold”的字体字符串。
     */
    static QFont deriveQFont(const std::string& font, const std::string& fontFamily, QFont::Weight weight = QFont::Normal, int size = -1);

    /**
     * 将给定交互控件的字体设为斜体。
     * 字体名称和大小保持不变。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    static void italicFont(GInteractor* interactor);

    /**
     * 将给定 Qt 字体对象转换为以下字体字符串：
     * "Helvetica-12-Bold"。
     */
    static std::string toFontString(const QFont& font);

    /**
     * 将“Helvetica-12-Bold”这样的字体字符串转换为 Qt 字体对象。
     */
    static QFont toQFont(const std::string& fontString);

    /**
     * 将“Helvetica-*-12”这样的字体字符串转换为 Qt 字体对象，
     * 对于其中不存在的任何默认值，使用给定的 `basis` 对象
     * 字体字符串。
     */
    static QFont toQFont(const QFont& basisFont, const std::string& fontString);

private:
    GFont();   // 阻止构造
    static QFont::StyleHint getStyleHint(const std::string& fontFamily);
};

#endif // _gfont_h
