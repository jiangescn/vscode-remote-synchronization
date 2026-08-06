/*
 * 文件：gfilechooser.h
 * --------------------
 * 此文件定义支持
 * 弹出图形对话框以选择文件名。
 * 
 * @author Marty Stepp
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * - 添加接受 GWindow* parent 的重载
 * @version 2018/08/23
 * - 重命名为 gfilechooser.h，以替代 Java 版本
 * @version 2018/06/28
 * - 初始版本
 */


#ifndef _gfilechooser_h
#define _gfilechooser_h

#include <string>
#include <QWidget>

#include "gwindow.h"

/**
 * GFileChooser 类包含用于弹出文件选择
 * 允许用户选择文件的对话框。
 * 每个方法都会阻塞，直到选择文件并关闭对话框，
 * 返回用户选择的文件（如果用户取消，则为空字符串）。
 */
class GFileChooser {
public:
    /**
     * 弹出“打开”文件选择对话框，使用给定顶部标题文本、
     * 当前目录和文件过滤器。所有参数均为可选。
     * @param fileFilter 文件过滤字符串，例如 "*.gif,*.jpg,*.png"。
     */
    static std::string showOpenDialog(const std::string& title = "Open file", const std::string& currentDir = "", const std::string& fileFilter = "");

    /**
     * 弹出“打开”文件选择对话框，使用给定顶部标题文本、
     * 当前目录和文件过滤器。所有参数均为可选。
     * @param fileFilter 文件过滤字符串，例如 "*.gif,*.jpg,*.png"。
     */
    static std::string showOpenDialog(GWindow* parent, const std::string& title = "Open file", const std::string& currentDir = "", const std::string& fileFilter = "");

    /**
     * 弹出“打开”文件选择对话框，使用给定顶部标题文本、
     * 当前目录和文件过滤器。所有参数均为可选。
     * @param fileFilter 文件过滤字符串，例如 "*.gif,*.jpg,*.png"。
     */
    static std::string showOpenDialog(QWidget* parent, const std::string& title = "Open file", const std::string& currentDir = "", const std::string& fileFilter = "");

    /**
     * 弹出“保存”文件选择对话框，使用给定顶部标题文本、
     * 当前目录和文件过滤器。所有参数均为可选。
     *
     * “打开”对话框和“保存”对话框的主要区别
     * 除标题栏文字不同外，“保存”对话框还允许
     * 允许用户输入尚不存在的文件名。
     *
     * 若用户选择了已经存在的文件名，则会
     * 提示用户是否覆盖此文件。若选择“否”，对话框会
     * 保持打开；若选择“是”，则关闭。
     * @param fileFilter 文件过滤字符串，例如 "*.gif,*.jpg,*.png"。
     */
    static std::string showSaveDialog(const std::string& title = "Save file", const std::string& currentDir = "", const std::string& fileFilter = "");

    /**
     * 弹出“保存”文件选择对话框，使用给定顶部标题文本、
     * 当前目录和文件过滤器。所有参数均为可选。
     *
     * “打开”对话框和“保存”对话框的主要区别
     * 除标题栏文字不同外，“保存”对话框还允许
     * 允许用户输入尚不存在的文件名。
     *
     * 若用户选择了已经存在的文件名，则会
     * 提示用户是否覆盖此文件。若选择“否”，对话框会
     * 保持打开；若选择“是”，则关闭。
     * @param fileFilter 文件过滤字符串，例如 "*.gif,*.jpg,*.png"。
     */
    static std::string showSaveDialog(GWindow* parent, const std::string& title = "Save file", const std::string& currentDir = "", const std::string& fileFilter = "");

    /**
     * 弹出“保存”文件选择对话框，使用给定顶部标题文本、
     * 当前目录和文件过滤器。所有参数均为可选。
     *
     * “打开”对话框和“保存”对话框的主要区别
     * 除标题栏文字不同外，“保存”对话框还允许
     * 允许用户输入尚不存在的文件名。
     *
     * 若用户选择了已经存在的文件名，则会
     * 提示用户是否覆盖此文件。若选择“否”，对话框会
     * 保持打开；若选择“是”，则关闭。
     * @param fileFilter 文件过滤字符串，例如 "*.gif,*.jpg,*.png"。
     */
    static std::string showSaveDialog(QWidget* parent, const std::string& title = "Save file", const std::string& currentDir = "", const std::string& fileFilter = "");

private:
    GFileChooser();   // 阻止构造

    /*
     * 对话框类型的常量，类似 Java JFileChooser 中的常量
     */
    enum DialogType {
        OPEN_DIALOG = 0,
        SAVE_DIALOG = 1
    };

    /*
     * 在逗号分隔的文件筛选器格式与以下格式之间转换：
     * 供 Qt 使用，其分隔符为 ;;。
     */
    static std::string normalizeFileFilter(const std::string& fileFilter);
};

#endif // _gfilechooser_h
