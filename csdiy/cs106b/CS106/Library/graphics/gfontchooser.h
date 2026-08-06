/*
 * 文件：gfontchooser.h
 * ----------------------
 * 此文件定义支持
 * 弹出图形对话框以选择字体。
 * 
 * @author Marty Stepp
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * - 添加接受 GWindow* parent 的重载
 * @version 2018/08/23
 * - 重命名为 gfontchooser.h，以替代 Java 版本
 * @version 2018/07/29
 * - 初始版本
 */


#ifndef _gfontchooser_h
#define _gfontchooser_h

#include <string>
#include <QWidget>

#include "gwindow.h"

/**
 * GFontChooser 类包含用于弹出字体选择
 * 允许用户选择字体族、大小和样式的对话框。
 * 每个方法都会阻塞，直到选择字体并关闭对话框，
 * 返回用户选择的字体（如果用户取消，则为空字符串）。
 *
 * 字体表示为“Helvetica-12-Bold”或类似的字体字符串
 * “Times New Roman-14”。
 *
 * 有关字体和字体字符串的更多信息，请参阅 GFont 类。
 */
class GFontChooser {
public:
    /**
     * 弹出字体选择对话框，使用给定顶部标题文本
     * 以及给定的初始选中字体。所有参数均为可选。
     * @param initialFont 字体字符串，例如 "Helvetica-12-Bold"。
     */
    static std::string showDialog(const std::string& title = "", const std::string& initialFont = "");

    /**
     * 弹出字体选择对话框，使用给定顶部标题文本
     * 以及给定的初始选中字体。所有参数均为可选。
     * @param initialFont 字体字符串，例如 "Helvetica-12-Bold"。
     */
    static std::string showDialog(GWindow* parent, const std::string& title = "", const std::string& initialFont = "");

    /**
     * 弹出字体选择对话框，使用给定顶部标题文本
     * 以及给定的初始选中字体。所有参数均为可选。
     * @param initialFont 字体字符串，例如 "Helvetica-12-Bold"。
     */
    static std::string showDialog(QWidget* parent, const std::string& title = "", const std::string& initialFont = "");

private:
    GFontChooser();   // 阻止构造
};

#endif // _gfontchooser_h
