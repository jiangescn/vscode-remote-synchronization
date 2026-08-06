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
 * - 重命名为 gcolorchooser.cpp，以替代 Java 版本
 * @version 2018/07/29
 * - 初始版本
 */

#include "gcolorchooser.h"
#include <QColorDialog>
#include "gcolor.h"
#include "gthread.h"

GColorChooser::GColorChooser() {
    // 空
}

std::string GColorChooser::showDialog(const std::string& title, int initialColor) {
    return showDialog(/* 父级 */ (QWidget*) nullptr, title, initialColor);
}

std::string GColorChooser::showDialog(GWindow* parent, const std::string& title, int initialColor) {
    return showDialog(parent ? parent->getWidget() : nullptr, title, GColor::convertRGBToColor(initialColor));
}

std::string GColorChooser::showDialog(QWidget* parent, const std::string& title, int initialColor) {
    return showDialog(parent, title, GColor::convertRGBToColor(initialColor));
}

std::string GColorChooser::showDialog(const std::string& title, const std::string& initialColor) {
    return showDialog(/* 父级 */ (QWidget*) nullptr, title, initialColor);
}

std::string GColorChooser::showDialog(GWindow* parent, const std::string& title, const std::string& initialColor) {
    return showDialog(parent ? parent->getWidget() : nullptr, title, initialColor);
}

std::string GColorChooser::showDialog(QWidget* parent, const std::string& title, const std::string& initialColor) {
    QColor initialQColor = initialColor.empty() ? Qt::white : GColor::toQColor(initialColor);
    std::string result = "";
    GThread::runOnQtGuiThread([parent, title, initialQColor, &result]() {
        QColor selectedColor = QColorDialog::getColor(initialQColor, parent, QString::fromStdString(title));
        if (selectedColor.isValid()) {
            result = GColor::convertQColorToColor(selectedColor);
        }
    });
    return result;
}
