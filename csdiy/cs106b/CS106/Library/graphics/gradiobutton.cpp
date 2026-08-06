/*
 * 文件：gradiobutton.cpp
 * ----------------------
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
 * - 重命名为 gradiobutton.cpp，以替代 Java 版本
 * @version 2018/06/25
 * - 初始版本
 */

#include "gradiobutton.h"
#include "gthread.h"
#include "gwindow.h"
#include "require.h"

Map<std::string, QButtonGroup*> GRadioButton::_buttonGroups;

GRadioButton::GRadioButton(const std::string& text, const std::string& group, bool checked, QWidget* parent) {
    GThread::runOnQtGuiThread([this, text, group, checked, parent]() {
        _iqradioButton = new _Internal_QRadioButton(this, checked, getInternalParent(parent));
        QButtonGroup* buttonGroup = getButtonGroup(group);
        buttonGroup->addButton(_iqradioButton);
    });
    setText(text);
    setVisible(false);   // 所有控件在添加到窗口之前都不会显示
}

GRadioButton::~GRadioButton() {
    // TODO：delete _iqradioButton;
    _iqradioButton->detach();
    _iqradioButton = nullptr;
}

std::string GRadioButton::getActionCommand() const {
    if (_actionCommand.empty()) {
        return getText();
    } else {
        return _actionCommand;
    }
}

std::string GRadioButton::getActionEventType() const {
    return "change";
}

_Internal_QWidget* GRadioButton::getInternalWidget() const {
    return _iqradioButton;
}

std::string GRadioButton::getText() const {
    return _iqradioButton->text().toStdString();
}

std::string GRadioButton::getType() const {
    return "GRadioButton";
}

QWidget* GRadioButton::getWidget() const {
    return static_cast<QWidget*>(_iqradioButton);
}

bool GRadioButton::isChecked() const {
    return _iqradioButton->isChecked();
}

bool GRadioButton::isSelected() const {
    return _iqradioButton->isChecked();
}

void GRadioButton::setChecked(bool checked) {
    GThread::runOnQtGuiThread([this, checked]() {
        _iqradioButton->setChecked(checked);
    });
}

void GRadioButton::setSelected(bool selected) {
    setChecked(selected);
}

void GRadioButton::setText(const std::string& text) {
    GThread::runOnQtGuiThread([this, text]() {
        _iqradioButton->setText(QString::fromStdString(text));
    });
}

void GRadioButton::toggle() {
    setChecked(!isChecked());
}

/* 静态 */ QButtonGroup* GRadioButton::getButtonGroup(const std::string& group) {
    if (!_buttonGroups.containsKey(group)) {
        GThread::runOnQtGuiThread([group]() {
            _buttonGroups.put(group, new QButtonGroup());
        });
    }
    return _buttonGroups[group];
}


_Internal_QRadioButton::_Internal_QRadioButton(GRadioButton* gradioButton, bool checked, QWidget* parent)
        : QRadioButton(parent),
          _gradioButton(gradioButton) {
    require::nonNull(gradioButton, "_Internal_QRadioButton::constructor");
    setObjectName(QString::fromStdString("_Internal_QRadioButton_" + std::to_string(gradioButton->getID())));
    setChecked(checked);
    // 我们处理 clicked 信号而不是 toggled，因为在单选按钮组中，
    // toggled 信号会触发两次：一次针对被单击的单选按钮，另一次
    // 用于另一个被取消选中的按钮。
    connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
}

void _Internal_QRadioButton::detach() {
    _gradioButton = nullptr;
}

void _Internal_QRadioButton::handleClick() {
    GEvent changeEvent(
                /* 类  */ CHANGE_EVENT,
                /* 类型   */ STATE_CHANGED,
                /* 名称   */ "change",
                /* 来源 */ _gradioButton);
    changeEvent.setActionCommand(_gradioButton->getActionCommand());
    _gradioButton->fireEvent(changeEvent);
}

void _Internal_QRadioButton::keyPressEvent(QKeyEvent* event) {
    require::nonNull(event, "_Internal_QRadioButton::keyPressEvent", "event");
    if (_gradioButton && _gradioButton->isAcceptingEvent("keypress")) {
        event->accept();
        _gradioButton->fireGEvent(event, KEY_PRESSED, "keypress");
        if (event->isAccepted()) {
            QRadioButton::keyPressEvent(event);   // 调用父类实现
        }
    } else {
        QRadioButton::keyPressEvent(event);   // 调用父类实现
    }
}

void _Internal_QRadioButton::keyReleaseEvent(QKeyEvent* event) {
    require::nonNull(event, "_Internal_QRadioButton::keyReleaseEvent", "event");
    if (_gradioButton && _gradioButton->isAcceptingEvent("keyrelease")) {
        event->accept();
        _gradioButton->fireGEvent(event, KEY_RELEASED, "keyrelease");
        if (event->isAccepted()) {
            QRadioButton::keyReleaseEvent(event);   // 调用父类实现
        }
    } else {
        QRadioButton::keyReleaseEvent(event);   // 调用父类实现
    }
}

void _Internal_QRadioButton::mouseDoubleClickEvent(QMouseEvent* event) {
    require::nonNull(event, "_Internal_QRadioButton::mouseDoubleClickEvent");
    QWidget::mouseDoubleClickEvent(event);   // 调用父类实现
    if (!_gradioButton) {
        return;
    }

    emit doubleClicked();
    if (!_gradioButton->isAcceptingEvent("doubleclick")) {
        return;
    }
    GEvent mouseEvent(
                /* 类  */ MOUSE_EVENT,
                /* 类型   */ MOUSE_DOUBLE_CLICKED,
                /* 名称   */ "doubleclick",
                /* 来源 */ _gradioButton);
    mouseEvent.setActionCommand(_gradioButton->getActionCommand());
    mouseEvent.setButton((int) event->button());
    mouseEvent.setX(event->pos().x());
    mouseEvent.setY(event->pos().y());
    _gradioButton->fireEvent(mouseEvent);
}

QSize _Internal_QRadioButton::sizeHint() const {
    if (hasPreferredSize()) {
        return getPreferredSize();
    } else {
        return QRadioButton::sizeHint();
    }
}


