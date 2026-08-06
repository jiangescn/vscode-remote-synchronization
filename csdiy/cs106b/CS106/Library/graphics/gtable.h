/*
 * 文件：gtable.h
 * --------------
 * 此文件导出用于图形化可编辑二维表格的 GTable 类。
 *
 * @author Marty Stepp
 * @version 2018/08/23
 * - 重命名为 gtable.h，以替代 Java 版本
 * @version 2018/07/17
 * - 初始版本，基于 gtable.h
 * @since 2018/07/17
 */


#ifndef _gtable_h
#define _gtable_h

#include <string>
#include <QAbstractItemModel>
#include <QBrush>
#include <QFont>
#include <QItemSelection>
#include <QStyledItemDelegate>
#include <QTableWidget>

#include "grid.h"
#include "map.h"
#include "ginteractor.h"
#include "gobjects.h"
#include "gtypes.h"

class _Internal_QTableWidget;

/**
 * GTable 表示可编辑的二维图形表格，类似一个较为粗糙的
 * Excel 电子表格。
 *
 * 创建 GTable 后，可以监听表格事件，以便在以下情况收到通知：
 * 用户在表格单元格中输入新值时，可调用 setTableListener。
 *
 * 可编辑表格具有较复杂的编辑模型，用户可以开始
 * 通过高亮并输入来修改单元格，这会替换现有
 * 值，或双击它来编辑现有值。
 * 也可以在单元格上按 F2 进行编辑，等同于双击。
 * 编辑期间，可以按 Esc 取消编辑，或按 Tab/Enter
 * 完成编辑并移动到下一个单元格。
 *
 * 此类中的所有行/列索引均从 0 开始。
 */
class GTable : public GInteractor {
public:
    /**
     * 可显示的列标题标签样式。
     * “Excel”样式使用列名 A-Z，然后 AA-AZ、BA-BZ、……
     * ZA-ZZ，然后是 AAA、AAB，依此类推。
     * “numeric”样式使用 1、2、3、……这样的简单数字
     * “none”样式表示完全不使用任何列标题。
     */
    enum ColumnHeaderStyle {
        COLUMN_HEADER_NONE,     // 标题不会显示
        COLUMN_HEADER_EXCEL,    // A, B, ..., Z, AA, AB, ...
        COLUMN_HEADER_NUMERIC   // 1, 2, 3, ...
    };

    /**
     * 构造具有给定尺寸和可选大小的新表。
     * 如果省略 x、y、width 或 height，它们将由以下内容自动设置
     * 放置该表格的 GWindow 的布局管理器。
     * 这通常正是你想要的。
     * @throw 如果行数、列数、宽度或高度为负数，则抛出 ErrorException。
     */
    GTable(int rows = 0, int columns = 0, double width = 0, double height = 0,
            QWidget* parent = nullptr);

    ~GTable() override;

    /**
     * 更改所有列的宽度，使其恰好足够大
     * 适应其内容。
     */
    virtual void autofitColumnWidths();

    /**
     * 将表格中的所有单元格设为空字符串值。
     */
    virtual void clear();

    /**
     * 将给定单元格设为空字符串值。
     * @throw 如果给定行/列索引越界，则抛出 ErrorException
     */
    virtual void clearCell(int row, int column);

    /**
     * 删除应用于表格的所有单元格/列/行格式。
     */
    virtual void clearFormatting();

    /**
     * 删除应用于给定单元格的所有格式。
     */
    virtual void clearCellFormatting(int row, int column);

    /**
     * 取消选择当前选中的任何单元格。
     * 如果未选中单元格，调用此函数不会产生任何效果。
     */
    virtual void clearSelection();

    /**
     * 将表格中的每个单元格设为给定值。
     */
    virtual void fill(const std::string& text);

    /**
     * 返回给定单元格中存储的文本。
     * @throw 如果给定行或列越界，则抛出 ErrorException
     */
    virtual std::string get(int row, int column) const;

    /**
     * 返回要使用给定样式的列标题。
     * 默认无标题，但可设为 Excel 风格或数字形式。
     */
    virtual ColumnHeaderStyle getColumnHeaderStyle() const;

    /**
     * 返回给定列索引的像素宽度。
     * 构造表格时，所有列初始宽度相同。
     * @throw 如果给定列索引越界，则抛出 ErrorException
     */
    virtual double getColumnWidth(int column) const;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回给定行索引的像素高度。
     * 构造表格时，所有行初始高度相同。
     * @throw 如果给定行索引越界，则抛出 ErrorException
     */
    virtual double getRowHeight(int row) const;

    /**
     * 返回当前选中单元格的行和列。
     * 如果当前未选择单元格，则将行和列都设置为 -1。
     */
    virtual GridLocation getSelectedCell() const;

    /**
     * 返回当前选中单元格的行和列
     * 通过填充给定引用参数。
     * 如果当前未选择单元格，则将行和列都设置为 -1。
     */
    virtual void getSelectedCell(int& row, int& column) const;

    /**
     * 返回当前选中单元格中的文本。
     * 如果当前未选中单元格，则返回空字符串。
     */
    virtual std::string getSelectedCellValue() const;

    /**
     * 返回当前选中单元格的列；如果未选中单元格则为 -1
     * 当前已选择。
     */
    virtual int getSelectedColumn() const;

    /**
     * 返回当前选中单元格的行；如果未选中单元格则为 -1
     * 当前已选择。
     */
    virtual int getSelectedRow() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 如果当前选中了单元格，则返回 true。
     */
    virtual bool hasSelectedCell() const;

    /**
     * 返回表格的行数。
     * 等价于 numRows()。
     */
    virtual int height() const;

    /**
     * 如果给定从 0 开始的行/列索引位于边界内，则返回 true
     * 表格。换句话说，索引是否位于 (0, 0) 与
     * 以及 (numRows-1, numCols-1)，包含两端。
     */
    virtual bool inTableBounds(int row, int column) const;

    /**
     * 返回表格单元格是否可编辑。
     * 初始创建表格时默认为 true。
     */
    virtual bool isEditable() const;

    /**
     * 返回表格的列数。
     * 等价于 width()。
     */
    virtual int numCols() const;

    /**
     * 返回表格的行数。
     * 等价于 height()。
     */
    virtual int numRows() const;

    /**
     * 从此按钮删除表格监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeTableListener();

    /* @inherit */
    void requestFocus() override;

    /**
     * 修改表格，使其具有给定行数和列数。
     * 保留所有现有数据，所有新单元格为空。
     * @throw 如果 numRows 或 numCols 为负数，则抛出 ErrorException
     */
    virtual void resize(int numRows, int numCols);

    /**
     * 返回表格中是否显示行标题和列标题。
     * 初始为 false。
     */
    virtual bool rowColumnHeadersVisible() const;

    /**
     * 将给定单元格设为当前选中，
     * 替换之前的任何选区。
     * 请注意，用户之后可以点击其他单元格来选中它。
     * 若要表示不选择任何单元格，请调用 clearSelection。
     * @throw 如果给定行或列越界，则抛出 ErrorException
     */
    virtual void select(int row, int column);

    /**
     * 修改给定单元格中的值，使其存储给定文本。
     * @throw 如果给定行或列越界，则抛出 ErrorException
     */
    virtual void set(int row, int column, const std::string& text);

    /**
     * 设置显示在每个单元格后面的背景色。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     */
    void setBackground(int rgb) override;

    /**
     * 设置显示在每个单元格后面的背景色。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     */
    void setBackground(const std::string& color) override;

    /**
     * 设置给定单元格的水平对齐方式。
     * 行/列由从表格顶部/左侧开始、从 0 计数的行/列索引指定。
     * @throw 如果给定行/列索引越界，则抛出 ErrorException
     */
    virtual void setCellAlignment(int row, int column, HorizontalAlignment alignment);

    /**
     * 将给定单元格的背景色设置为给定颜色。
     * 行/列由从表格顶部/左侧开始、从 0 计数的行/列索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定行/列索引越界，则抛出 ErrorException
     */
    virtual void setCellBackground(int row, int column, int color);

    /**
     * 将给定单元格的背景色设置为给定颜色。
     * 行/列由从表格顶部/左侧开始、从 0 计数的行/列索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定行/列索引越界，则抛出 ErrorException
     */
    virtual void setCellBackground(int row, int column, const std::string& color);

    /**
     * 将给定单元格的文本字体设为给定 RGB 颜色。
     * 行/列由从表格顶部/左侧开始、从 0 计数的行/列索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定行/列索引越界，则抛出 ErrorException
     */
    virtual void setCellFont(int row, int column, const std::string& font);

    /**
     * 将给定单元格的前景色/文本颜色设置为给定颜色。
     * 行/列由从表格顶部/左侧开始、从 0 计数的行/列索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定行/列索引越界，则抛出 ErrorException
     */
    virtual void setCellForeground(int row, int column, int color);

    /**
     * 将给定单元格的前景色/文本颜色设置为给定颜色。
     * 行/列由从表格顶部/左侧开始、从 0 计数的行/列索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定行/列索引越界，则抛出 ErrorException
     */
    virtual void setCellForeground(int row, int column, const std::string& color);

    /**
     * 设置显示每个单元格文本所用的颜色。
     * 等价于 setForeground。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     */
    void setColor(int rgb) override;

    /**
     * 设置显示每个单元格文本所用的颜色。
     * 等价于 setForeground。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     */
    void setColor(const std::string& color) override;

    /**
     * 设置给定列的水平对齐方式。
     * 列由从表格左侧开始、从 0 计数的列索引指定。
     * @throw 如果给定列索引越界，则抛出 ErrorException
     */
    virtual void setColumnAlignment(int column, HorizontalAlignment alignment);

    /**
     * 将给定列的背景色设置为给定颜色。
     * 列由从表格左侧开始、从 0 计数的列索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定列索引越界，则抛出 ErrorException
     */
    virtual void setColumnBackground(int column, int color);

    /**
     * 将给定列的背景色设置为给定颜色。
     * 列由从表格左侧开始、从 0 计数的列索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定列索引越界，则抛出 ErrorException
     */
    virtual void setColumnBackground(int column, const std::string& color);

    /**
     * 将给定列的文本字体设为给定 RGB 颜色。
     * 列由从表格左侧开始、从 0 计数的列索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定列索引越界，则抛出 ErrorException
     */
    virtual void setColumnFont(int column, const std::string& font);

    /**
     * 将给定列的前景色/文本颜色设置为给定颜色。
     * 列由从表格左侧开始、从 0 计数的列索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定列索引越界，则抛出 ErrorException
     */
    virtual void setColumnForeground(int column, int color);

    /**
     * 将给定列的前景色/文本颜色设置为给定颜色。
     * 列由从表格左侧开始、从 0 计数的列索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定列索引越界，则抛出 ErrorException
     */
    virtual void setColumnForeground(int column, const std::string& color);

    /**
     * 将给定列索引设为给定像素宽度。
     * @throw 如果给定列索引越界，则抛出 ErrorException
     *        或宽度为负时
     */
    virtual void setColumnWidth(int column, double width);

    /**
     * 将列标题设置为使用给定样式。
     * 默认无标题，但可设为 Excel 风格或数字形式。
     */
    virtual void setColumnHeaderStyle(ColumnHeaderStyle style);

    /**
     * 设置表格单元格是否可编辑。
     * 初始为 true。
     */
    virtual void setEditable(bool editable);

    /**
     * 修改当前正在编辑的单元格中的值，使其存储
     * 给定的文本。这不会修改表格单元格中的值，而是
     * 仅仅是编辑器控件中的值。
     * @throw 如果给定行或列越界，则抛出 ErrorException
     */
    virtual void setEditorValue(int row, int column, const std::string& text);

    /**
     * 设置用于显示每个单元格文本的字体。
     */
    void setFont(const QFont& font) override;

    /**
     * 设置用于显示每个单元格文本的字体。
     * 有关字体的更多详细信息，请参阅 gfont.h。
     */
    void setFont(const std::string& font) override;

    /**
     * 设置显示每个单元格文本所用的颜色。
     * 等价于 setColor。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     */
    void setForeground(int rgb) override;

    /**
     * 设置显示每个单元格文本所用的颜色。
     * 等价于 setColor。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     */
    void setForeground(const std::string& color) override;

    /**
     * 设置表格所有单元格中文本的水平对齐方式。
     * 对齐方式可以是 LEFT、CENTER 或 RIGHT，初始为 LEFT。
     */
    virtual void setHorizontalAlignment(HorizontalAlignment alignment);

    /**
     * 设置给定行的水平对齐方式。
     * 行由从表格顶部开始、从 0 计数的行索引指定。
     * @throw 如果给定行索引越界，则抛出 ErrorException
     */
    virtual void setRowAlignment(int row, HorizontalAlignment alignment);

    /**
     * 将给定行的背景色设为给定 RGB 颜色。
     * 行由从表格顶部开始、从 0 计数的行索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定行索引越界，则抛出 ErrorException
     */
    virtual void setRowBackground(int row, int rgb);

    /**
     * 将给定行的背景色设为给定颜色。
     * 行由从表格顶部开始、从 0 计数的行索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定行索引越界，则抛出 ErrorException
     */
    virtual void setRowBackground(int row, const std::string& color);

    /**
     * 将给定行的文本字体设为给定字体。
     * 行由从表格顶部开始、从 0 计数的行索引指定。
     * 有关字体的更多详细信息，请参阅 gfont.h。
     * @throw 如果给定行索引越界，则抛出 ErrorException
     */
    virtual void setRowFont(int row, const std::string& font);

    /**
     * 将给定行的前景色/文本颜色设置为给定颜色。
     * 行由从表格顶部开始、从 0 计数的行索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定行索引越界，则抛出 ErrorException
     */
    virtual void setRowForeground(int row, int rgb);

    /**
     * 将给定行的前景色/文本颜色设置为给定颜色。
     * 行由从表格顶部开始、从 0 计数的行索引指定。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定行索引越界，则抛出 ErrorException
     */
    virtual void setRowForeground(int row, const std::string& color);

    /**
     * 设置表格中是否显示行标题和列标题。
     * 初始为 false。
     */
    virtual void setRowColumnHeadersVisible(bool visible);

    /**
     * 将给定行索引设为给定像素高度。
     * @throw 如果给定行索引越界，则抛出 ErrorException
     *        或高度为负时
     */
    virtual void setRowHeight(int row, double width);

    /**
     * 设置当前选中单元格中的文本。
     * 如果当前未选中单元格，则不执行任何操作。
     */
    virtual void setSelectedCellValue(const std::string& text);

    /**
     * 设置在此表中发生事件时要调用的给定函数。
     * 任何现有的表格监听器都会被替换。
     */
    virtual void setTableListener(GEventListener func);

    /**
     * 设置在此表中发生事件时要调用的给定函数。
     * 任何现有的表格监听器都会被替换。
     */
    virtual void setTableListener(GEventListenerVoid func);

    /**
     * 返回表格的列数。
     * 等价于 numCols()。
     */
    virtual int width() const;

private:
    Q_DISABLE_COPY(GTable)

    // 表示单元格、行、列或表格上的级联样式。
    struct TableStyle {
        int background;
        int foreground;
        std::string font;
        HorizontalAlignment alignment;
        // TODO：边框？

        TableStyle() {
            background = 0;
            foreground = 0;
            font = "";
            alignment = ALIGN_LEFT;
        }

        bool isSet() const {
            return background >= 0
                    && foreground >= 0
                    && !font.empty()
                    && alignment >= 0;
        }

        void mergeWith(const TableStyle& other) {
            if (other.background >= 0) {
                background = other.background;
            }
            if (other.foreground >= 0) {
                foreground = other.foreground;
            }
            if (!other.font.empty()) {
                font = other.font;
            }
            if (other.alignment >= 0) {
                alignment = other.alignment;
            }
        }

        TableStyle mergedWith(const TableStyle& other) {
            TableStyle copy = *this;
            copy.mergeWith(other);
            return copy;
        }

        static TableStyle unset() {
            TableStyle style;
            style.background = -1;
            style.foreground = -1;
            style.font = "";
            style.alignment = (HorizontalAlignment) -1;
            return style;
        }
    };

    // 默认格式的静态变量：
    // 背景色/前景色
    // 字体
    // 对齐方式
    static TableStyle _defaultCellStyle;

    // 成员变量
    _Internal_QTableWidget* _iqtableview;
    ColumnHeaderStyle _columnHeaderStyle;

    // 表格、行、列、单元格上的样式
    Map<int, TableStyle> _rowStyles;
    Map<int, TableStyle> _columnStyles;
    TableStyle _globalCellStyle;

    void applyStyleToCell(int row, int column, const TableStyle& style);

    /*
     * @throw 如果给定行/列值越界，则抛出 ErrorException。
     */
    void checkColumn(const std::string& member, int column) const;
    void checkIndex(const std::string& member, int row, int column) const;
    void checkRow(const std::string& member, int row) const;

    void ensureColumnStyle(int column);
    void ensureDefaultFormatting() const;   // const 权宜处理
    void ensureGlobalCellStyle();
    void ensureRowStyle(int row);
    TableStyle getMergedStyleForCell(int row, int column);

    // 单元格格式的内部设置函数。
    virtual void setCellAlignmentInternal(int row, int column, HorizontalAlignment alignment);
    virtual void setCellBackgroundInternal(int row, int column, int color);
    virtual void setCellFontInternal(int row, int column, const std::string& font);
    virtual void setCellForegroundInternal(int row, int column, int color);

    static std::string toExcelColumnName(int col);
    // static GridLocation toRowColumn(const std::string& excelColumnName);

    void updateColumnHeaders();

    friend class _Internal_QTableWidget;
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QItemDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    _Internal_QItemDelegate(QObject* parent = nullptr);
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual void destroyEditor(QWidget* editor, const QModelIndex& index) const;
    virtual QWidget* getEditor() const;

private:
    QWidget* _editor;
};


/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QTableWidget : public QTableWidget, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QTableWidget(GTable* gtable, int rows, int columns, QWidget* parent = nullptr);
    void detach() override;
    bool edit(const QModelIndex& index, QAbstractItemView::EditTrigger trigger, QEvent* event) override;
    virtual QWidget* getEditor() const;
    virtual _Internal_QItemDelegate* getItemDelegate() const;
    virtual bool isEditing() const;
    void closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint) override;
    void keyPressEvent(QKeyEvent* event) override;
    QSize sizeHint() const override;

public slots:
    void handleCellChange(int row, int column);
    void handleCellDoubleClick(int row, int column);
    void handleSelectionChange(const QItemSelection& selected, const QItemSelection& deselected);

private:
    GTable* _gtable;
    _Internal_QItemDelegate* _delegate;
    int _lastKeyPressed;

    void fireTableEvent(EventType eventType, const std::string& eventName, int row = -1, int col = -1);

    friend class GTable;
};

#endif // _gtable_h
