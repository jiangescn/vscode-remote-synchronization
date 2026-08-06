/*
 * 文件：goptionpane.h
 * -------------------
 *
 * @author Marty Stepp
 * @version 2018/09/23
 * - 重命名枚举常量以避免名称冲突（可能破坏部分客户端代码）
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 goptionpane.h，以替代 Java 版本
 * @version 2018/06/28
 * - 初始版本
 */


#ifndef _goptionpane_h
#define _goptionpane_h

#include <string>

#include "ginteractor.h"
#include "vector.h"

// 前向声明
class GWindow;

/**
 * 此类提供弹出图形输入/输出对话框的静态方法
 * 屏幕上的方框。
 */
class GOptionPane {
public:
    /**
     * showConfirmDialog 使用的类型，表示三种
     * 确认对话框：是/否、是/否/取消，或确定/取消。
     */
    enum ConfirmType {
        CONFIRM_YES_NO = 0,
        CONFIRM_YES_NO_CANCEL = 1,
        CONFIRM_OK_CANCEL = 2
    };

    /**
     * 某些选项对话框可能返回的各种结果。
     * 请注意，NO 的值为 0，而 YES/OK 为非零值，因此你
     * 可以在布尔上下文中使用 ConfirmResult。
     */
    enum ConfirmResult {
        CONFIRM_CANCEL = -1,   // 用于是/否/取消对话框
        CONFIRM_NO = 0,        // 使用 0，使“no”为假值
        CONFIRM_YES = 1,       // 使用 1，使“yes”为真值
        CONFIRM_OK = 2         // 用于确定/取消对话框
    };

    /**
     * showMessageDialog 使用的类型，表示各种
     * 消息对话框。类型通常会略微改变对话框外观，
     * 例如更改其图标或字体。
     */
    enum MessageType {
        MESSAGE_ERROR = 0,
        MESSAGE_INFORMATION = 1,
        MESSAGE_PLAIN = -1,
        MESSAGE_WARNING = 2,
        MESSAGE_QUESTION = 3,
        MESSAGE_ABOUT = 4
    };

    /**
     * 弹出“是/否”确认框。
     * 用户单击按钮关闭对话框后，会返回某个
     * 返回 GOptionPaneResult 枚举常量。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     */
    static ConfirmResult showConfirmDialog(const std::string& message,
                                           const std::string& title = "",
                                           ConfirmType type = CONFIRM_YES_NO);

    /**
     * 弹出“是/否”确认框。
     * 用户单击按钮关闭对话框后，会返回某个
     * 返回 GOptionPaneResult 枚举常量。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     */
    static ConfirmResult showConfirmDialog(GWindow* parent,
                                           const std::string& message,
                                           const std::string& title = "",
                                           ConfirmType type = CONFIRM_YES_NO);

    /**
     * 弹出“是/否”确认框。
     * 用户单击按钮关闭对话框后，会返回某个
     * 返回 GOptionPaneResult 枚举常量。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     */
    static ConfirmResult showConfirmDialog(QWidget* parent,
                                           const std::string& message,
                                           const std::string& title = "",
                                           ConfirmType type = CONFIRM_YES_NO);

    /**
     * 弹出带文本字段的输入框，用户可在其中输入
     * 响应，并将其返回。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     * 若用户取消对话框，则返回空字符串。
     */
    static std::string showInputDialog(const std::string& message,
                                       const std::string& title = "",
                                       const std::string& initialValue = "");

    /**
     * 弹出带文本字段的输入框，用户可在其中输入
     * 响应，并将其返回。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     * 若用户取消对话框，则返回空字符串。
     */
    static std::string showInputDialog(GWindow* parent,
                                       const std::string& message,
                                       const std::string& title = "",
                                       const std::string& initialValue = "");

    /**
     * 弹出带文本字段的输入框，用户可在其中输入
     * 响应，并将其返回。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     * 若用户取消对话框，则返回空字符串。
     */
    static std::string showInputDialog(QWidget* parent,
                                       const std::string& message,
                                       const std::string& title = "",
                                       const std::string& initialValue = "");

    /**
     * 向用户显示输出消息对话框。
     * 用户必须单击“确定”按钮关闭对话框。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     * 可选的 type 参数必须是 PLAIN_MESSAGE、INFORMATION_MESSAGE、
     * WARNING_MESSAGE 或 QUESTION_MESSAGE；这会略微影响对话框的
     * 外观。默认为 PLAIN_MESSAGE。
     */
    static void showMessageDialog(const std::string& message,
                                  const std::string& title = "",
                                  MessageType type = MESSAGE_PLAIN);

    /**
     * 向用户显示输出消息对话框。
     * 用户必须单击“确定”按钮关闭对话框。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     * 可选的 type 参数必须是 PLAIN_MESSAGE、INFORMATION_MESSAGE、
     * WARNING_MESSAGE 或 QUESTION_MESSAGE；这会略微影响对话框的
     * 外观。默认为 PLAIN_MESSAGE。
     */
    static void showMessageDialog(GWindow* parent,
                                  const std::string& message,
                                  const std::string& title = "",
                                  MessageType type = MESSAGE_PLAIN);

    /**
     * 向用户显示输出消息对话框。
     * 用户必须单击“确定”按钮关闭对话框。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     * 可选的 type 参数必须是 PLAIN_MESSAGE、INFORMATION_MESSAGE、
     * WARNING_MESSAGE 或 QUESTION_MESSAGE；这会略微影响对话框的
     * 外观。默认为 PLAIN_MESSAGE。
     */
    static void showMessageDialog(QWidget* parent,
                                  const std::string& message,
                                  const std::string& title = "",
                                  MessageType type = MESSAGE_PLAIN);

    /**
     * 显示一个通用输入框，其中有一组按钮供用户
     * 选择一个选项。用户单击的按钮以字符串形式返回。
     * 若用户取消对话框，则返回空字符串。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     * 调用者可以提供列表中可选的初始选中值。
     */
    static std::string showOptionDialog(const std::string& message,
                                        const Vector<std::string>& options,
                                        const std::string& title = "",
                                        const std::string& initiallySelected = "");

    /**
     * 显示一个通用输入框，其中有一组按钮供用户
     * 选择一个选项。用户单击的按钮以字符串形式返回。
     * 若用户取消对话框，则返回空字符串。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     * 调用者可以提供列表中可选的初始选中值。
     */
    static std::string showOptionDialog(GWindow* parent,
                                        const std::string& message,
                                        const Vector<std::string>& options,
                                        const std::string& title = "",
                                        const std::string& initiallySelected = "");

    /**
     * 显示一个通用输入框，其中有一组按钮供用户
     * 选择一个选项。用户单击的按钮以字符串形式返回。
     * 若用户取消对话框，则返回空字符串。
     * 调用者可以提供可选的窗口标题；若未提供，则使用默认标题。
     * 调用者可以提供列表中可选的初始选中值。
     */
    static std::string showOptionDialog(QWidget* parent,
                                        const std::string& message,
                                        const Vector<std::string>& options,
                                        const std::string& title = "",
                                        const std::string& initiallySelected = "");

    /**
     * 在可滚动的等宽文本区域中显示给定文本。
     * rows/cols 参数控制显示大小；设为 <= 0 使用默认限制。
     */
    static void showTextFileDialog(const std::string& fileText,
                                   const std::string& title = "",
                                   int rows = -1, int cols = -1);

    /**
     * 在可滚动的等宽文本区域中显示给定文本。
     * rows/cols 参数控制显示大小；设为 <= 0 使用默认限制。
     */
    static void showTextFileDialog(GWindow* parent,
                                   const std::string& fileText,
                                   const std::string& title = "",
                                   int rows = -1, int cols = -1);

    /**
     * 在可滚动的等宽文本区域中显示给定文本。
     * rows/cols 参数控制显示大小；设为 <= 0 使用默认限制。
     */
    static void showTextFileDialog(QWidget* parent,
                                   const std::string& fileText,
                                   const std::string& title = "",
                                   int rows = -1, int cols = -1);

private:
    /**
     * 私有构造函数，防止客户端尝试构造
     * GOptionPane 对象。该类旨在通过其
     * 通过静态方法使用，而不是实例化。
     */
    GOptionPane();

    /**
     * showConfirmDialog 可能返回的结果。
     * 这些值会转换为 Result 枚举值。
     */
    enum InternalResult {
        INTERNAL_CANCEL_OPTION = 2,
        INTERNAL_CLOSED_OPTION = -1,
        INTERNAL_NO_OPTION = 1,
        INTERNAL_OK_OPTION = 0,
        INTERNAL_YES_OPTION = 0
    };
};

#endif // _goptionpane_h
