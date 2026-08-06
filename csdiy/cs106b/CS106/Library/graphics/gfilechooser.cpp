/*
 * 文件：gfilechooser.cpp
 * ----------------------
 * 此文件实现 gfilechooser.h 中声明的操作。
 * 各成员的文档请参阅 gfilechooser.h。
 * 
 * @author Marty Stepp
 * @version 2018/09/07
 * - 添加接受 GWindow* parent 的重载
 * @version 2018/08/23
 * - 重命名为 gfilechooser.cpp，以替代 Java 版本
 * @version 2018/06/28
 * - 初始版本
 */

#include "gfilechooser.h"
#include <QFileDialog>
#include "gthread.h"
#include "strlib.h"
#include "vector.h"

GFileChooser::GFileChooser() {
    // 空
}

std::string GFileChooser::showOpenDialog(const std::string& title, const std::string& currentDir, const std::string& fileFilter) {
    return showOpenDialog(/* 父级 */ (QWidget*) nullptr, title, currentDir, fileFilter);
}

std::string GFileChooser::showOpenDialog(GWindow* parent, const std::string& title, const std::string& currentDir, const std::string& fileFilter) {
    return showOpenDialog(parent ? parent->getWidget() : nullptr, title, currentDir, fileFilter);
}

std::string GFileChooser::showOpenDialog(QWidget* parent, const std::string& title, const std::string& currentDir, const std::string& fileFilter) {
    // Qt 筛选器规范：
    // 如果需要多个筛选器，用 ';;' 分隔，例如：
    // “图像 (*.png *.xpm *.jpg);;文本文件 (*.txt);;XML 文件 (*.xml)”

    std::string result = "";
    GThread::runOnQtGuiThread([parent, title, currentDir, fileFilter, &result]() {
        result = QFileDialog::getOpenFileName(parent,
                QString::fromStdString(title),
                QString::fromStdString(currentDir),
                QString::fromStdString(normalizeFileFilter(fileFilter))).toStdString();
    });
    return result;
}

std::string GFileChooser::showSaveDialog(const std::string& title, const std::string& currentDir, const std::string& fileFilter) {
    return showSaveDialog(/* 父级 */ (QWidget*) nullptr, title, currentDir, fileFilter);
}

std::string GFileChooser::showSaveDialog(GWindow* parent, const std::string& title, const std::string& currentDir, const std::string& fileFilter) {
    return showSaveDialog(parent ? parent->getWidget() : nullptr, title, currentDir, fileFilter);
}

std::string GFileChooser::showSaveDialog(QWidget* parent, const std::string& title, const std::string& currentDir, const std::string& fileFilter) {
    std::string result = "";
    GThread::runOnQtGuiThread([parent, title, currentDir, fileFilter, &result]() {
        result = QFileDialog::getSaveFileName(parent,
                QString::fromStdString(title),
                QString::fromStdString(currentDir),
                QString::fromStdString(normalizeFileFilter(fileFilter))).toStdString();
    });
    return result;
}

std::string GFileChooser::normalizeFileFilter(const std::string& fileFilter) {
    Vector<std::string> tokens = stringSplit(fileFilter, ",");
    for (int i = 0; i < tokens.size(); i++) {
        std::string token = tokens[i];
        token = trim(token);
        // TODO：更多处理
        tokens[i] = token;
    }
    return stringJoin(tokens, ";;");
}
