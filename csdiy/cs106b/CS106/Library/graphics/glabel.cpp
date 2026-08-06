/*
 * 文件：glabel.cpp
 * ----------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 将部分事件处理代码移到 GInteractor 父类
 * @version 2019/04/22
 * - 添加接受 QIcon 和 QPixmap 的 setIcon
 * @version 2019/02/02
 * - 析构函数现在会停止事件处理
 * @version 2018/10/04
 * - 添加 get/setWordWrap
 * @version 2018/09/04
 * - 添加双击事件支持
 * @version 2018/09/03
 * - 为可单击标签添加 addActionListener 方法
 * @version 2018/08/23
 * - 重命名为 glabel.cpp，以替代 Java 版本
 * @version 2018/06/25
 * - 初始版本
 */

#include "glabel.h"
#include <iostream>
#include "filelib.h"
#include "glayout.h"
#include "gthread.h"
#include "gwindow.h"
#include "require.h"

GLabel::GLabel(const std::string& text, const std::string& iconFileName, QWidget* parent)
        : _gtext(nullptr) {
    GThread::runOnQtGuiThread([this, parent]() {
        _iqlabel = new _Internal_QLabel(this, getInternalParent(parent));
    });
    setText(text);
    if (!iconFileName.empty()) {
        setIcon(iconFileName);
    }
    setVisible(false);   // 所有控件在添加到窗口之前都不会显示
}

GLabel::GLabel(const std::string& text, const QIcon& icon, QWidget* parent)
        : _gtext(nullptr) {
    GThread::runOnQtGuiThread([this, parent]() {
        _iqlabel = new _Internal_QLabel(this, getInternalParent(parent));
    });
    setText(text);
    setIcon(icon);
    setVisible(false);   // 所有控件在添加到窗口之前都不会显示
}

GLabel::GLabel(const std::string& text, const QPixmap& icon, QWidget* parent)
        : _gtext(nullptr) {
    GThread::runOnQtGuiThread([this, parent]() {
        _iqlabel = new _Internal_QLabel(this, getInternalParent(parent));
    });
    setText(text);
    setIcon(icon);
    setVisible(false);   // 所有控件在添加到窗口之前都不会显示
}

GLabel::~GLabel() {
    // TODO：if (_gtext) { delete _gtext; }
    // TODO：delete _iqlabel;
    _iqlabel->detach();
    _iqlabel = nullptr;
}

void GLabel::ensureGText() {
    _gtext = new GText(getText());
    _gtext->setColor(getColor());
    _gtext->setFont(getFont());
}

GText* GLabel::getGText() const {
    return _gtext;
}

_Internal_QWidget* GLabel::getInternalWidget() const {
    return _iqlabel;
}

std::string GLabel::getLabel() const {
    return getText();
}

std::string GLabel::getText() const {
    return _iqlabel->text().toStdString();
}

GInteractor::TextPosition GLabel::getTextPosition() const {
    // TODO（待办）
//    switch (_iqlabel->toolButtonStyle()) {
//    case Qt::ToolButtonTextBesideIcon:
//        return GInteractor::TEXT_BESIDE_ICON;
//    case Qt::ToolButtonTextUnderIcon:
//        return GInteractor::TEXT_UNDER_ICON;
//    case Qt::ToolButtonTextOnly:
//    默认：
//        return GInteractor::TEXT_ONLY;
//    }

    return GInteractor::TEXT_BESIDE_ICON;
}

std::string GLabel::getType() const {
    return "GLabel";
}

QWidget* GLabel::getWidget() const {
    return static_cast<QWidget*>(_iqlabel);
}

bool GLabel::hasGText() const {
    return _gtext != nullptr;
}

bool GLabel::isWordWrap() const {
    return _iqlabel->wordWrap();
}

void GLabel::setBounds(double x, double y, double width, double height) {
    if (_gtext) {
        _gtext->setBounds(x, y, width, height);
    }
    GInteractor::setBounds(x, y, width, height);
}

void GLabel::setBounds(const GRectangle& size) {
    if (_gtext) {
        _gtext->setBounds(size);
    }
    GInteractor::setBounds(size);
}

void GLabel::setColor(int rgb) {
    if (_gtext) {
        _gtext->setColor(rgb);
    }
    GInteractor::setColor(rgb);   // 调用父类实现
}

void GLabel::setColor(const std::string& color) {
    if (_gtext) {
        _gtext->setColor(color);
    }
    GInteractor::setColor(color);   // 调用父类实现
}

void GLabel::setFont(const QFont& font) {
    if (_gtext) {
        _gtext->setFont(font);
    }
    GInteractor::setFont(font);   // 调用父类实现
}

void GLabel::setFont(const std::string& font) {
    if (_gtext) {
        _gtext->setFont(font);
    }
    GInteractor::setFont(font);   // 调用父类实现
}

void GLabel::setForeground(int rgb) {
    if (_gtext) {
        _gtext->setForeground(rgb);
    }
    GInteractor::setForeground(rgb);   // 调用父类实现
}

void GLabel::setForeground(const std::string& color) {
    if (_gtext) {
        _gtext->setForeground(color);
    }
    GInteractor::setForeground(color);   // 调用父类实现
}

void GLabel::setHeight(double height) {
    ensureGText();   // 设置大小会触发 GText 模式
    _gtext->setHeight(height);
    GInteractor::setHeight(height);
}

void GLabel::setIcon(const QIcon& icon) {
    GInteractor::setIcon(icon);
    GThread::runOnQtGuiThread([this, &icon]() {
        QSize size(16, 16);   // 默认大小
        if (!icon.availableSizes().empty()) {
            size = icon.availableSizes()[0];
        }
        QPixmap pixmap = icon.pixmap(size);
        _iqlabel->setPixmap(pixmap);
        _iqlabel->updateGeometry();
        _iqlabel->update();

        // TODO：会丢失文本；怎样让同一个标签同时拥有图标和文本？
        if (!getText().empty()) {
            std::cerr << "Warning: a GLabel cannot currently have both text and icon." << std::endl;
        }
    });
}

void GLabel::setIcon(const QPixmap& icon) {
    GInteractor::setIcon(icon);
    GThread::runOnQtGuiThread([this, &icon]() {
        _iqlabel->setPixmap(icon);
        _iqlabel->updateGeometry();
        _iqlabel->update();

        // TODO：会丢失文本；怎样让同一个标签同时拥有图标和文本？
        if (!getText().empty()) {
            std::cerr << "Warning: a GLabel cannot currently have both text and icon." << std::endl;
        }
    });
}

void GLabel::setIcon(const std::string& filename, bool retainIconSize) {
    GInteractor::setIcon(filename, retainIconSize);
    if (!filename.empty() && fileExists(filename)) {
        GThread::runOnQtGuiThread([this, filename, retainIconSize]() {
            if (filename.empty()) {
                _iqlabel->setPixmap(QPixmap());
            } else {
                QPixmap pixmap(QString::fromStdString(filename));
                _iqlabel->setPixmap(pixmap);
                if (retainIconSize) {
                    // TODO（待办）
                    // _iqlabel->setIconSize(pixmap.size());
                    _iqlabel->updateGeometry();
                    _iqlabel->update();
                }

                // TODO：会丢失文本；怎样让同一个标签同时拥有图标和文本？
                if (!getText().empty()) {
                    std::cerr << "Warning: a GLabel cannot currently have both text and icon." << std::endl;
                }
            }
        });
    }
}

void GLabel::setLabel(const std::string& text) {
    setText(text);
}

void GLabel::setLocation(double x, double y) {
    ensureGText();   // 设置位置会触发 GText 模式
    _gtext->setLocation(x, y);
    GInteractor::setLocation(x, y);
}

void GLabel::setSize(double width, double height) {
    ensureGText();   // 设置大小会触发 GText 模式
    _gtext->setSize(width, height);
    GInteractor::setSize(width, height);
}

void GLabel::setSize(const GDimension& size) {
    ensureGText();   // 设置大小会触发 GText 模式
    _gtext->setSize(size);
    GInteractor::setSize(size);
}

void GLabel::setText(const std::string& text) {
    if (_gtext) {
        _gtext->setText(text);
    }
    GThread::runOnQtGuiThread([this, text]() {
        _iqlabel->setText(QString::fromStdString(text));
        GLayout::forceUpdate(_iqlabel);
    });
}

void GLabel::setTextPosition(GInteractor::TextPosition position) {
    // TODO：这实际上不起作用，因为 Qt 中的标签无法同时包含文本和图标
    if (position == GInteractor::TEXT_UNDER_ICON) {
        // _iqpushbutton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    } else if (position == GInteractor::TEXT_BESIDE_ICON) {
        // _iqpushbutton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    } else if (position == GInteractor::TEXT_ONLY) {
        // _iqpushbutton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    }
}

void GLabel::setVisible(bool visible) {
    if (_gtext) {
        _gtext->setVisible(visible);
    }
    GInteractor::setVisible(visible);   // 调用父类实现
}

void GLabel::setWidth(double width) {
    ensureGText();   // 设置大小会触发 GText 模式
    _gtext->setWidth(width);
    GInteractor::setWidth(width);
}

void GLabel::setWordWrap(bool wrap) {
    GThread::runOnQtGuiThread([this, wrap]() {
        _iqlabel->setWordWrap(wrap);
    });
}

void GLabel::setX(double x) {
    ensureGText();   // 设置位置会触发 GText 模式
    _gtext->setX(x);
    GInteractor::setX(x);
}

void GLabel::setY(double y) {
    ensureGText();   // 设置位置会触发 GText 模式
    _gtext->setY(y);
    GInteractor::setY(y);
}


_Internal_QLabel::_Internal_QLabel(GLabel* glabel, QWidget* parent)
        : QLabel(parent),
          _glabel(glabel) {
    require::nonNull(glabel, "_Internal_QLabel::constructor");
    setObjectName(QString::fromStdString("_Internal_QLabel_" + std::to_string(glabel->getID())));
}

void _Internal_QLabel::detach() {
    _glabel = nullptr;
}

void _Internal_QLabel::mouseDoubleClickEvent(QMouseEvent* event) {
    require::nonNull(event, "_Internal_QLabel::mouseDoubleClickEvent", "event");
    QWidget::mouseDoubleClickEvent(event);   // 调用父类实现
    if (!_glabel) {
        return;
    }
    emit doubleClicked();
    if (!_glabel->isAcceptingEvent("doubleclick")) {
        return;
    }
    GEvent mouseEvent(
                /* 类  */ MOUSE_EVENT,
                /* 类型   */ MOUSE_DOUBLE_CLICKED,
                /* 名称   */ "doubleclick",
                /* 来源 */ _glabel);
    mouseEvent.setActionCommand(_glabel->getActionCommand());
    mouseEvent.setButton((int) event->button());
    mouseEvent.setX(event->pos().x());
    mouseEvent.setY(event->pos().y());
    _glabel->fireEvent(mouseEvent);
}

void _Internal_QLabel::mousePressEvent(QMouseEvent* event) {
    require::nonNull(event, "_Internal_QLabel::mousePressEvent", "event");
    QWidget::mousePressEvent(event);   // 调用父类实现
    if (!_glabel) {
        return;
    }

    // 仅对左键单击触发信号/事件
    if (!(event->button() & Qt::LeftButton)) {
        return;
    }

    emit clicked();

    if (!_glabel->isAcceptingEvent("click")) {
        return;
    }

    GEvent actionEvent(
                /* 类  */ ACTION_EVENT,
                /* 类型   */ ACTION_PERFORMED,
                /* 名称   */ "click",
                /* 来源 */ _glabel);
    actionEvent.setActionCommand(_glabel->getActionCommand());
    actionEvent.setButton((int) event->button());
    actionEvent.setX(event->pos().x());
    actionEvent.setY(event->pos().y());
    _glabel->fireEvent(actionEvent);
}

QSize _Internal_QLabel::sizeHint() const {
    if (hasPreferredSize()) {
        return getPreferredSize();
    } else {
        return QLabel::sizeHint();
    }
}


