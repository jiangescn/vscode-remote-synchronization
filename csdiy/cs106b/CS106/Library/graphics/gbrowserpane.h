/*
 * 文件：gbrowserpane.h
 * --------------------
 * 此文件声明 <code>GBrowserPane</code> 类，它是一个
 * 用于显示网页的图形交互控件。
 *
 * @version 2019/04/23
 * - 将部分事件处理代码移到 GInteractor 父类
 * @version 2018/12/28
 * - 添加文本选择、滚动、光标位置以及键盘/鼠标监听器方法
 * @version 2018/09/17
 * - 修复线程安全问题
 * - 添加链接监听事件
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gbrowserpane.h，以替代 Java 版本
 * @version 2018/07/15
 * - 初始版本
 */

#ifndef _gbrowserpane_h
#define _gbrowserpane_h

#include <string>
#include <QTextBrowser>

#include "ginteractor.h"

class _Internal_QTextBrowser;

/**
 * GBrowserPane 是显示网页的图形交互控件。
 * 此交互控件是对 Qt QTextBrowser 控件的包装，该控件
 * 能够显示 HTML 页面等富内容。
 *
 * 可以使用 GBrowserPane 实现基本
 * Web 浏览器，不过它不支持所有浏览器功能，例如
 * JavaScript 内容、安全会话或 Cookie。
 */
class GBrowserPane : public GInteractor {
public:
    /**
     * 构造新的浏览器窗格。
     * 如果传入 URL 字符串，则从该 URL 加载数据。
     * 否则，窗格初始为空白。
     */
    GBrowserPane(const std::string& url = "", QWidget* parent = nullptr);

    /**
     * 释放浏览器窗格内部分配的内存。
     */
    ~GBrowserPane() override;

    /**
     * 取消选择窗格中当前选中的任何文本。
     */
    virtual void clearSelection();

    /**
     * 将窗格中的文本设为空。
     */
    virtual void clearText();

    /**
     * 以以下形式返回文本窗格中键盘光标的当前位置
     * 整个文本字符串中的从 0 开始字符索引。
     */
    virtual int getCursorPosition() const;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回当前查看的网页 URL 或文件名。
     * 如果尚未加载页面或文件，则返回空字符串。
     */
    virtual std::string getPageUrl() const;

    /**
     * 返回文本窗格中当前选中的文本。
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
     * 返回窗格中当前显示页面或文件的完整文本。
     * 根据页面内容，这可能是一个相当长的字符串。
     * 如果尚未加载页面或文件，初始值为空字符串。
     */
    virtual std::string getText() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 返回文本窗格是否允许用户修改其文本。
     * 默认为 false。
     */
    virtual bool isEditable() const;

    /**
     * 返回文本窗格中一行过长时是否自动换行。
     * 默认为 true。
     */
    virtual bool isLineWrap() const;

    /**
     * 将文本窗格的键盘光标位置设置到以下内容末尾
     * 当前文本。
     */
    virtual void moveCursorToEnd();

    /**
     * 将文本窗格的键盘光标位置设置到以下内容开头
     * 当前文本。
     */
    virtual void moveCursorToStart();

    /**
     * 从给定文件读取文本，并将整个文件的文本显示为
     * 此格式化窗格的内容。
     * 窗格会尝试以最合适的格式显示内容，
     * 例如在保留格式的情况下渲染基本 HTML 内容。
     * 如果无法读取文件，则将窗格文本设为空。
     */
    virtual void readTextFromFile(std::istream& file);

    /**
     * 从给定文件读取文本，并将整个文件的文本显示为
     * 此格式化窗格的内容。
     * 窗格会尝试以最合适的格式显示内容，
     * 例如在保留格式的情况下渲染基本 HTML 内容。
     * 如果文件不存在或无法读取，则将窗格文本设为空。
     */
    virtual void readTextFromFile(const std::string& filename);

    /**
     * 从给定网页 URL 读取文本并显示整个页面的
     * 将文本作为此格式化窗格的内容。
     * 如果页面不存在或无法读取，则将窗格文本设为空。
     */
    virtual void readTextFromUrl(const std::string& url);

    /**
     * 从画布删除链接监听器，使其不再
     * 在发生超链接事件时调用它。
     */
    virtual void removeLinkListener();

    /**
     * 从此文本窗格删除文本变化监听器，使其不再
     * 用户修改文本时调用它。
     */
    virtual void removeTextChangeListener();

    /**
     * 移动文本窗格的可见滚动区域，使底部部分
     * 文本中可见的部分。
     */
    virtual void scrollToBottom();

    /**
     * 移动文本窗格的可见滚动区域，使顶部部分
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
     * 选择文本窗格的全部文本。
     */
    virtual void selectAll();

    /**
     * 将键盘光标移动到其中给定的从 0 开始的字符索引处
     * 该文本。
     * @throw 如果 index 为负，则抛出 ErrorException
     */
    virtual void setCursorPosition(int index, bool keepAnchor = false);

    /**
     * 设置文本窗格是否允许用户修改其文本。
     * 默认为 true。
     */
    virtual void setEditable(bool value);

    /**
     * 设置文本窗格中一行过长时是否自动换行。
     * 默认为 true。
     */
    virtual void setLineWrap(bool wrap);

    /**
     * 在此画布上设置链接监听器，以便在以下情况发生时调用它
     * 当用户单击窗格中的超链接时。
     * 任何现有的鼠标监听器都会被替换。
     */
    virtual void setLinkListener(GEventListener func);

    /**
     * 在此画布上设置链接监听器，以便在以下情况发生时调用它
     * 当用户单击窗格中的超链接时。
     * 任何现有的鼠标监听器都会被替换。
     */
    virtual void setLinkListener(GEventListenerVoid func);

    /**
     * 在此文本窗格上设置鼠标监听器，以便在以下情况发生时调用它
     * 当用户移动或单击鼠标时。
     * 任何现有的鼠标监听器都会被替换。
     */
    void setMouseListener(GEventListener func) override;

    /**
     * 在此文本窗格上设置鼠标监听器，以便在以下情况发生时调用它
     * 当用户移动或单击鼠标时。
     * 任何现有的鼠标监听器都会被替换。
     */
    void setMouseListener(GEventListenerVoid func) override;

    /**
     * 使用当前内容类型将窗格设置为显示给定内容。
     * 例如，如果你自行构建 HTML 或文本内容字符串，并希望
     * 若要在窗格中显示它而不保存到文件，应使用此方法。
     */
    virtual void setText(const std::string& text);

    /**
     * 上述版本的变体，还会在
     * 更改文本内容。
     *
     * 如果 preserve 为 true，则保留当前滚动位置，并且
     * 恢复，否则会滚动到新的底部
     */
     void setTextPreserveScroll(const std::string& text, bool preserve);

    /**
     * 在此文本窗格上设置文本更改监听器，以便在以下情况发生时调用它
     * 当用户修改当前文本时。
     * 任何现有的文本更改监听器都会被替换。
     *
     * 文本更改监听器与按键监听器类似，二者都会
     * 当用户在文本窗格输入字符时触发事件。
     * 但按键监听器会在按下任意键时触发，即使该键
     * 但并不修改文本本身，例如用户按下方向键时
     * 或 Ctrl 键、Esc 键及任何其他特殊字符。
     *
     * 文本更改监听器仅在实际文本发生变化时触发，例如
     * 例如用户在文本区中输入新字符时。
     */
    virtual void setTextChangeListener(GEventListener func);

    /**
     * 在此文本窗格上设置文本更改监听器，以便在以下情况发生时调用它
     * 当用户修改当前文本时。
     * 任何现有的文本更改监听器都会被替换。
     *
     * 文本更改监听器与按键监听器类似，二者都会
     * 当用户在文本窗格输入字符时触发事件。
     * 但按键监听器会在按下任意键时触发，即使该键
     * 但并不修改文本本身，例如用户按下方向键时
     * 或 Ctrl 键、Esc 键及任何其他特殊字符。
     *
     * 文本更改监听器仅在实际文本发生变化时触发，例如
     * 例如用户在文本区中输入新字符时。
     */
    virtual void setTextChangeListener(GEventListenerVoid func);

private:
    Q_DISABLE_COPY(GBrowserPane)

    std::string _pageUrl;   // 最近加载页面的 URL/文件名
    _Internal_QTextBrowser* _iqtextbrowser;

    friend class _Internal_QTextBrowser;
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QTextBrowser : public QTextBrowser, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QTextBrowser(GBrowserPane* gbrowserpane, QWidget* parent = nullptr);
    void detach() override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    QSize sizeHint() const override;

private:
    GBrowserPane* _gbrowserpane;
    QString _clickedLink;
};

#endif // _gbrowserpane_h
