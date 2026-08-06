/*
 * 文件：gcolorchooser.cpp
 * -----------------------
 * 此文件实现 gfilechooser.h 中声明的操作。
 * 各成员的文档请参阅 gfilechooser.h。
 * 
 * @author Marty Stepp
 * @version 2018/09/07
 * - 添加接受 GWindow* parent 的重载
 * @version 2018/08/23
 * - 重命名为 gfontchooser.cpp，以替代 Java 版本
 * @version 2018/07/29
 * - 初始版本
 */

#include "gfontchooser.h"
#include <QFontDialog>
#include "gfont.h"
#include "gthread.h"

GFontChooser::GFontChooser() {
    // 空
}

std::string GFontChooser::showDialog(const std::string& title, const std::string& initialFont) {
    return showDialog(/* 父级 */ (QWidget*) nullptr, title, initialFont);
}

std::string GFontChooser::showDialog(GWindow* parent, const std::string& title, const std::string& initialFont) {
    return showDialog(parent ? parent->getWidget() : nullptr, title, initialFont);
}

std::string GFontChooser::showDialog(QWidget* parent, const std::string& title, const std::string& initialFont) {
    QFont initialQFont = GFont::toQFont(initialFont);
    std::string result = "";
    GThread::runOnQtGuiThread([parent, title, initialQFont, &result]() {
        bool ok = false;
        QFont font = QFontDialog::getFont(&ok, initialQFont, parent, QString::fromStdString(title));
        if (ok) {
            result = GFont::toFontString(font);
        }
    });
    return result;
}
