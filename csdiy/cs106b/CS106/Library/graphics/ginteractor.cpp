/*
 * 文件：ginteractor.cpp
 * ---------------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 添加 set/removeActionListener
 * - 添加 set/removeClickListener
 * - 添加 set/removeDoubleClickListener
 * - 添加 set/removeKeyListener
 * - 添加 set/removeMouseListener
 * @version 2019/04/22
 * - 添加接受 QIcon 和 QPixmap 的 setIcon
 * @version 2019/04/10
 * - 修复 GTextArea 和 GBrowserPane 上 setBackground 的错误
 * @version 2018/09/20
 * - 修复 requestFocus 线程处理的错误
 * @version 2018/09/04
 * - 添加 get/setName、getID
 * @version 2018/08/23
 * - 重命名为 ginteractor.cpp，以替代 Java 版本
 * @version 2018/06/29
 * - 初始版本
 */

#include "ginteractor.h"
#include <iostream>
#include <sstream>
#include "gcolor.h"
#include "gfont.h"
#include "gthread.h"
#include "gwindow.h"
#include "qtgui.h"
#include "require.h"

int GInteractor::_interactorCount = 0;

GInteractor::GInteractor()
        : _actionCommand(""),
          _actionEventType("click"),
          _icon(""),
          _name(""),
          _id(-1),
          _container(nullptr),
          _lock(QReadWriteLock::Recursive) {
    QtGui::instance()->initializeQt();   // 确保 Qt 系统已初始化
    _id = ++_interactorCount;            // 将 ID 设为交互控件数量 + 1
}

GInteractor::~GInteractor() {
    // 空
}

bool GInteractor::eventsEnabled() const {
    return GObservable::eventsEnabled() && getWidget() != nullptr && isVisible();
}

std::string GInteractor::getAccelerator() const {
    // 在子类中重写
    return "";
}

std::string GInteractor::getActionCommand() const {
    return _actionCommand;
}

std::string GInteractor::getActionEventType() const {
    return _actionEventType;
}

std::string GInteractor::getBackground() const {
    int rgb = getBackgroundInt();
    return GColor::convertRGBToColor(rgb);
}

int GInteractor::getBackgroundInt() const {
    QColor color = getWidget()->palette().color(getWidget()->backgroundRole());
    return GColor::convertQColorToRGB(color);
}

GRectangle GInteractor::getBounds() const {
    return GRectangle(getX(), getY(), getWidth(), getHeight());
}

std::string GInteractor::getColor() const {
    int rgb = getColorInt();
    return GColor::convertRGBToColor(rgb);
}

int GInteractor::getColorInt() const {
    QColor color = getWidget()->palette().color(getWidget()->foregroundRole());
    return GColor::convertQColorToRGB(color);
}

GContainer* GInteractor::getContainer() const {
    return _container;
}

std::string GInteractor::getDefaultInteractorName() const {
    return getType() + "_" + std::to_string(getID());
}

std::string GInteractor::getFont() const {
    return GFont::toFontString(getWidget()->font());
}

std::string GInteractor::getForeground() const {
    int rgb = getForegroundInt();
    return GColor::convertRGBToColor(rgb);
}

int GInteractor::getForegroundInt() const {
    QColor color = getWidget()->palette().color(getWidget()->foregroundRole());
    return GColor::convertQColorToRGB(color);
}

double GInteractor::getHeight() const {
    return getWidget()->height();
}

int GInteractor::getID() const {
    return _id;
}

std::string GInteractor::getIcon() const {
    return _icon;
}

GPoint GInteractor::getLocation() const {
    return GPoint(getX(), getY());
}

/* 静态 */ QWidget* GInteractor::getInternalParent(QWidget* parent) {
    return parent ? parent : (QWidget*) GWindow::getLastWindow();
}

double GInteractor::getMinimumHeight() const {
    return getMinimumSize().height;
}

GDimension GInteractor::getMinimumSize() const {
    QSize size = getInternalWidget()->getMinimumSize();
    return GDimension(size.width(), size.height());
}

double GInteractor::getMinimumWidth() const {
    return getMinimumSize().width;
}

std::string GInteractor::getName() const {
    if (_name.empty()) {
        return getDefaultInteractorName();
    } else {
        return _name;
    }
}

double GInteractor::getPreferredHeight() const {
    return getPreferredSize().height;
}

GDimension GInteractor::getPreferredSize() const {
    QSize size;
    if (getInternalWidget()->hasPreferredSize()) {
        size = getInternalWidget()->getPreferredSize();
    } else {
        size = getWidget()->sizeHint();
    }
    return GDimension(size.width(), size.height());
}

double GInteractor::getPreferredWidth() const {
    return getPreferredSize().width;
}

GDimension GInteractor::getSize() const {
    return GDimension(getWidth(), getHeight());
}

double GInteractor::getWidth() const {
    return getWidget()->width();
}

double GInteractor::getX() const {
    return getWidget()->x();
}

double GInteractor::getY() const {
    return getWidget()->y();
}

bool GInteractor::inBounds(double x, double y) const {
    return 0 <= x && x < getWidth() && 0 <= y && y < getHeight();
}

bool GInteractor::inBounds(int x, int y) const {
    return 0 <= x && x < (int) getWidth() && 0 <= y && y < (int) getHeight();
}

bool GInteractor::isEnabled() const {
    return getWidget()->isEnabled();
}

bool GInteractor::isVisible() const {
    return getWidget()->isVisible();
}

void GInteractor::lockForRead() {
    _lock.lockForRead();
}

void GInteractor::lockForReadConst() const {
    GInteractor* that = const_cast<GInteractor*>(this);
    that->lockForRead();
}

void GInteractor::lockForWrite() {
    _lock.lockForWrite();
}

void GInteractor::lockForWriteConst() const {
    GInteractor* that = const_cast<GInteractor*>(this);
    that->lockForWrite();
}

std::string GInteractor::normalizeAccelerator(const std::string& accelerator) {
    std::string acceleratorStr = stringReplace(accelerator, "Alt-", "Alt+");
    acceleratorStr = stringReplace(acceleratorStr, "Command-", "Command+");
    acceleratorStr = stringReplace(acceleratorStr, "Ctrl-", "Ctrl+");
    acceleratorStr = stringReplace(acceleratorStr, "Meta-", "Meta+");
    acceleratorStr = stringReplace(acceleratorStr, "Shift-", "Shift+");
    return acceleratorStr;
}

void GInteractor::removeActionListener() {
    removeEventListener(getActionEventType());
}

void GInteractor::removeClickListener() {
    removeEventListener("click");
}

void GInteractor::removeDoubleClickListener() {
    removeEventListener("doubleclick");
}

void GInteractor::removeKeyListener() {
    removeEventListeners({"keypress",
                         "keyrelease",
                         "keytype"});
}

void GInteractor::removeMouseListener() {
    removeEventListeners({"click",
                         "mousedrag",
                         "mouseenter",
                         "mouseexit",
                         "mousemove",
                         "mousepress",
                         "mouserelease",
                         "mousewheeldown",
                         "mousewheelup"});
}

void GInteractor::requestFocus() {
    GThread::runOnQtGuiThread([this]() {
        getWidget()->setFocus();
    });
}

void GInteractor::setActionCommand(const std::string& actionCommand) {
    _actionCommand = actionCommand;
}

void GInteractor::setAccelerator(const std::string& /* 快捷键 */) {
    // 在子类中重写
}

void GInteractor::setActionListener(GEventListener func) {
    setEventListener(getActionEventType(), func);
}

void GInteractor::setActionListener(GEventListenerVoid func) {
    setEventListener(getActionEventType(), func);
}

void GInteractor::setBackground(int rgb) {
    GThread::runOnQtGuiThread([this, rgb]() {
        QPalette palette(getWidget()->palette());
        palette.setColor(getWidget()->backgroundRole(), QColor(rgb));

        // 为 GChooser 和其他控件添加额外调色板颜色设置
        // TODO：对某些控件尚不能完全正常工作，例如 GChooser 弹出菜单
        if (getType() == "GChooser") {
            palette.setColor(QPalette::Base, QColor(rgb));
            palette.setColor(QPalette::Active, QPalette::Button, QColor(rgb));
            palette.setColor(QPalette::Inactive, QPalette::Button, QColor(rgb));
        } else if (getType() == "GTextArea"
                   || getType() == "GBrowserPane") {
            palette.setColor(QPalette::Base, QColor(rgb));
        }

        getWidget()->setAutoFillBackground(true);
        getWidget()->setPalette(palette);
    });
}

void GInteractor::setBackground(const std::string& color) {
    if (GColor::hasAlpha(color)) {
        int argb = GColor::convertColorToARGB(color);
        GThread::runOnQtGuiThread([this, argb]() {
            QColor qcolor = GColor::toQColorARGB(argb);
            QPalette palette(getWidget()->palette());
            palette.setColor(getWidget()->backgroundRole(), qcolor);

            // 为 GChooser 和其他控件添加额外调色板颜色设置
            // TODO：对某些控件尚不能完全正常工作，例如 GChooser 弹出菜单
            if (getType() == "GChooser") {
                palette.setColor(QPalette::Base, qcolor);
                palette.setColor(QPalette::Active, QPalette::Button, qcolor);
                palette.setColor(QPalette::Inactive, QPalette::Button, qcolor);
            } else if (getType() == "GTextArea"
                       || getType() == "GBrowserPane") {
                palette.setColor(QPalette::Base, qcolor);
            }

            getWidget()->setAutoFillBackground(true);
            getWidget()->setPalette(palette);
        });
    } else {
        int rgb = GColor::convertColorToRGB(color);
        setBackground(rgb);
    }
}

void GInteractor::setBounds(double x, double y, double width, double height) {
    GThread::runOnQtGuiThread([this, x, y, width, height]() {
        getWidget()->setGeometry((int) x, (int) y, (int) width, (int) height);
        getWidget()->setFixedSize((int) width, (int) height);
    });
}

void GInteractor::setBounds(const GRectangle& size) {
    setBounds(size.x, size.y, size.width, size.height);
}

void GInteractor::setClickListener(GEventListener func) {
    setEventListener("click", func);
}

void GInteractor::setClickListener(GEventListenerVoid func) {
    setEventListener("click", func);
}

void GInteractor::setColor(int rgb) {
    setForeground(rgb);
}

void GInteractor::setColor(const std::string& color) {
    setForeground(color);
}

void GInteractor::setContainer(GContainer* container) {
    _container = container;
    if (!container) {
        // 不在任何容器中的控件不应显示在屏幕上
        // （如果显示，它们会尴尬地悬停在 (0, 0)）
        QWidget* widget = getWidget();
        GThread::runOnQtGuiThread([widget]() {
            widget->setParent(nullptr);
        });
        setVisible(false);
    }
}

void GInteractor::setDoubleClickListener(GEventListener func) {
    setEventListener("doubleclick", func);
}

void GInteractor::setDoubleClickListener(GEventListenerVoid func) {
    setEventListener("doubleclick", func);
}

void GInteractor::setEnabled(bool value) {
    GThread::runOnQtGuiThread([this, value]() {
        getWidget()->setEnabled(value);
    });
}

void GInteractor::setForeground(int rgb) {
    GThread::runOnQtGuiThread([this, rgb]() {
        QPalette palette(getWidget()->palette());
        palette.setColor(getWidget()->foregroundRole(), QColor(rgb));
        // TODO：对某些控件尚不能完全正常工作，例如 GChooser 弹出菜单
        getWidget()->setPalette(palette);
    });
}

void GInteractor::setForeground(const std::string& color) {
    if (GColor::hasAlpha(color)) {
        int argb = GColor::convertColorToARGB(color);
        GThread::runOnQtGuiThread([this, argb]() {
            QPalette palette(getWidget()->palette());
            palette.setColor(getWidget()->foregroundRole(), GColor::toQColorARGB(argb));
            // TODO：对某些控件尚不能完全正常工作，例如 GChooser 弹出菜单
            getWidget()->setPalette(palette);
        });
    } else {
        int rgb = GColor::convertColorToRGB(color);
        setForeground(rgb);
    }
}

void GInteractor::setFont(const QFont& font) {
    GThread::runOnQtGuiThread([this, font]() {
        getWidget()->setFont(font);
    });
}

void GInteractor::setFont(const std::string& font) {
    setFont(GFont::toQFont(font));
}

void GInteractor::setHeight(double height) {
    require::nonNegative(height, "GInteractor::setHeight", "height");
    GThread::runOnQtGuiThread([this, height]() {
        getWidget()->setFixedHeight((int) height);
    });
}

void GInteractor::setIcon(const QIcon& /*图标*/) {
    // 在适当的子类中重写
}

void GInteractor::setIcon(const QPixmap& /*图标*/) {
    // 在适当的子类中重写
}

void GInteractor::setIcon(const std::string& filename, bool /* retainIconSize */) {
    _icon = filename;

    // 在子类中按需重写；务必调用父类
}

void GInteractor::setKeyListener(GEventListener func) {
    setEventListeners({"keypress",
                       "keyrelease",
                       "keytype"}, func);
}

void GInteractor::setKeyListener(GEventListenerVoid func) {
    setEventListeners({"keypress",
                       "keyrelease",
                       "keytype"}, func);
}

void GInteractor::setLocation(double x, double y) {
    GThread::runOnQtGuiThread([this, x, y]() {
        getWidget()->setGeometry(x, y, getWidth(), getHeight());
    });
}

void GInteractor::setMinimumSize(double width, double height) {
    require::nonNegative(width, "GInteractor::setMinimumSize", "width");
    require::nonNegative(height, "GInteractor::setMinimumSize", "height");
    GThread::runOnQtGuiThread([this, width, height]() {
        getInternalWidget()->setMinimumSize(width, height);
    });
}

void GInteractor::setMinimumSize(const GDimension& size) {
    setMinimumSize(size.width, size.height);
}

void GInteractor::setMouseListener(GEventListener func) {
    setEventListeners({"click",
                       "mousedrag",
                       "mouseenter",
                       "mouseexit",
                       "mousemove",
                       "mousepress",
                       "mouserelease",
                       "mousewheeldown",
                       "mousewheelup"}, func);
}

void GInteractor::setMouseListener(GEventListenerVoid func) {
    setEventListeners({"click",
                       "mousedrag",
                       "mouseenter",
                       "mouseexit",
                       "mousemove",
                       "mousepress",
                       "mouserelease",
                       "mousewheeldown",
                       "mousewheelup"}, func);
}

void GInteractor::setName(const std::string& name) {
    _name = name;
    // TODO：getWidget()->setObjectName()？
}

void GInteractor::setPreferredHeight(double height) {
    setPreferredSize(getPreferredWidth(), height);
}

void GInteractor::setPreferredSize(double width, double height) {
    require::nonNegative(width, "GInteractor::setPreferredSize", "width");
    require::nonNegative(height, "GInteractor::setPreferredSize", "height");
    GThread::runOnQtGuiThread([this, width, height]() {
        getInternalWidget()->setPreferredSize(width, height);
    });
}

void GInteractor::setPreferredSize(const GDimension& size) {
    GThread::runOnQtGuiThread([this, size]() {
        getInternalWidget()->setPreferredSize(size.width, size.height);
    });
}

void GInteractor::setPreferredWidth(double width) {
    setPreferredSize(width, getPreferredHeight());
}

void GInteractor::setSize(double width, double height) {
    require::nonNegative(width, "GInteractor::setSize", "width");
    require::nonNegative(height, "GInteractor::setSize", "height");
    GThread::runOnQtGuiThread([this, width, height]() {
        // setBounds(GRectangle(getX(), getY(), width, height));
        getWidget()->setGeometry((int) getX(), (int) getY(), (int) width, (int) height);
        getWidget()->setFixedSize((int) width, (int) height);
        getWidget()->setMinimumSize((int) width, (int) height);
    });
}

void GInteractor::setSize(const GDimension& size) {
    setSize(size.width, size.height);
}

void GInteractor::setTooltip(const std::string& tooltipText) {
    GThread::runOnQtGuiThread([this, tooltipText]() {
        getWidget()->setToolTip(QString::fromStdString(tooltipText));
    });
}

void GInteractor::setVisible(bool visible) {
    // 除非控件位于容器中，否则不允许将 visible 设置为 true
    if (!visible || _container) {
        GThread::runOnQtGuiThread([this, visible]() {
            getWidget()->setVisible(visible);
        });
    }
}

void GInteractor::setWidth(double width) {
    GThread::runOnQtGuiThread([this, width]() {
        getWidget()->setFixedWidth((int) width);
    });
}

void GInteractor::setX(double x) {
    setLocation(x, getY());
}

void GInteractor::setY(double y) {
    setLocation(getX(), y);
}

void GInteractor::unlock() {
    _lock.unlock();
}

void GInteractor::unlockConst() const {
    GInteractor* that = const_cast<GInteractor*>(this);
    that->unlock();
}


_Internal_QWidget::_Internal_QWidget()
        : _minimumSize(-1, -1),
          _preferredSize(-1, -1) {
    // 空
}

_Internal_QWidget::~_Internal_QWidget() {
    detach();
}

void _Internal_QWidget::detach() {
    // 空
}

QSize _Internal_QWidget::getMinimumSize() const {
    return QSize((int) _minimumSize.width, (int) _minimumSize.height);
}

bool _Internal_QWidget::hasMinimumSize() const {
    return _minimumSize.width >= 0 && _minimumSize.height >= 0;
}

QSize _Internal_QWidget::getPreferredSize() const {
    return QSize((int) _preferredSize.width, (int) _preferredSize.height);
}

bool _Internal_QWidget::hasPreferredSize() const {
    return _preferredSize.width >= 0 && _preferredSize.height >= 0;
}

void _Internal_QWidget::setMinimumSize(double width, double height) {
    _minimumSize = GDimension(width, height);
}

void _Internal_QWidget::setMinimumSize(const QSize& size) {
    setMinimumSize(size.width(), size.height());
}

void _Internal_QWidget::setPreferredSize(double width, double height) {
    _preferredSize = GDimension(width, height);
}

void _Internal_QWidget::setPreferredSize(const QSize& size) {
    setPreferredSize(size.width(), size.height());
}
