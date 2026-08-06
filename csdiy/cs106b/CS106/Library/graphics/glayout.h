/*
 * 文件：glayout.h
 * ---------------
 *
 * @author Marty Stepp
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 glayout.h，以替代 Java 版本
 * @version 2018/06/25
 * - 初始版本
 */


#ifndef _glayout_h
#define _glayout_h

#include <QLayout>
#include <QRect>
#include <QWidget>

#include "ginteractor.h"

/**
 * 提供容器布局管理相关功能的辅助类。
 * 客户端通常无需直接使用此类。
 * @private
 */
class GLayout {
public:

    enum Position { West, North, South, East, Center };

    static void clearLayout(QLayout* layout);
    static bool contains(QLayout* layout, QWidget* widget);
    static void forceUpdate(GInteractor* interactor);
    static void forceUpdate(QWidget* widget);
    static QSize getPreferredSize(QWidget* widget);
    static QSize getProperSize(QLayout* layout);
    static QSize getProperSize(QWidget* widget);
    static void invalidateLayout(QLayout* layout);
    static Position toPosition(const std::string& positionName);

private:
    GLayout();   // 禁止构造
};

/**
 * 类似 Java AWT，以“边框”方式进行布局的 Qt 布局管理器。
 * 此类目前无法正常工作。
 *
 * 基于：http://doc.qt.io/qt-5.6/qtwidgets-layouts-borderlayout-example.html
 *
 * TODO：完成/调试或移除
 *
 * @private
 */
class GBorderLayout : public QLayout {
public:
    GBorderLayout(QWidget* parent, int margin = 0, int spacing = -1);
    GBorderLayout(int spacing = -1);
    ~GBorderLayout() override;

    void addItem(QLayoutItem* item) override;
    void addWidget(QWidget* widget);
    void addWidget(QWidget* widget, GLayout::Position position);
    Qt::Orientations expandingDirections() const override;
    bool hasHeightForWidth() const override;
    int count() const override;
    QLayoutItem* itemAt(int index) const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect& rect) override;
    QSize sizeHint() const override;
    QLayoutItem* takeAt(int index) override;

    void add(QLayoutItem* item, GLayout::Position position);

private:
    Q_DISABLE_COPY(GBorderLayout)

    struct ItemWrapper {
        ItemWrapper(QLayoutItem* i, GLayout::Position p) {
            item = i;
            position = p;
        }

        QLayoutItem* item;
        GLayout::Position position;
    };

    enum SizeType { MinimumSize, SizeHint };

    QSize calculateSize(SizeType sizeType) const;

    QList<ItemWrapper*> list;
};

#endif // _glayout_h
