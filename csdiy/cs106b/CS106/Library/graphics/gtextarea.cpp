/*
 * 文件：gtextarea.cpp
 * -------------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 将部分事件监听代码移到 GInteractor 父类
 * @version 2019/02/02
 * - 析构函数现在会停止事件处理
 * @version 2018/08/23
 * - 重命名为 gtextarea.cpp，以替代 Java 版本
 * @version 2018/06/25
 * - 初始版本
 */

#include "gtextarea.h"
#include <QScrollBar>
#include <QTextCursor>
#include "gcolor.h"
#include "gfont.h"
#include "gthread.h"
#include "gwindow.h"
#include "require.h"

GTextArea::GTextArea(int rows, int columns, QWidget* parent)
        : _contextMenuEnabled(true) {
    GThread::runOnQtGuiThread([this, parent]() {
        _iqtextedit = new _Internal_QTextEdit(this, getInternalParent(parent));
    });
    setRowsColumns(rows, columns);
    setVisible(false);   // 所有控件在添加到窗口之前都不会显示
}

GTextArea::GTextArea(const std::string& text, QWidget* parent)
        : _contextMenuEnabled(true) {
    GThread::runOnQtGuiThread([this, parent]() {
        _iqtextedit = new _Internal_QTextEdit(this, getInternalParent(parent));
    });
    setText(text);
    setVisible(false);   // 所有控件在添加到窗口之前都不会显示
}

GTextArea::~GTextArea() {
    // TODO：delete _iqtextedit;
    _iqtextedit->detach();
    _iqtextedit = nullptr;
}

void GTextArea::appendFormattedText(const std::string& text, const std::string& color, const std::string& font) {
    moveCursorToEnd();

    // 使用字体和颜色创建格式化块
    QTextCharFormat format;
    if (!color.empty()) {
        format.setForeground(QBrush(GColor::convertColorToRGB(color)));
    }
    if (!font.empty()) {
        // 只保留字体粗细，不保留大小/字体族
        QFont qfont = GFont::toQFont(_iqtextedit->font(), font);
        format.setFontWeight(qfont.weight());
    }

    QTextCursor cursor = _iqtextedit->textCursor();
    cursor.beginEditBlock();
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor, 1);
    cursor.insertText(QString::fromStdString(text), format);
    cursor.endEditBlock();
    GThread::runOnQtGuiThread([this, cursor]() {
        _iqtextedit->setTextCursor(cursor);
        _iqtextedit->ensureCursorVisible();
    });

    moveCursorToEnd();
}

void GTextArea::appendHtml(const std::string& html) {
    // TODO：为提高速度使用 insertHtml？
    setHtml(getHtml() + html);
}

void GTextArea::appendText(const std::string& text) {
    QTextCursor cursor = _iqtextedit->textCursor();
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor, 1);
    cursor.insertText(QString::fromStdString(text));
    moveCursorToEnd();
}

void GTextArea::clearSelection() {
    GThread::runOnQtGuiThread([this]() {
        QTextCursor cursor = _iqtextedit->textCursor();
        cursor.clearSelection();
        _iqtextedit->setTextCursor(cursor);
    });
}

void GTextArea::clearText() {
    GThread::runOnQtGuiThread([this]() {
        _iqtextedit->clear();
    });
}

int GTextArea::getColumns() const {
    return (int) (getHeight() / getRowColumnSize().width);
}

int GTextArea::getCursorPosition() const {
    return _iqtextedit->textCursor().position();
}

std::string GTextArea::getHtml() const {
    return _iqtextedit->toHtml().toStdString();
}

_Internal_QWidget* GTextArea::getInternalWidget() const {
    return _iqtextedit;
}

std::string GTextArea::getPlaceholder() const {
    return _iqtextedit->placeholderText().toStdString();
}

GDimension GTextArea::getRowColumnSize() const {
    QFontMetrics metrics(_iqtextedit->font());
    return GDimension(metrics.horizontalAdvance(QString::fromStdString("mmmmmmmmmm")) / 10.0, metrics.lineSpacing() + 2);
}

int GTextArea::getRows() const {
    return (int) (getHeight() / getRowColumnSize().height);
}

std::string GTextArea::getSelectedText() const {
    QTextCursor cursor = _iqtextedit->textCursor();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    if (end > start) {
        return getText().substr(start, end - start);
    } else {
        return "";
    }
}

int GTextArea::getSelectionEnd() const {
    QTextCursor cursor = _iqtextedit->textCursor();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    if (end > start) {
        return end;
    } else {
        // 没有选区；光标使选区起点和终点相等
        return -1;
    }
}

int GTextArea::getSelectionLength() const {
    QTextCursor cursor = _iqtextedit->textCursor();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    return end - start;
}

int GTextArea::getSelectionStart() const {
    QTextCursor cursor = _iqtextedit->textCursor();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    if (end > start) {
        return start;
    } else {
        return -1;
    }
}

std::string GTextArea::getText() const {
    return _iqtextedit->toPlainText().toStdString();
}

std::string GTextArea::getType() const {
    return "GTextArea";
}

QWidget* GTextArea::getWidget() const {
    return static_cast<QWidget*>(_iqtextedit);
}

bool GTextArea::isContextMenuEnabled() const {
    return _contextMenuEnabled;
}

bool GTextArea::isEditable() const {
    return !_iqtextedit->isReadOnly();
}

bool GTextArea::isLineWrap() const {
    return _iqtextedit->lineWrapMode() != QTextEdit::NoWrap;
}

void GTextArea::moveCursorToEnd() {
    GThread::runOnQtGuiThread([this]() {
        QTextCursor cursor = _iqtextedit->textCursor();
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor, 1);
        _iqtextedit->setTextCursor(cursor);
        _iqtextedit->ensureCursorVisible();
    });
}

void GTextArea::moveCursorToStart() {
    GThread::runOnQtGuiThread([this]() {
        QTextCursor cursor = _iqtextedit->textCursor();
        cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
        _iqtextedit->setTextCursor(cursor);
        _iqtextedit->ensureCursorVisible();
    });
}

void GTextArea::removeTextChangeListener() {
    removeEventListener("textchange");
}

void GTextArea::scrollToBottom() {
    GThread::runOnQtGuiThread([this]() {
        QScrollBar* scrollbar = _iqtextedit->verticalScrollBar();
        scrollbar->setValue(scrollbar->maximum());
        scrollbar->setSliderPosition(scrollbar->maximum());
    });
}

void GTextArea::scrollToTop() {
    GThread::runOnQtGuiThread([this]() {
        QScrollBar* scrollbar = _iqtextedit->verticalScrollBar();
        scrollbar->setValue(0);
        scrollbar->setSliderPosition(0);
    });
}

void GTextArea::select(int startIndex, int length) {
    require::nonNegative(startIndex, 0, "GTextArea::select", "startIndex");
    require::nonNegative(length, 0, "GTextArea::select", "length");
    GThread::runOnQtGuiThread([this, startIndex, length]() {
        QTextCursor cursor = _iqtextedit->textCursor();
        cursor.setPosition(startIndex);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, length);
        _iqtextedit->setTextCursor(cursor);
    });
}

void GTextArea::selectAll() {
    GThread::runOnQtGuiThread([this]() {
        _iqtextedit->selectAll();
    });
}

void GTextArea::setColumns(int columns) {
    require::nonNegative(columns, "GTextArea::setColumns");
    double desiredWidth = getRowColumnSize().width * columns;
    setPreferredSize(desiredWidth, getHeight());
    setSize(desiredWidth, getHeight());
}

void GTextArea::setContextMenuEnabled(bool enabled) {
    _contextMenuEnabled = enabled;
}

void GTextArea::setCursorPosition(int index, bool keepAnchor) {
    require::nonNegative(index, "TextArea::setCursorPosition", "index");
    GThread::runOnQtGuiThread([this, index, keepAnchor]() {
        QTextCursor cursor(_iqtextedit->textCursor());
        cursor.setPosition(index, keepAnchor ? QTextCursor::KeepAnchor : QTextCursor::MoveAnchor);
        _iqtextedit->setTextCursor(cursor);
        _iqtextedit->ensureCursorVisible();
    });
}

void GTextArea::setEditable(bool value) {
    GThread::runOnQtGuiThread([this, value]() {
        _iqtextedit->setReadOnly(!value);
    });
}

void GTextArea::setHtml(const std::string& html) {
    GThread::runOnQtGuiThread([this, html]() {
        _iqtextedit->setHtml(QString::fromStdString(html));
    });
}

void GTextArea::setLineWrap(bool wrap) {
    GThread::runOnQtGuiThread([this, wrap]() {
        _iqtextedit->setLineWrapMode(wrap ? QTextEdit::WidgetWidth : QTextEdit::NoWrap);
    });
}

void GTextArea::setMouseListener(GEventListener func) {
    setEventListeners({"mousepress",
                       "mouserelease"}, func);
}

void GTextArea::setMouseListener(GEventListenerVoid func) {
    setEventListeners({"mousepress",
                       "mouserelease"}, func);
}

void GTextArea::setPlaceholder(const std::string& text) {
    GThread::runOnQtGuiThread([this, text]() {
        _iqtextedit->setPlaceholderText(QString::fromStdString(text));
    });
}

void GTextArea::setRows(int rows) {
    require::nonNegative(rows, "GTextArea::setRows");
    double desiredHeight = getRowColumnSize().height * rows;
    setPreferredSize(getWidth(), desiredHeight);
    setSize(getWidth(), desiredHeight);
}

void GTextArea::setRowsColumns(int rows, int columns) {
    require::nonNegative2D(rows, columns, "GTextArea::setRowsColumns", "rows", "columns");
    double desiredWidth = getRowColumnSize().width * columns;
    double desiredHeight = getRowColumnSize().height * rows;
    setPreferredSize(desiredWidth, desiredHeight);
    setSize(desiredWidth, desiredHeight);
}

void GTextArea::setText(const std::string& text) {
    GThread::runOnQtGuiThread([this, text]() {
        _iqtextedit->setText(QString::fromStdString(text));
    });
}

void GTextArea::setTextChangeListener(GEventListener func) {
    setEventListener("textchange", func);
}

void GTextArea::setTextChangeListener(GEventListenerVoid func) {
    setEventListener("textchange", func);
}


_Internal_QTextEdit::_Internal_QTextEdit(GTextArea* gtextArea, QWidget* parent)
        : QTextEdit(parent),
          _gtextarea(gtextArea) {
    require::nonNull(gtextArea, "_Internal_QTextEdit::constructor");
    setObjectName(QString::fromStdString("_Internal_QTextEdit_" + std::to_string(gtextArea->getID())));
    ensureCursorVisible();
    setFocusPolicy(Qt::StrongFocus);
    setTabChangesFocus(false);
    document()->setUndoRedoEnabled(false);
    connect(this, SIGNAL(textChanged()), this, SLOT(handleTextChange()));
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(handleScroll(int)));
}

void _Internal_QTextEdit::contextMenuEvent(QContextMenuEvent* event) {
    if (!_gtextarea) {
        QTextEdit::contextMenuEvent(event);   // 调用父类实现
        return;
    }
    if (_gtextarea->isContextMenuEnabled()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void _Internal_QTextEdit::detach() {
    _gtextarea = nullptr;
}

void _Internal_QTextEdit::handleScroll(int value) {
    if (_gtextarea && _gtextarea->isAcceptingEvent("scroll")) {
        GEvent scrollEvent(
                    /* 类  */ SCROLL_EVENT,
                    /* 类型   */ SCROLL_SCROLLED,
                    /* 名称   */ "scroll",
                    /* 来源 */ _gtextarea);
        scrollEvent.setActionCommand(_gtextarea->getActionCommand());
        scrollEvent.setY(value);   // 近似值
        _gtextarea->fireEvent(scrollEvent);
    }
}

void _Internal_QTextEdit::handleTextChange() {
    if (_gtextarea && _gtextarea->isAcceptingEvent("textchange")) {
        GEvent textChangeEvent(
                    /* 类  */ KEY_EVENT,
                    /* 类型   */ KEY_TYPED,
                    /* 名称   */ "textchange",
                    /* 来源 */ _gtextarea);
        textChangeEvent.setActionCommand(_gtextarea->getActionCommand());
        _gtextarea->fireEvent(textChangeEvent);

        // 错误修复：为向后兼容，同时触发 CHANGE_EVENT
        // （仅发送给旧式 waitForEvent 函数）
        GEvent changeEvent(
                    /* 类  */ CHANGE_EVENT,
                    /* 类型   */ STATE_CHANGED,
                    /* 名称   */ "statechange",
                    /* 来源 */ _gtextarea);
        changeEvent.setActionCommand(_gtextarea->getActionCommand());
        _gtextarea->fireEvent(changeEvent);
    }
}

void _Internal_QTextEdit::keyPressEvent(QKeyEvent* event) {
    require::nonNull(event, "_Internal_QTextEdit::keyPressEvent", "event");
    if (_gtextarea && _gtextarea->isAcceptingEvent("keypress")) {
        event->accept();
        _gtextarea->fireGEvent(event, KEY_PRESSED, "keypress");
        if (event->isAccepted()) {
            QTextEdit::keyPressEvent(event);   // 调用父类实现
        }
    } else {
        QTextEdit::keyPressEvent(event);   // 调用父类实现
    }
}

void _Internal_QTextEdit::keyReleaseEvent(QKeyEvent* event) {
    require::nonNull(event, "_Internal_QTextEdit::keyReleaseEvent", "event");
    if (_gtextarea && _gtextarea->isAcceptingEvent("keyrelease")) {
        event->accept();
        _gtextarea->fireGEvent(event, KEY_RELEASED, "keyrelease");
        if (event->isAccepted()) {
            QTextEdit::keyReleaseEvent(event);   // 调用父类实现
        }
    } else {
        QTextEdit::keyReleaseEvent(event);   // 调用父类实现
    }
}

void _Internal_QTextEdit::mousePressEvent(QMouseEvent* event) {
    require::nonNull(event, "_Internal_QTextEdit::mousePressEvent", "event");
    if (_gtextarea && _gtextarea->isAcceptingEvent("mousepress")) {
        event->accept();
        _gtextarea->fireGEvent(event, MOUSE_PRESSED, "mousepress");
        if (event->isAccepted()) {
            QTextEdit::mousePressEvent(event);   // 调用父类实现
        }
    } else {
        QTextEdit::mousePressEvent(event);   // 调用父类实现
    }
}

void _Internal_QTextEdit::mouseReleaseEvent(QMouseEvent* event) {
    require::nonNull(event, "_Internal_QTextEdit::mouseReleaseEvent", "event");
    if (_gtextarea && _gtextarea->isAcceptingEvent("mouserelease")) {
        event->accept();
        _gtextarea->fireGEvent(event, MOUSE_RELEASED, "mouserelease");
        if (event->isAccepted()) {
            QTextEdit::mouseReleaseEvent(event);   // 调用父类实现
        }
    } else {
        QTextEdit::mouseReleaseEvent(event);   // 调用父类实现
    }
}

QSize _Internal_QTextEdit::sizeHint() const {
    if (hasPreferredSize()) {
        return getPreferredSize();
    } else {
        return QTextEdit::sizeHint();
    }
}


