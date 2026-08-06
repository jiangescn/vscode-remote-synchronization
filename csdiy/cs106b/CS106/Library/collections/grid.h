/*
 * 文件：grid.h
 * ------------
 * 此文件导出 <code>Grid</code> 类，该类提供
 * 表示二维数组的便捷抽象。
 */

#ifndef _grid_h
#define _grid_h

#include <initializer_list>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>

#include "collections.h"
#include "error.h"
#include "gridlocation.h"
#include "hashcode.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"

/*
 * 类：Grid<ValueType>
 * ----------------------
 * 此类存储带索引的二维数组。以下代码
 * 例如，创建大小为 <code>n</code> 的单位矩阵，其中
 * 元素在主对角线上为 1.0，其他位置为 0.0：
 *
 *<pre>
 *    Grid&lt;double&gt; createIdentityMatrix(int n) {
 *       Grid&lt;double&gt; matrix(n, n);
 *       for (int i = 0; i &lt; n; i++) {
 *          matrix[i][i] = 1.0;
 *       }
 *       return matrix;
 *    }
 *</pre>
 */

template <typename ValueType>
class Grid {
public:
    /* 前向引用 */
    class GridRow;
    class GridRowConst;

    /*
     * 构造函数：Grid
     * 用法：Grid<ValueType> grid;
     *        Grid<ValueType> grid(nRows, nCols);
     * ------------------------------------------
     * 初始化一个新网格。第二种构造函数形式
     * 更常见，并创建具有指定行数的网格
     * 以及列。网格中的每个元素均初始化为
     * 该类型的默认值。默认构造函数创建一个
     * 空网格，客户端必须调用 <code>resize</code> 才能
     * 设置尺寸。
     * 三参数构造函数还接受一个初始值和
     * 用该值填充网格的每个单元格。
     */
    Grid() = default;
    Grid(int _rowCount, int _columnCount);
    Grid(int _rowCount, int _columnCount, const ValueType& value);

    /*
     * 此构造函数使用初始化列表设置网格。
     * 用法：Grid<int> grid {{1, 2, 3}, {4, 5, 6}};
     */
    Grid(std::initializer_list<std::initializer_list<ValueType>> list);

    /*
     * 析构函数：~Grid
     * -----------------
     * 释放与此网格关联的任何堆存储。
     */
    virtual ~Grid() = default;

    /*
     * 方法：clear
     * 用法：grid.clear();
     * --------------------
     * 将网格中的每个值设为其元素类型的默认值。
     */
    void clear();

    /*
     * 方法：equals
     * 用法：if (grid.equals(grid2)) ...
     * ----------------------------------
     * 如果此网格包含完全相同的内容，则返回 <code>true</code>
     * 与给定另一个网格相同的值。
     * 行为与 == 运算符相同。
     */
    bool equals(const Grid<ValueType>& grid2) const;

    /*
     * 方法：fill
     * 用法：grid.fill(value);
     * ------------------------
     * 将给定值存入此网格的每个单元格。
     */
    void fill(const ValueType& value);

    /*
     * 方法：get
     * 用法：ValueType value = grid.get(row, col);
     * --------------------------------------------
     * 返回指定 <code>row</code>/<code>col</code> 处的元素
     * 此网格中的位置。如果
     * <code>row</code> 和 <code>col</code> 参数位于以下范围之外：
     * 网格边界。
     */
    const ValueType& get(int row, int col) const;
    const ValueType& get(const GridLocation& loc) const;

    /*
     * 方法：inBounds
     * 用法：if (grid.inBounds(row, col)) ...
     * ---------------------------------------
     * 如果指定行列位置满足条件，则返回 <code>true</code>
     * 位于网格边界内。
     */
    bool inBounds(int row, int col) const;
    bool inBounds(const GridLocation& loc) const;

    /*
     * 方法：isEmpty
     * 用法：if (grid.isEmpty()) ...
     * ---------------------------------------
     * 如果网格有 0 行和/或 0 列，则返回 <code>true</code>。
     */
    bool isEmpty() const;

    /*
     * 方法：locations
     * 用法：for (GridLocation loc : grid.locations()) ...
     * ----------------------------------------------------
     * 返回此网格中 (row,col) 位置的范围。
     * 这为遍历二维网格范围提供了一个很好的抽象
     * 使用单个 for 循环遍历索引。
     * 默认情况下，位置按行优先顺序排列，
     * 但如果将 rowMajor 参数传为 false，位置将会
     * 改为按列优先顺序返回。
     */
    GridLocationRange locations(bool rowMajor = true) const;

    /*
     * 方法：mapAll
     * 用法：grid.mapAll(fn);
     * -----------------------
     * 对网格中的每个元素调用指定函数。
     * 元素按<b><i>行优先顺序</i></b>处理，即
     * 先处理第 0 行的所有元素，然后处理
     * 位于第 1 行，依此类推。
     */
    void mapAll(std::function<void (const ValueType &)>) const;

    /*
     * 方法：numCols
     * 用法：int nCols = grid.numCols();
     * ----------------------------------
     * 返回网格的列数。
     */
    int numCols() const;

    /*
     * 方法：numRows
     * 用法：int nRows = grid.numRows();
     * ----------------------------------
     * 返回网格的行数。
     */
    int numRows() const;

    /*
     * 方法：resize
     * 用法：grid.resize(nRows, nCols);
     * ---------------------------------
     * 重新初始化网格，使其具有指定行数
     * 以及列。如果“retain”参数为 true，
     * 会尽可能保留此前的网格内容。
     * 如果未传入 'retain' 或其为 false，之前的所有网格内容
     * 被丢弃。
     */
    void resize(int _rowCount, int _columnCount, bool retain = false);

    /*
     * 方法：set
     * 用法：grid.set(row, col, value);
     * ---------------------------------
     * 替换指定 <code>row</code>/<code>col</code> 处的元素
     * 用新值设置此网格中的位置。如果
     * 如果 <code>row</code> 和 <code>col</code> 参数超出
     * 网格边界。
     */
    void set(int row, int col, const ValueType& value);
    void set(const GridLocation& loc, const ValueType& value);

    /*
     * 方法：size
     * 用法：int size = grid.size();
     * ------------------------------
     * 返回网格中的元素总数，它等于
     * 行数乘以列数。
     */
    int size() const;

    /*
     * 方法：toString
     * 用法：string str = grid.toString();
     * ------------------------------------
     * 将网格转换为可打印的字符串表示。
     * 返回的字符串是一维表示形式，例如：
     * "{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}"
     */
    std::string toString() const;

    /*
     * 方法：toString2D
     * 用法：string str = grid.toString2D();
     * --------------------------------------
     * 将网格转换为可打印的字符串表示。
     * 返回的字符串是二维表示形式，例如：
     * "{{1, 2, 3},\n
     *   {4, 5, 6},\n
     *   {7, 8, 9}}"
     */
    std::string toString2D(
            std::string rowStart = "{",
            std::string rowEnd = "}",
            std::string colSeparator = ", ",
            std::string rowSeparator = ",\n ") const;


    /*
     * 运算符：[]
     * 用法：grid[row][col]
     * ----------------------
     * 重载 <code>[]</code>，用于从此网格中选择元素。
     * 此扩展允许使用传统数组下标语法来
     * 获取或设置单个元素。若以下情况发生，此方法会报错：
     * <code>row</code> 和 <code>col</code> 参数超出
     * 网格边界。
     */
    GridRow operator [](int row);
    const GridRowConst operator [](int row) const;
    ValueType& operator [](const GridLocation& loc);
    const ValueType& operator [](const GridLocation& loc) const;

    /*
     * 其他 Grid 操作
     * --------------------------
     * 除本接口中列出的方法外，Grid
     * 类支持以下操作：
     *
     *   - 使用 << 和 >> 运算符进行流输入/输出
     *   - 为复制构造函数和赋值运算符实现深拷贝
     *   - 使用基于范围的 for 语句和 STL 迭代器进行迭代
     *
     * 这些迭代形式按行优先顺序处理网格。
     */

    /*
     * 运算符：==
     * 用法：if (grid1 == grid2) ...
     * ------------------------------
     * 比较两个网格是否相等。
     */
    bool operator ==(const Grid& grid2) const;

    /*
     * 运算符：!=
     * 用法：if (grid1 != grid2) ...
     * ------------------------------
     * 比较两个网格是否不相等。
     */
    bool operator !=(const Grid& grid2) const;

    /*
     * 运算符：<、>、<=、>=
     * 用法：if (grid1 < grid2) ...
     * -----------------------------
     * 用于比较两个网格的关系运算符。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     */
    bool operator <(const Grid& grid2) const;
    bool operator <=(const Grid& grid2) const;
    bool operator >(const Grid& grid2) const;
    bool operator >=(const Grid& grid2) const;

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

    /*
     * 实现说明：Grid 数据结构
     * -----------------------------------------
     * Grid 在内部以动态元素数组管理。
     * 数组本身是一维的，逻辑上划分为
     * 行列布局通过算术计算完成。布局
     * 按行优先顺序存储，也就是说完整的第一行
     * 连续排列，后面紧跟完整的第二行，
     * 依此类推。
     */

private:
    /* 实例变量 */
    Vector<ValueType> _elements;   // 按行优先顺序排列的元素
    int _rowCount = 0;             // 网格中的行数
    int _columnCount = 0;          // 网格中的列数

    /* 私有方法原型 */

    /*
     * 如果给定的行/列不在
     * 从 (0,0) 到 (rowMax-1,colMax-1)，包含两端。
     * 这是供 Grid 各成员使用的统一错误处理程序，这些成员
     * 接受索引参数。
     * prefix 参数表示放在以下内容开头的文本字符串：
     * 错误消息，通常用于指出是哪个成员抛出了错误。
     */
    void checkIndexes(int row, int col,
                      int rowMax, int colMax,
                      std::string prefix) const;
    int gridCompare(const Grid& grid2) const;

    /*
     * 隐藏功能
     * ---------------
     * 此文件的剩余部分包含实现以下功能所需的代码：
     * 支持深拷贝和迭代。加入这些方法
     * 放入公共接口会使该接口更加
     * 普通客户端难以理解。
     */

public:
    using iterator       = typename Vector<ValueType>::iterator;
    using const_iterator = typename Vector<ValueType>::const_iterator;

    iterator begin() {
        return _elements.begin();
    }
    iterator end() {
        return _elements.end();
    }

    const_iterator begin() const {
        return _elements.begin();
    }
    const_iterator end() const {
        return _elements.end();
    }

    /*
     * 私有类：Grid<ValType>::GridRow
     * -------------------------------------
     * 此代码段在 Grid 模板内部定义一个嵌套类
     * 使得可以对 Grid 值使用传统下标操作。
     */
    class GridRow {
    public:
        GridRow() : _gp(nullptr), _row(0) {
            /* 空 */
        }

        ValueType& operator [](int col) {
            _gp->checkIndexes(_row, col, _gp->_rowCount-1, _gp->_columnCount-1, "operator [][]");
            return _gp->_elements[(_row * _gp->_columnCount) + col];
        }

        ValueType operator [](int col) const {
            _gp->checkIndexes(_row, col, _gp->_rowCount-1, _gp->_columnCount-1, "operator [][]");
            return _gp->_elements[(_row * _gp->_columnCount) + col];
        }

        int size() const {
            return _gp->numCols();
        }

    private:
        GridRow(Grid* gridRef, int index) {
            _gp = gridRef;
            _row = index;
        }

        Grid* _gp;
        int _row;
        friend class Grid;
    };
    friend class GridRow;

    class GridRowConst {
    public:
        GridRowConst() : _gp(nullptr), _row(0) {
            /* 空 */
        }

        const ValueType operator [](int col) const {
            _gp->checkIndexes(_row, col, _gp->_rowCount-1, _gp->_columnCount-1, "operator [][]");
            return _gp->_elements[(_row * _gp->_columnCount) + col];
        }

        int size() const {
            return _gp->numCols();
        }

    private:
        GridRowConst(Grid* const gridRef, int index) : _gp(gridRef), _row(index) {}

        const Grid* const _gp;
        const int _row;
        friend class Grid;
    };
    friend class GridRowConst;

    template <typename T>
    friend int hashCode(const Grid<T>& g);
};

template <typename ValueType>
Grid<ValueType>::Grid(int numRows, int numCols) {
    resize(numRows, numCols);
}

template <typename ValueType>
Grid<ValueType>::Grid(int numRows, int numCols, const ValueType& value) {
    resize(numRows, numCols);
    fill(value);
}

template <typename ValueType>
Grid<ValueType>::Grid(std::initializer_list<std::initializer_list<ValueType>> list) {
    // 以适当大小创建网格
    _rowCount = list.size();
    if (list.begin() != list.end()) {
        _columnCount = list.begin()->size();
    }
    resize(_rowCount, _columnCount);

    // 将初始化列表中的数据复制到 Grid
    auto rowItr = list.begin();
    for (int row = 0; row < _rowCount; row++) {
        if (static_cast<int>(rowItr->size()) != _columnCount) {
            error("Grid::constructor: initializer list is not rectangular (must have same # cols in each row)");
        }
        auto colItr = rowItr->begin();
        for (int col = 0; col < _columnCount; col++) {
            set(row, col, *colItr);
            colItr++;
        }
        rowItr++;
    }
}

template <typename ValueType>
void Grid<ValueType>::clear() {
    ValueType defaultValue = ValueType();
    for (int r = 0; r < _rowCount; r++) {
        for (int c = 0; c < _columnCount; c++) {
            set(r, c, defaultValue);
        }
    }
}

template <typename ValueType>
bool Grid<ValueType>::equals(const Grid<ValueType>& grid2) const {
    // 优化：如果确实是同一网格，则停止
    if (this == &grid2) {
        return true;
    }

    if (_rowCount != grid2._rowCount || _columnCount != grid2._columnCount) {
        return false;
    }
    for (int row = 0; row < _rowCount; row++) {
        for (int col = 0; col < _columnCount; col++) {
            if (get(row, col) != grid2.get(row, col)) {
                return false;
            }
        }
    }
    return true;
}

template <typename ValueType>
void Grid<ValueType>::fill(const ValueType& value) {
    for (int row = 0; row < _rowCount; row++) {
        for (int col = 0; col < _columnCount; col++) {
            set(row, col, value);
        }
    }

    /* 这算作一次语义更新，因此必须更新版本。 */
    _elements.updateVersion();
}

template <typename ValueType>
const ValueType& Grid<ValueType>::get(int row, int col) const {
    checkIndexes(row, col, _rowCount-1, _columnCount-1, "get");
    return _elements[(row * _columnCount) + col];
}

template <typename ValueType>
const ValueType& Grid<ValueType>::get(const GridLocation& loc) const {
    return get(loc.row, loc.col);
}

template <typename ValueType>
bool Grid<ValueType>::inBounds(int row, int col) const {
    return row >= 0 && col >= 0 && row < _rowCount && col < _columnCount;
}

template <typename ValueType>
bool Grid<ValueType>::inBounds(const GridLocation& loc) const {
    return inBounds(loc.row, loc.col);
}

template <typename ValueType>
bool Grid<ValueType>::isEmpty() const {
    return _rowCount == 0 || _columnCount == 0;
}

template <typename ValueType>
GridLocationRange Grid<ValueType>::locations(bool rowMajor) const {
    return GridLocationRange(0, 0, numRows() - 1, numCols() - 1, rowMajor);
}

template <typename ValueType>
void Grid<ValueType>::mapAll(std::function<void (const ValueType &)> fn) const {
    for (int i = 0; i < _rowCount; i++) {
        for (int j = 0; j < _columnCount; j++) {
            fn(get(i, j));
        }
    }
}

template <typename ValueType>
int Grid<ValueType>::numCols() const {
    return _columnCount;
}

template <typename ValueType>
int Grid<ValueType>::numRows() const {
    return _rowCount;
}

template <typename ValueType>
void Grid<ValueType>::resize(int numRows, int numCols, bool retain) {
    if (numRows < 0 || numCols < 0) {
        std::ostringstream out;
        out << "Grid::resize: Attempt to resize grid to invalid size ("
               << numRows << ", " << numCols << ")";
        error(out.str());
    }

    // 优化：如果已是该大小，则不执行 resize
    if (numRows == this->_rowCount && numCols == this->_columnCount && retain) {
        /* 需要更新版本，因为从语义上说我们已经更改了网格，
         * 但尚未修改向量。
         */
        _elements.updateVersion();
        return;
    }

    // 保存旧数组/大小的备份
    Vector<ValueType> oldElements = std::move(_elements);
    int oldnRows = this->_rowCount;
    int oldnCols = this->_columnCount;

    // 创建新的空数组并设置新大小
    this->_rowCount = numRows;
    this->_columnCount = numCols;
    this->_elements = Vector<ValueType>(numRows * numCols, ValueType());

    // 可能保留旧内容
    if (retain) {
        int minRows = oldnRows < numRows ? oldnRows : numRows;
        int minCols = oldnCols < numCols ? oldnCols : numCols;
        for (int row = 0; row < minRows; row++) {
            for (int col = 0; col < minCols; col++) {
                this->_elements[(row * numCols) + col] = oldElements[(row * oldnCols) + col];
            }
        }
    }
}

template <typename ValueType>
void Grid<ValueType>::set(int row, int col, const ValueType& value) {
    checkIndexes(row, col, _rowCount - 1, _columnCount - 1, "set");
    _elements[(row * _columnCount) + col] = value;
}

template <typename ValueType>
void Grid<ValueType>::set(const GridLocation& loc, const ValueType& value) {
    set(loc.row, loc.col, value);
}

template <typename ValueType>
int Grid<ValueType>::size() const {
    return _rowCount * _columnCount;
}

template <typename ValueType>
std::string Grid<ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

template <typename ValueType>
std::string Grid<ValueType>::toString2D(
        std::string rowStart, std::string rowEnd,
        std::string colSeparator, std::string rowSeparator) const {
    std::ostringstream os;
    os << rowStart;
    int nr = numRows();
    int nc = numCols();
    for (int i = 0; i < nr ; i++) {
        if (i > 0) {
            os << rowSeparator;
        }
        os << rowStart;
        for (int j = 0; j < nc; j++) {
            if (j > 0) {
                os << colSeparator;
            }
            writeGenericValue(os, get(i, j), /* forceQuotes */ true);
        }
        os << rowEnd;
    }
    os << rowEnd;
    return os.str();
}

template <typename ValueType>
typename Grid<ValueType>::GridRow Grid<ValueType>::operator [](int row) {
    return GridRow(this, row);
}

template <typename ValueType>
ValueType& Grid<ValueType>::operator [](const GridLocation& loc) {
    checkIndexes(loc.row, loc.col, _rowCount-1, _columnCount-1, "operator []");
    return _elements[(loc.row * _columnCount) + loc.col];
}

template <typename ValueType>
const typename Grid<ValueType>::GridRowConst
Grid<ValueType>::operator [](int row) const {
    return GridRowConst(const_cast<Grid*>(this), row);
}

template <typename ValueType>
const ValueType& Grid<ValueType>::operator [](const GridLocation& loc) const {
    checkIndexes(loc.row, loc.col, _rowCount-1, _columnCount-1, "operator []");
    return _elements[(loc.row * _columnCount) + loc.col];
}

template <typename ValueType>
bool Grid<ValueType>::operator ==(const Grid& grid2) const {
    return equals(grid2);
}

template <typename ValueType>
bool Grid<ValueType>::operator !=(const Grid& grid2) const {
    return !equals(grid2);
}

template <typename ValueType>
bool Grid<ValueType>::operator <(const Grid& grid2) const {
    return gridCompare(grid2) < 0;
}

template <typename ValueType>
bool Grid<ValueType>::operator <=(const Grid& grid2) const {
    return gridCompare(grid2) <= 0;
}

template <typename ValueType>
bool Grid<ValueType>::operator >(const Grid& grid2) const {
    return gridCompare(grid2) > 0;
}

template <typename ValueType>
bool Grid<ValueType>::operator >=(const Grid& grid2) const {
    return gridCompare(grid2) >= 0;
}

template <typename ValueType>
void Grid<ValueType>::checkIndexes(int row, int col,
                                   int rowMax, int colMax,
                                   std::string prefix) const {
    const int rowMin = 0;
    const int colMin = 0;
    if (row < rowMin || row > rowMax || col < colMin || col > colMax) {
        std::ostringstream out;
        out << "Grid::" << prefix << ": (" << row << ", " << col << ")"
            << " is outside of valid range [";
        if (rowMin < rowMax && colMin < colMax) {
            out << "(" << rowMin << ", " << colMin <<  ")..("
                << rowMax << ", " << colMax << ")";
        } else if (rowMin == rowMax && colMin == colMax) {
            out << "(" << rowMin << ", " << colMin <<  ")";
        } // 否则 min > max，没有范围，空网格
        out << "]";
        error(out.str());
    }
}

template <typename ValueType>
int Grid<ValueType>::gridCompare(const Grid& grid2) const {
    if (_rowCount != grid2._rowCount) return _rowCount - grid2._rowCount;
    if (_columnCount != grid2._columnCount) return _columnCount - grid2._columnCount;
    return stanfordcpplib::collections::compare(_elements, grid2._elements);
}

template <typename ValueType>
int hashCode(const Grid<ValueType>& g) {
    return hashCode(g._rowCount, g._columnCount, g._elements);
}

/*
 * 实现说明：<< 和 >>
 * -------------------------------
 * 插入和提取运算符使用以下文件中的模板功能：
 * 使用 strlib.h 读写通用值，并以特殊方式处理字符串
 * 特殊处理。
 */
template <typename ValueType>
std::ostream& operator <<(std::ostream& os, const Grid<ValueType>& grid) {
    os << "{";
    int nRows = grid.numRows();
    int nCols = grid.numCols();
    for (int i = 0; i < nRows; i++) {
        if (i > 0) {
            os << ", ";
        }
        os << "{";
        for (int j = 0; j < nCols; j++) {
            if (j > 0) {
                os << ", ";
            }
            writeGenericValue(os, grid.get(i, j), /* forceQuotes */ true);
        }
        os << "}";
    }
    return os << "}";
}

template <typename ValueType>
std::istream& operator >>(std::istream& is, Grid<ValueType>& grid) {
    Vector<Vector<ValueType>> vec2d;
    if (!(is >> vec2d)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    int nRows = vec2d.size();
    int nCols = (nRows == 0) ? 0 : vec2d[0].size();
    grid.resize(nRows, nCols);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            grid[i][j] = vec2d[i][j];
        }
    }

    return is;
}

/*
 * 函数：randomElement
 * 用法：element = randomElement(grid);
 * -------------------------------------
 * 返回从给定网格中随机选择的元素。
 * 如果网格为空，则抛出错误。
 */
template <typename T>
const T& randomElement(const Grid<T>& grid) {
    if (grid.isEmpty()) {
        error("randomElement: empty grid was passed");
    }

    int randomIndex = randomInteger(0, grid.size() - 1);
    int row = randomIndex / grid.numCols();
    int col = randomIndex % grid.numCols();
    return grid.get(row, col);
}


#endif // _grid_h
