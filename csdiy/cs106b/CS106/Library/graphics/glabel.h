/*
 * 文件：glabel.h
 * --------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 将部分事件处理代码移到 GInteractor 父类
 * @version 2019/04/22
 * - 添加接受 QIcon 和 QPixmap 的 setIcon
 * @version 2018/10/04
 * - 添加 get/setWordWrap
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/04
 * - 添加双击事件支持
 * @version 2018/09/03
 * - 为可单击标签添加 addActionListener 方法
 * @version 2018/08/23
 * - 重命名为 glabel.h，以替代 Java 版本
 * @version 2018/06/25
 * - 初始版本
 */


#ifndef _glabel_h
#define _glabel_h

#include <string>
#include <QLabel>

#include "ginteractor.h"
#include "gobjects.h"

// 前向声明
class _Internal_QLabel;
class GWindow;

/**
 * GLabel 表示文本字符串。
 * 标签可以包含文本和/或图像图标。
 *
 * 可以通过设置动作、单击或双击监听器使 GLabel 可单击
 * 监听器，但通常如果你想要带文本的可点击交互控件，
 * 你可能更适合使用 GButton。
 */
class GLabel : public GInteractor {
public:
    /**
     * 创建具有指定文本标签和可选图标的标签。
     */
    GLabel(const std::string& text = "", const std::string& iconFileName = "", QWidget* parent = nullptr);

    /**
     * 创建具有指定文本标签和图标的标签。
     */
    GLabel(const std::string& text, const QIcon& icon, QWidget* parent = nullptr);

    /**
     * 创建具有指定文本标签和图标的标签。
     */
    GLabel(const std::string& text, const QPixmap& icon, QWidget* parent = nullptr);

    /**
     * 释放标签内部分配的内存。
     */
    ~GLabel() override;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回标签显示的字符串。
     * 等价于 getText。
     */
    virtual std::string getLabel() const;

    /**
     * 返回标签显示的字符串。
     * 等价于 getLabel。
     */
    virtual std::string getText() const;

    /**
     * 返回标签文本相对于图标的位置。
     * 默认值为 TEXT_BESIDE_ICON，但可以改为 TEXT_UNDER_ICON
     * 通过调用 setTextPosition 方法。
     */
    virtual GInteractor::TextPosition getTextPosition() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 返回标签文本过长时是否应自动换行。
     * 默认为 false。
     */
    virtual bool isWordWrap() const;

    /* @inherit */
    void setBounds(double x, double y, double width, double height) override;

    /* @inherit */
    void setBounds(const GRectangle& size) override;

    /* @inherit */
    void setColor(int rgb) override;

    /* @inherit */
    void setColor(const std::string& color) override;

    /* @inherit */
    void setFont(const QFont& font) override;

    /* @inherit */
    void setFont(const std::string& font) override;

    /* @inherit */
    void setForeground(int rgb) override;

    /* @inherit */
    void setForeground(const std::string& color) override;

    /* @inherit */
    void setHeight(double height) override;

    /* @inherit */
    void setIcon(const QIcon& icon) override;

    /* @inherit */
    void setIcon(const QPixmap& icon) override;

    /* @inherit */
    void setIcon(const std::string& filename, bool retainIconSize = true) override;

    /**
     * 将标签上的文本设置为给定文本。
     * 等价于 setText。
     */
    virtual void setLabel(const std::string& text);

    /* @inherit */
    void setLocation(double x, double y) override;

    /* @inherit */
    void setSize(double width, double height) override;

    /* @inherit */
    void setSize(const GDimension& size) override;

    /**
     * 将标签上的文本设置为给定文本。
     * 等价于 setLabel。
     */
    virtual void setText(const std::string& text);

    /**
     * 设置标签文本相对于图标的位置。
     * 默认值为 TEXT_BESIDE_ICON，但可以改为 TEXT_UNDER_ICON。
     */
    virtual void setTextPosition(GInteractor::TextPosition position);

    /* @inherit */
    void setVisible(bool visible) override;

    /* @inherit */
    void setWidth(double width) override;

    /**
     * 设置标签文本过长时是否自动换行。
     * 默认为 false。
     */
    virtual void setWordWrap(bool wrap);

    /* @inherit */
    void setX(double x) override;

    /* @inherit */
    void setY(double y) override;

private:
    Q_DISABLE_COPY(GLabel)
    _Internal_QLabel* _iqlabel;
    GText* _gtext;

    void ensureGText();
    GText* getGText() const;
    bool hasGText() const;

    friend class _Internal_QLabel;
    friend class GWindow;
};

// 为向后兼容，将 GTextLabel 作为 GLabel 的别名
typedef GLabel GTextLabel;


/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QLabel : public QLabel, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QLabel(GLabel* glabel, QWidget* parent = nullptr);
    void detach() override;
    QSize sizeHint() const override;

signals:
    void clicked();
    void doubleClicked();

protected:
    void mouseDoubleClickEvent(QMouseEvent* e) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    GLabel* _glabel;

    friend class GLabel;
};

#endif // _glabel_h
