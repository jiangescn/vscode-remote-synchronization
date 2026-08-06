/*
 * 文件：gcolorchooser.h
 * ---------------------
 * 此文件定义支持
 * 弹出图形对话框以选择颜色。
 * 
 * @author Marty Stepp
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * - 添加接受 GWindow* parent 的重载
 * @version 2018/08/23
 * - 重命名为 gcolorchooser.h，以替代 Java 版本
 * @version 2018/07/29
 * - 初始版本
 */


#ifndef _gcolorchooser_h
#define _gcolorchooser_h

#include <string>
#include <QWidget>

#include "gwindow.h"

/**
 * GColorChooser 类包含用于弹出颜色选择
 * 允许用户选择颜色的对话框。
 * 每个方法都会阻塞，直到选择颜色并关闭对话框，
 * 返回用户选择的颜色（如果用户取消，则为空字符串）。
 */
class GColorChooser {
public:
    /**
     * 弹出颜色选择对话框，使用给定的顶部标题文本、
     * 并预先选中给定的初始颜色。
     * 返回所选颜色的颜色字符串，例如 "#ff0077" 或 "blue"。
     */
    static std::string showDialog(const std::string& title, int initialColor);

    /**
     * 弹出颜色选择对话框，使用给定的顶部标题文本、
     * 并预先选中给定的初始颜色。
     * 返回所选颜色的颜色字符串，例如 "#ff0077" 或 "blue"。
     */
    static std::string showDialog(GWindow* parent, const std::string& title, int initialColor);

    /**
     * 弹出颜色选择对话框，使用给定的顶部标题文本、
     * 并预先选中给定的初始颜色。
     * 返回所选颜色的颜色字符串，例如 "#ff0077" 或 "blue"。
     */
    static std::string showDialog(QWidget* parent, const std::string& title, int initialColor);

    /**
     * 弹出颜色选择对话框，使用给定的顶部标题文本、
     * 并预先选中给定的初始颜色。
     * 返回所选颜色的颜色字符串，例如 "#ff0077" 或 "blue"。
     */
    static std::string showDialog(const std::string& title = "", const std::string& initialColor = "");

    /**
     * 弹出颜色选择对话框，使用给定的顶部标题文本、
     * 并预先选中给定的初始颜色。
     * 返回所选颜色的颜色字符串，例如 "#ff0077" 或 "blue"。
     */
    static std::string showDialog(GWindow* parent, const std::string& title = "", const std::string& initialColor = "");

    /**
     * 弹出颜色选择对话框，使用给定的顶部标题文本、
     * 并预先选中给定的初始颜色。
     * 返回所选颜色的颜色字符串，例如 "#ff0077" 或 "blue"。
     */
    static std::string showDialog(QWidget* parent, const std::string& title = "", const std::string& initialColor = "");

private:
    GColorChooser();   // 阻止构造
};

#endif // _gcolorchooser_h
