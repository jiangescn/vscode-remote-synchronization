/*
 * 文件：gcheckbox.cpp
 * -------------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 添加按键事件支持
 * @version 2019/02/02
 * - 析构函数现在会停止事件处理
 * @version 2018/10/06
 * - 添加 toggle()
 * @version 2018/09/04
 * - 添加双击事件支持
 * @version 2018/08/23
 * - 重命名为 gcheckbox.cpp，以替代 Java 版本
 * @version 2018/06/25
 * - 初始版本
 */

#include "gcheckbox.h"
#include "gthread.h"
#include "gwindow.h"
#include "require.h"

GCheckBox::GCheckBox(const std::string& text, bool checked, QWidget* parent) {
    GThread::runOnQtGuiThread([this, checked, parent]() {
        _iqcheckBox = new _Internal_QCheckBox(this, checked, getInternalParent(parent));
    });
    setText(text);
    setVisible(false);   // 所有控件在添加到窗口之前都不会显示
}

GCheckBox::~GCheckBox() {
    // TODO：delete _iqcheckBox;
    _iqcheckBox->detach();
    _iqcheckBox = nullptr;
}

std::string GCheckBox::getActionCommand() const {
    if (_actionCommand.empty()) {
        return getText();
    } else {
        return _actionCommand;
    }
}

std::string GCheckBox::getActionEventType() const {
    return "change";
}

_Internal_QWidget* GCheckBox::getInternalWidget() const {
    return _iqcheckBox;
}

std::string GCheckBox::getText() const {
    return _iqcheckBox->text().toStdString();
}

std::string GCheckBox::getType() const {
    return "GCheckBox";
}

QWidget* GCheckBox::getWidget() const {
    return static_cast<QWidget*>(_iqcheckBox);
}

bool GCheckBox::isChecked() const {
    return _iqcheckBox->isChecked();
}

bool GCheckBox::isSelected() const {
    return _iqcheckBox->isChecked();
}

void GCheckBox::setChecked(bool checked) {
    GThread::runOnQtGuiThread([this, checked]() {
        _iqcheckBox->setChecked(checked);
    });
}

void GCheckBox::setSelected(bool selected) {
    setChecked(selected);
}

void GCheckBox::setText(const std::string& text) {
    GThread::runOnQtGuiThread([this, text]() {
        _iqcheckBox->setText(QString::fromStdString(text));
    });
}

void GCheckBox::toggle() {
    setChecked(!isChecked());
}


_Internal_QCheckBox::_Internal_QCheckBox(GCheckBox* gcheckBox, bool checked, QWidget* parent)
        : QCheckBox(parent),
          _gcheckBox(gcheckBox) {
    require::nonNull(gcheckBox, "_Internal_QCheckBox::constructor");
    setObjectName(QString::fromStdString("_Internal_QCheckBox_" + std::to_string(gcheckBox->getID())));
    setChecked(checked);
    connect(this, SIGNAL(stateChanged(int)), this, SLOT(handleStateChange(int)));
}

void _Internal_QCheckBox::detach() {
    _gcheckBox = nullptr;
}

void _Internal_QCheckBox::handleStateChange(int /* 状态 */) {
    if (!_gcheckBox) {
        return;
    }
    GEvent changeEvent(
                /* 类  */ CHANGE_EVENT,
                /* 类型   */ STATE_CHANGED,
                /* 名称   */ "change",
                /* 来源 */ _gcheckBox);
    changeEvent.setActionCommand(_gcheckBox->getActionCommand());
    _gcheckBox->fireEvent(changeEvent);
}

void _Internal_QCheckBox::keyPressEvent(QKeyEvent* event) {
    require::nonNull(event, "_Internal_QCheckBox::keyPressEvent", "event");
    if (_gcheckBox && _gcheckBox->isAcceptingEvent("keypress")) {
        event->accept();
        _gcheckBox->fireGEvent(event, KEY_PRESSED, "keypress");
        if (event->isAccepted()) {
            QCheckBox::keyPressEvent(event);   // 调用父类实现
        }
    } else {
        QCheckBox::keyPressEvent(event);   // 调用父类实现
    }
}

void _Internal_QCheckBox::keyReleaseEvent(QKeyEvent* event) {
    require::nonNull(event, "_Internal_QCheckBox::keyReleaseEvent", "event");
    if (_gcheckBox && _gcheckBox->isAcceptingEvent("keyrelease")) {
        event->accept();
        _gcheckBox->fireGEvent(event, KEY_RELEASED, "keyrelease");
        if (event->isAccepted()) {
            QCheckBox::keyReleaseEvent(event);   // 调用父类实现
        }
    } else {
        QCheckBox::keyReleaseEvent(event);   // 调用父类实现
    }
}

void _Internal_QCheckBox::mouseDoubleClickEvent(QMouseEvent* event) {
    require::nonNull(event, "_Internal_QCheckBox::mouseDoubleClickEvent");
    QWidget::mouseDoubleClickEvent(event);   // 调用父类实现
    emit doubleClicked();

    if (!_gcheckBox || !_gcheckBox->isAcceptingEvent("doubleclick")) {
        return;
    }
    GEvent mouseEvent(
                /* 类  */ MOUSE_EVENT,
                /* 类型   */ MOUSE_DOUBLE_CLICKED,
                /* 名称   */ "doubleclick",
                /* 来源 */ _gcheckBox);
    mouseEvent.setActionCommand(_gcheckBox->getActionCommand());
    mouseEvent.setButton((int) event->button());
    mouseEvent.setX(event->pos().x());
    mouseEvent.setY(event->pos().y());
    _gcheckBox->fireEvent(mouseEvent);
}

QSize _Internal_QCheckBox::sizeHint() const {
    if (hasPreferredSize()) {
        return getPreferredSize();
    } else {
        return QCheckBox::sizeHint();
    }
}


