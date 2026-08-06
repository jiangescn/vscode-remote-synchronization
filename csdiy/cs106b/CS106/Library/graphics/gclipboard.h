/*
 * 文件：gclipboard.h
 * ------------------
 *
 * @author Marty Stepp
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gclipboard.h，以替代 Java 版本
 * @version 2018/07/19
 * - 初始版本
 */


#ifndef _gclipboard_h
#define _gclipboard_h

#include <QKeyEvent>
#include <string>

/**
 * GClipboard 类包含可用于获取和设置的静态方法
 * 系统剪贴板的内容。
 */
class GClipboard {
public:
    /**
     * 返回系统剪贴板的当前内容。
     */
    static std::string get();

    /**
     * 如果给定事件表示“复制”操作，则返回 true。
     * @throw 如果事件为空，则抛出 ErrorException
     */
    static bool isCopy(QKeyEvent* event);

    /**
     * 如果给定事件表示“剪切”操作，则返回 true。
     * @throw 如果事件为空，则抛出 ErrorException
     */
    static bool isCut(QKeyEvent* event);

    /**
     * 如果给定事件表示“粘贴”操作，则返回 true。
     * @throw 如果事件为空，则抛出 ErrorException
     */
    static bool isPaste(QKeyEvent* event);

    /**
     * 设置系统剪贴板以存储给定文本。
     * 等价于“复制”操作。
     */
    static void set(const std::string& text);

private:
    GClipboard();   // 阻止构造
};

#endif // _gclipboard_h
