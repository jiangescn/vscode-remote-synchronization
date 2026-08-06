/*
 * 文件：gtextarea.h
 * -----------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 将部分事件监听代码移到 GInteractor 父类
 * @version 2018/09/10
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gtextarea.h，以替代 Java 版本
 * @version 2018/06/25
 * - 初始版本
 */


#ifndef _gtextarea_h
#define _gtextarea_h

#include <string>
#include <QTextEdit>

#include "ginteractor.h"

class _Internal_QTextEdit;

/**
 * GTextArea 是多行可编辑文本框。
 * 该框允许用户输入任意长度的文档。
 * 如果文本过长而无法放入可见区域，将出现滚动条
 * 方框面积。
 */
class GTextArea : public GInteractor {
public:
    /**
     * 创建足够大、可显示给定行数的新文本区域
     * 以及文本的列。
     * @throw 如果 rows 或 columns 为负，则抛出 ErrorException
     */
    GTextArea(int rows, int columns, QWidget* parent = nullptr);

    /**
     * 创建具有给定初始文本的新文本区域。
     */
    GTextArea(const std::string& text = "", QWidget* parent = nullptr);

    /**
     * 释放文本区域内部分配的内存。
     */
    ~GTextArea() override;

    /**
     * 将格式化文本添加到文本区域末尾。
     * 文本将使用给定颜色和字体格式化。
     */
    virtual void appendFormattedText(const std::string& text, const std::string& color = "", const std::string& font = "");

    /**
     * 将 HTML 格式文本添加到文本区域末尾。
     */
    virtual void appendHtml(const std::string& html);

    /**
     * 将给定纯文本添加到文本区域末尾。
     */
    virtual void appendText(const std::string& text);

    /**
     * 取消选择文本区域中当前选中的任何文本。
     */
    virtual void clearSelection();

    /**
     * 将文本区域中的文本设为空。
     */
    virtual void clearText();

    /**
     * 返回文本区域的可见列数（字符宽度）。
     */
    virtual int getColumns() const;

    /**
     * 以以下形式返回文本区域中键盘光标的当前位置
     * 整个文本字符串中的从 0 开始字符索引。
     */
    virtual int getCursorPosition() const;

    /**
     * 以 HTML 返回文本区域的当前文本。
     * 它与 getText 的区别是不会移除标签和格式。
     */
    virtual std::string getHtml() const;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回文本区域的占位文本，通常显示在
     * 当文本区域为空时，以浅灰色文字显示。
     * 这通常是向用户提示应输入什么值。
     * 默认初始占位符为空。
     */
    virtual std::string getPlaceholder() const;

    /**
     * 返回文本区域的可见行数（行高度）。
     * 这是近似值；如果
     * 文本区域的大小并非行/文本行大小的整数倍。
     */
    virtual int getRows() const;

    /**
     * 返回文本区域中当前选中的文本。
     * 若当前未选择文本，则返回空字符串。
     */
    virtual std::string getSelectedText() const;

    /**
     * 以索引形式返回当前文本选区末尾之后的位置
     * 整个文本字符串中的从 0 开始字符索引。
     * 若当前未选择任何文本，则返回 -1。
     */
    virtual int getSelectionEnd() const;

    /**
     * 返回当前选中的字符数。
     * 若当前未选择文本，则返回 0。
     */
    virtual int getSelectionLength() const;

    /**
     * 以索引形式返回当前文本选区的起始位置
     * 整个文本字符串中的从 0 开始字符索引。
     * 若当前未选择任何文本，则返回 -1。
     */
    virtual int getSelectionStart() const;

    /**
     * 返回文本区域的当前文本。
     */
    virtual std::string getText() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 如果用户右键单击以下对象时会弹出上下文菜单，则返回 true
     * 文本区域。
     * 默认值为 true，但可以通过调用以下方法关闭：
     * setContextMenuEnabled(false)。
     */
    virtual bool isContextMenuEnabled() const;

    /**
     * 返回文本区域是否允许用户修改其文本。
     * 默认为 true。
     */
    virtual bool isEditable() const;

    /**
     * 返回文本区域中一行过长时是否自动换行。
     * 默认为 true。
     */
    virtual bool isLineWrap() const;

    /**
     * 将文本区域的键盘光标位置设置到以下内容末尾
     * 当前文本。
     */
    virtual void moveCursorToEnd();

    /**
     * 将文本区域的键盘光标位置设置到以下内容开头
     * 当前文本。
     */
    virtual void moveCursorToStart();

    /**
     * 从此文本区域删除文本变化监听器，使其不再
     * 用户修改文本时调用它。
     */
    virtual void removeTextChangeListener();

    /**
     * 移动文本区域的可见滚动区域，使底部部分
     * 文本中可见的部分。
     */
    virtual void scrollToBottom();

    /**
     * 移动文本区域的可见滚动区域，使顶部部分
     * 文本中可见的部分。
     */
    virtual void scrollToTop();

    /**
     * 将给定文本范围设为选中，从给定起始位置开始
     * index 是整个文本字符串中从 0 开始的字符索引，并且
     * 从该位置开始延伸给定字符长度。
     * @throw 如果起始索引或长度为负，则抛出 ErrorException
     */
    virtual void select(int startIndex, int length);

    /**
     * 选择文本区域的全部文本。
     */
    virtual void selectAll();

    /**
     * 设置文本区域宽度，使其足以容纳给定数量的
     * 文本字符数（列数）。
     * @throw 如果 columns 值为负数，则抛出 ErrorException
     */
    virtual void setColumns(int columns);

    /**
     * 设置用户右键单击以下对象时是否弹出上下文菜单
     * 文本区域。
     * 初始为 true。
     */
    virtual void setContextMenuEnabled(bool enabled);

    /**
     * 将键盘光标移动到其中给定的从 0 开始的字符索引处
     * 该文本。
     * @throw 如果 index 为负，则抛出 ErrorException
     */
    virtual void setCursorPosition(int index, bool keepAnchor = false);

    /**
     * 设置文本区域是否允许用户修改其文本。
     * 默认为 true。
     */
    virtual void setEditable(bool value);

    /**
     * 将文本区域的当前文本设为给定 HTML 字符串。
     * 它与 setText 的区别是会应用 HTML 标签和格式
     * 视为文本的一部分，而不是普通字符。
     */
    virtual void setHtml(const std::string& html);

    /**
     * 设置文本区域中一行过长时是否自动换行。
     * 默认为 true。
     */
    virtual void setLineWrap(bool wrap);

    /**
     * 在此文本区域上设置鼠标监听器，以便在以下情况发生时调用它
     * 当用户移动或单击鼠标时。
     * 任何现有的鼠标监听器都会被替换。
     */
    void setMouseListener(GEventListener func) override;

    /**
     * 在此文本区域上设置鼠标监听器，以便在以下情况发生时调用它
     * 当用户移动或单击鼠标时。
     * 任何现有的鼠标监听器都会被替换。
     */
    void setMouseListener(GEventListenerVoid func) override;

    /**
     * 设置文本区域的占位文本，通常显示在
     * 当文本区域为空时，以浅灰色文字显示。
     * 这通常是向用户提示应输入什么值。
     * 默认初始占位符为空。
     */
    virtual void setPlaceholder(const std::string& text);

    /**
     * 设置文本区域高度，使其足以容纳给定数量的
     * 文本行数（行）。
     * @throw 如果 rows 值为负数，则抛出 ErrorException
     */
    virtual void setRows(int rows);

    /**
     * 设置文本区域大小，使其宽度足以容纳给定数量的
     * 文本行数（行）和字符数（列）。
     * @throw 如果 rows 或 columns 为负，则抛出 ErrorException
     */
    virtual void setRowsColumns(int rows, int columns);

    /**
     * 将文本区域的当前文本设为给定字符串，
     * 替换任何现有文本。
     */
    virtual void setText(const std::string& text);

    /**
     * 在此文本区域上设置文本更改监听器，以便在以下情况发生时调用它
     * 当用户修改当前文本时。
     * 任何现有的文本更改监听器都会被替换。
     *
     * 文本更改监听器与按键监听器类似，二者都会
     * 当用户在文本区输入字符时触发事件。
     * 但按键监听器会在按下任意键时触发，即使该键
     * 但并不修改文本本身，例如用户按下方向键时
     * 或 Ctrl 键、Esc 键及任何其他特殊字符。
     *
     * 文本更改监听器仅在实际文本发生变化时触发，例如
     * 例如用户在文本区中输入新字符时。
     */
    virtual void setTextChangeListener(GEventListener func);

    /**
     * 在此文本区域上设置文本更改监听器，以便在以下情况发生时调用它
     * 当用户修改当前文本时。
     * 任何现有的文本更改监听器都会被替换。
     *
     * 文本更改监听器与按键监听器类似，二者都会
     * 当用户在文本区输入字符时触发事件。
     * 但按键监听器会在按下任意键时触发，即使该键
     * 但并不修改文本本身，例如用户按下方向键时
     * 或 Ctrl 键、Esc 键及任何其他特殊字符。
     *
     * 文本更改监听器仅在实际文本发生变化时触发，例如
     * 例如用户在文本区中输入新字符时。
     */
    virtual void setTextChangeListener(GEventListenerVoid func);

private:
    Q_DISABLE_COPY(GTextArea)

    _Internal_QTextEdit* _iqtextedit;
    bool _contextMenuEnabled;

    // 供 getRows、getColumns 等使用的辅助函数。
    GDimension getRowColumnSize() const;

    friend class _Internal_QTextEdit;
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QTextEdit : public QTextEdit, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QTextEdit(GTextArea* gtextArea, QWidget* parent = nullptr);
    void contextMenuEvent(QContextMenuEvent* event) override;
    void detach() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    QSize sizeHint() const override;

public slots:
    void handleScroll(int value);
    void handleTextChange();

private:
    GTextArea* _gtextarea;

    friend class GTextArea;
};

#endif // _gtextarea_h
