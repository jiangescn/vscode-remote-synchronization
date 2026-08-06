/*
 * 文件：graph.h
 * -------------
 * 此文件导出一个参数化 Graph 类，用于表示图，
 * 它由节点（顶点）集合和弧（边）集合组成。
 */

#ifndef _graph_h
#define _graph_h

#include <string>

#include "collections.h"
#include "error.h"
#include "hashcode.h"
#include "map.h"
#include "set.h"
#include "strlib.h"
#include "tokenscanner.h"

/**
 * 此类表示具有指定节点和弧类型的图。
 * <code>NodeType</code> 和 <code>ArcType</code> 参数表示
 * 分别用于节点和弧的结构体类型或类。
 * 这些类型可以包含客户端所需的任何字段或方法，
 * 但必须包含 <code>Graph</code> 所要求的以下字段
 * 软件包本身：
 *
 * <p><code>NodeType</code> 定义必须包含：
 * <ul>
 *   <li>一个名为 <code>name</code> 的 <code>string</code> 字段
 *   <li>一个名为 <code>arcs</code> 的 <code>Set&lt;ArcType *&gt;</code> 字段
 * </ul>
 *
 * <p><code>ArcType</code> 定义必须包含：
 * <ul>
 *   <li>一个名为 <code>start</code> 的 <code>NodeType *</code> 字段
 *   <li>一个名为 <code>finish</code> 的 <code>NodeType *</code> 字段
 * </ul>
 */
template <typename NodeType, typename ArcType>
class Graph {
public:
    /**
     * 创建空图。
     * @bigoh O(1)
     */
    Graph();

    /**
     * 释放用于表示图的内部存储空间。
     * @bigoh O(V + E)
     */
    virtual ~Graph();

    /**
     * 向图中添加一条从节点 n1 到 n2 的有向弧。
     * 若在图中找不到任一节点，则将该节点添加到图中。
     * 返回指向弧的指针，以便客户端需要时保存该值。
     * @bigoh O(log V + log E)
     */
    ArcType* addArc(const std::string& n1, const std::string& n2);

    /**
     * 向图中添加一条从节点 n1 到 n2 的有向弧。
     * 若在图中找不到任一节点，则将该节点添加到图中。
     * 返回指向弧的指针，以便客户端需要时保存该值。
     *
     * @throw 如果传入的任一指针为空，则抛出 ErrorException
     * @bigoh O(log V + log E)
     */
    ArcType* addArc(NodeType* n1, NodeType* n2);

    /**
     * 将给定弧添加到图中。
     * 如果传入的起点/终点节点尚不属于该图，
     * 它们会被添加到图中。
     * 返回指向弧的指针，以便客户端需要时保存该值。
     *
     * 内存管理：一旦将此 ArcType* 指针交给我，所有权归本代码。
     * 完成后会将其删除/释放。
     * 无需（也不应）自行释放它。
     *
     * @throw 如果传入的任一指针为空，则抛出 ErrorException
     * @bigoh O(log V + log E)
     */
    ArcType* addArc(ArcType* arc);

    /**
     * 向图中添加节点。此方法的第一个版本
     * 创建适当类型的新节点并初始化其
     * 字段；第二种假定客户端已创建
     * 该节点，并直接将其添加到图中。
     * 返回指向该节点的指针。
     * 若已存在给定名称的节点，则不执行任何操作。
     *
     * 内存管理：一旦你把这个 NodeType* 指针交给我，这段代码就拥有它。
     * 完成后会将其删除/释放。
     * 无需（也不应）自行释放它。
     *
     * @throw 如果传入的任一指针为空，则抛出 ErrorException
     * @bigoh O(log V)
     */
    NodeType* addNode(const std::string& name);

    /**
     * 向图中添加节点。
     * 此版本假定客户端已创建节点结构
     * 并直接将其添加到图中。
     * 返回指向该节点的指针。
     * 若已存在给定名称的节点，则不执行任何操作。
     *
     * 内存管理：一旦你把这个 NodeType* 指针交给我，这段代码就拥有它。
     * 完成后会将其删除/释放。
     * 无需（也不应）自行释放它。
     *
     * @throw 如果传入的任一指针为空，则抛出 ErrorException
     * @bigoh O(log V)
     */
    NodeType* addNode(NodeType* node);

    /**
     * 返回图中的弧数量。
     * @bigoh O(1)
     */
    int arcCount() const;

    /**
     * 按照以下迭代顺序返回图中的最后一个节点
     * for-each 循环或迭代器。
     * @throw 如果图为空，则抛出 ErrorException
     * @bigoh O(1)
     */
    NodeType* back() const;

    /**
     * 将图重新初始化为空，移除所有节点和弧
     * 并释放对应内部结构使用的任何堆存储空间。
     * @bigoh O(V + E)
     */
    void clear();

    /**
     * 从图中删除所有弧，并释放其使用的堆存储
     * 对应的内部结构。图的节点保持不变。
     * @bigoh O(E)
     */
    void clearArcs();

    /**
     * 从图中移除所有起点为给定节点的弧，
     * 释放对应内部结构使用的堆存储空间。
     * 图的节点保持不变。
     * 如果给定节点指针为 null 或在图中找不到，则不产生任何效果。
     * @bigoh O(log V + E)
     */
    void clearArcs(NodeType* node);

    /**
     * 从图中移除所有起点为给定节点的弧，
     * 释放对应内部结构使用的堆存储空间。
     * 图的节点保持不变。
     * 如果给定节点在图中找不到，则不产生任何效果。
     * @bigoh O(E log E)
     */
    void clearArcs(const std::string& name);

    /**
     * 如果给定两个节点之间直接存在一条弧，则返回 true。
     * 如果任一节点为 null 或不包含在此图中，则返回 false。
     * @bigoh O(log E)
     */
    bool containsArc(NodeType* node1, NodeType* node2) const;

    /**
     * 如果给定两个节点之间直接存在一条弧，则返回 true。
     * 若任一节点不在此图中，则返回 false。
     * @bigoh O(log E)
     */
    bool containsArc(const std::string& node1, const std::string& node2) const;

    /**
     * 如果给定弧存在于此图中，则返回 true。
     * 如果给定弧为 null，或其任一节点不包含在
     * 此图，则返回 false。
     * @bigoh O(log E)
     */
    bool containsArc(ArcType* arc) const;

    /**
     * 如果此图中存在具有给定名称的节点，则返回 true。
     * @bigoh O(log V)
     */
    bool containsNode(const std::string& name) const;

    /**
     * 如果给定节点属于此图，则返回 true。
     * 如果传入的指针为 null，则返回 false。
     * @bigoh O(log V)
     */
    bool containsNode(NodeType* node) const;

    /**
     * 比较两个图是否相等。
     * 如果此图包含完全相同的内容，则返回 <code>true</code>
     * 具有与给定另一图相同的节点、弧和连接。
     * 行为与 == 运算符相同。
     * @bigoh O(V log V + E log E)
     */
    bool equals(const Graph<NodeType, ArcType>& graph2) const;

    /**
     * 按照以下迭代顺序返回图中的第一个节点
     * for-each 循环或迭代器。
     * @throw 如果图为空，则抛出 ErrorException
     * @bigoh O(1)
     */
    NodeType* front() const;

    /**
     * 返回从 node1 到 node2 的弧（如果存在）。
     * 若给定两节点之间存在多条弧，返回哪一条未作规定。
     * 如果传入的任一指针为 null 或不存在这样的弧，则返回空指针。
     * @bigoh O(log V + log E)
     */
    ArcType* getArc(NodeType* node1, NodeType* node2) const;

    /**
     * 返回从 node1 到 node2 的弧（如果存在）。
     * 若给定两节点之间存在多条弧，返回哪一条未作规定。
     * 如果不存在这样的弧，则返回空指针。
     * @bigoh O(log V + log E)
     */
    ArcType* getArc(const std::string& node1, const std::string& node2) const;

    /**
     * 返回图中所有弧的集合。
     * @bigoh O(1)
     */
    const Set<ArcType*>& getArcSet() const;

    /**
     * 返回从指定节点出发的所有弧的集合，
     * 表示为指向其节点结构的指针。
     * 如果传入的指针为 null，或给定节点在图中找不到，
     * 返回空集合。
     * @bigoh O(1)
     */
    const Set<ArcType*>& getArcSet(NodeType* node) const;

    /**
     * 返回从指定节点出发的所有弧的集合。
     * 如果给定节点在图中找不到，则返回空集合。
     * @bigoh O(1)
     */
    const Set<ArcType*>& getArcSet(const std::string& name) const;

    /**
     * 返回从其他节点到给定节点的出向弧集合。
     * 换言之，getInverseArcSet(n1) 是满足以下条件的所有节点 n2 的集合：
     * 使得存在一条从 n2 出发并在 n1 结束的弧 E。
     *
     * 若传入的任一指针为空，或在以下对象中找不到给定节点：
     * 在此图中，则返回空集合。
     * @bigoh O(E)
     */
    const Set<ArcType*> getInverseArcSet(NodeType* node) const;

    /**
     * 返回从其他节点到给定节点的出向弧集合。
     * 换言之，getInverseArcSet(n1) 是满足以下条件的所有节点 n2 的集合：
     * 使得存在一条从 n2 出发并在 n1 结束的弧 E。
     *
     * 若在此图中找不到给定节点，则返回空集合。
     * @bigoh O(E)
     */
    const Set<ArcType*> getInverseArcSet(const std::string& name) const;

    /**
     * 返回指定节点邻居的节点名称字符串集合
     * 给定节点。
     * 换言之，getInverseNeighborNames(n1) 是满足以下条件的所有字符串 n2 的集合：
     * 使得存在一条从 n2 出发并在 n1 结束的弧 E。
     *
     * 若传入的任一指针为空，或在以下对象中找不到给定节点：
     * 在此图中，则返回空集合。
     * @bigoh O(E)
     */
    Set<std::string> getInverseNeighborNames(NodeType* node) const;

    /**
     * 返回指定节点邻居的节点名称字符串集合
     * 给定节点。
     * 换言之，getInverseNeighborNames(n1) 是满足以下条件的所有字符串 n2 的集合：
     * 使得存在一条从 n2 出发并在 n1 结束的弧 E。
     *
     * 若在此图中找不到给定节点，则返回空集合。
     * @bigoh O(E)
     */
    Set<std::string> getInverseNeighborNames(const std::string& node) const;

    /**
     * 返回指定节点的所有邻接节点集合。
     * 换言之，getInverseNeighbors(n1) 是满足以下条件的所有节点 n2 的集合：
     * 使得存在一条从 n2 出发并在 n1 结束的弧 E。
     *
     * 若传入的任一指针为空，或在以下对象中找不到给定节点：
     * 在此图中，则返回空集合。
     * @bigoh O(E)
     */
    Set<NodeType*> getInverseNeighbors(NodeType* node) const;

    /**
     * 返回指定节点的所有邻接节点集合。
     * 换言之，getInverseNeighbors(n1) 是满足以下条件的所有节点 n2 的集合：
     * 使得存在一条从 n2 出发并在 n1 结束的弧 E。
     *
     * 若在此图中找不到给定节点，则返回空集合。
     * @bigoh O(E)
     */
    Set<NodeType*> getInverseNeighbors(const std::string& node) const;

    /**
     * 返回指定节点所有邻居的节点名称集合。
     * 换言之，getNeighbors(n1) 是满足以下条件的所有字符串 n2 的集合：
     * 使得存在一条从 n1 出发并在 n2 结束的弧 E。
     *
     * 若传入的任一指针为空，或在以下对象中找不到给定节点：
     * 在此图中，则返回空集合。
     * @bigoh O(log V)
     */
    Set<std::string> getNeighborNames(NodeType* node) const;

    /**
     * 返回指定节点所有邻居的节点名称集合。
     * 换言之，getNeighbors(n1) 是满足以下条件的所有字符串 n2 的集合：
     * 使得存在一条从 n1 出发并在 n2 结束的弧 E。
     *
     * 若在此图中找不到给定节点，则返回空集合。
     * @bigoh O(log V)
     */
    Set<std::string> getNeighborNames(const std::string& node) const;

    /**
     * 返回指定节点的所有邻接节点集合。
     * 换言之，getNeighbors(n1) 是满足以下条件的所有节点 n2 的集合：
     * 使得存在一条从 n1 出发并在 n2 结束的弧 E。
     *
     * 若传入的任一指针为空，或在以下对象中找不到给定节点：
     * 在此图中，则返回空集合。
     * @bigoh O(log V)
     */
    Set<NodeType*> getNeighbors(NodeType* node) const;

    /**
     * 返回指定节点的所有邻接节点集合。
     * 换言之，getNeighbors(n1) 是满足以下条件的所有节点 n2 的集合：
     * 使得存在一条从 n1 出发并在 n2 结束的弧 E。
     *
     * 若在此图中找不到给定节点，则返回空集合。
     * @bigoh O(log V)
     */
    Set<NodeType*> getNeighbors(const std::string& node) const;

    /**
     * 在附加到图的名称表中查找节点，并
     * 返回指向该节点的指针。
     * 如果不存在指定名称的节点，则返回 <code>nullptr</code>。
     * @bigoh O(log V)
     */
    NodeType* getNode(const std::string& name) const;

    /**
     * 返回图中所有节点名称的集合。
     * 类似于 getNodeSet，但返回字符串集合而不是以下集合
     * 节点指针。
     * @bigoh O(V log V)
     */
    Set<std::string> getNodeNames() const;

    /**
     * 返回图中所有节点的集合。
     * 这些是指向内部 NodeType* 结构的直接指针，位于
     * 图，因此你对它们所做的任何修改都会反映到图中。
     * @bigoh O(1)
     */
    const Set<NodeType*>& getNodeSet() const;

    /**
     * 如果图中包含从某处出发的弧，则返回 <code>true</code>
     * 从 <code>n1</code> 到 <code>n2</code>。
     * 如果传入的任一指针为 null，或任一节点不包含在
     * 在此图中，则返回 false。
     * @bigoh O(log V)
     */
    bool isConnected(NodeType* n1, NodeType* n2) const;

    /**
     * 如果图中包含从某处出发的弧，则返回 <code>true</code>
     * 从 <code>n1</code> 到 <code>n2</code>。
     * 若任一节点不在此图中，则返回 false。
     * @bigoh O(log V)
     */
    bool isConnected(const std::string& s1, const std::string& s2) const;

    /**
     * 如果图中包含从 v1 到 v2 的边，则返回 true。
     * 若在图中找不到任一所给顶点，则返回 false。
     * @bigoh O(log V)
     */
    bool isNeighbor(const std::string& node1, const std::string& node2) const;

    /**
     * 如果图中包含从 v1 到 v2 的边，则返回 true。
     * 若任一所给顶点为空或在图中找不到，则返回 false。
     * @bigoh O(log V)
     */
    bool isNeighbor(NodeType* node1, NodeType* node2) const;

    /**
     * 如果图不包含顶点，则返回 <code>true</code>。
     * @bigoh O(1)
     */
    bool isEmpty() const;

    /**
     * 返回图中的节点数。
     * 等价于 size()。
     * @bigoh O(1)
     */
    int nodeCount() const;

    /**
     * 从图中删除从 v1 到 v2 的弧，通过端点名称指定。
     * 若有多条弧连接指定端点，则全部移除。
     * 若没有弧连接给定端点，或找不到给定弧，
     * 该调用不产生任何效果。
     * @bigoh O(E + log V)
     */
    void removeArc(const std::string& s1, const std::string& s2);

    /**
     * 从图中删除从 v1 到 v2 的弧，通过节点指针指定
     * 在其端点处。
     * 若有多条弧连接指定端点，则全部移除。
     * 若没有弧连接给定端点，或找不到给定弧，
     * 该调用不产生任何效果。
     * @bigoh O(E + log V)
     */
    void removeArc(NodeType* n1, NodeType* n2);

    /**
     * 从图中删除给定弧，通过弧指针指定。
     * 若有多条弧连接指定端点，则全部移除。
     * 若没有弧连接给定端点，或找不到给定弧，
     * 该调用不产生任何效果。
     *
     * 内存管理：使用完毕后，本代码会删除/释放 ArcType* 对象。
     * 无需（也不应）自行释放它。
     * @bigoh O(log E + log V)
     */
    void removeArc(ArcType* arc);

    /**
     * 从图中删除具有给定名称的节点。
     * 移除节点也会移除所有包含该节点的弧。
     * 如果传入的节点名称不属于该图，
     * 该调用不产生任何效果。
     * @bigoh O(E + log V)
     */
    void removeNode(const std::string& name);

    /**
     * 从图中删除节点，通过指针值指定。
     * 移除节点也会移除所有包含该节点的弧。
     * 如果传入的节点或名称为 null，或不属于该图，
     * 该调用不产生任何效果。
     *
     * 内存管理：使用完毕后，本代码会删除/释放 NodeType* 对象。
     * 无需（也不应）自行释放它。
     * @bigoh O(E + log V)
     */
    void removeNode(NodeType* node);

    /**
     * 从扫描器读取一条弧的数据。
     * <code>forward</code> 参数指向正向的弧。
     * 如果弧是无向的，<code>backward</code> 指向反向弧；
     * 对于有向弧，<code>backward</code> 指针为 <code>nullptr</code>。
     *
     * 此方法的默认实现为空。
     * 希望初始化弧中其他字段的客户端必须重写
     * 此方法，使其按情况初始化一条或两条弧。
     */
    virtual void scanArcData(TokenScanner &, ArcType* /*向前*/, ArcType* /*向后*/) {
        // 空
    }

    /**
     * 此方法读取图的一个“条目”，它可以是节点
     * 节点描述或弧描述。<code>scanGraphEntry</code>
     * 如果成功读取一个条目，此方法返回 <code>true</code>，否则
     * 在文件末尾或遇到无法解析的文本时返回 <code>false</code>
     * 识别为图条目。
     *
     * 节点条目由节点名称组成（名称可能带引号
     * 如果其中包含特殊字符），后面可选地跟随相关数据
     * 该节点。弧的描述具有以下形式之一：
     *
     * <pre>
     * n1 -> n2
     * n1 - n2
     * </pre>
     *
     * 任一形式后面都可跟随弧的数据。
     * 第一种形式创建一条有向弧；第二种创建两条弧，
     * 每个方向一条。
     *
     * 希望读取节点或弧数据的客户端必须重写空的
     * <code>scanNodeData</code> 和 <code>scanArcData</code> 的各版本
     * 包含在此接口中。
     */
    virtual bool scanGraphEntry(TokenScanner& scanner);

    /**
     * 从扫描器读取指定节点的数据。
     * 此方法的默认实现为空。
     * 希望根据标记初始化节点中其他字段的客户端
     * 流必须重写此方法。
     */
    virtual void scanNodeData(TokenScanner&, NodeType*) {
        /* 空 */
    }

    /**
     * 返回图中的节点数。
     * 等价于 nodeCount。
     * @bigoh O(1)
     */
    int size() const;

    /**
     * 将图转换为可打印的字符串表示。
     * @return 字符串，例如 <code>"{A, B, C, D, A - B, B - D, C - D}"</code>。
     * @bigoh O(V + E)
     */
    std::string toString() const;

    /**
     * 将弧的数据写入输出流。
     * 此方法的默认实现为空。
     * 希望存储弧中其他字段的客户端必须重写此方法
     * 方法，使其以 scanArcData 可读取的形式写入数据。
     */
    virtual void writeArcData(std::ostream&, ArcType*) const {
        // 空
    }

    /**
     * 将节点的数据写入输出流。
     * 此方法的默认实现为空。
     * 希望存储节点中其他字段的客户端必须重写此方法
     * 方法，使其以 scanNodeData 可读取的形式写入数据。
     */
    virtual void writeNodeData(std::ostream&, NodeType*) const {
        // 空
    }

    using graph_iterator = typename Set<NodeType *>::const_iterator;

    /**
     * 返回位于图中第一个顶点的 STL 迭代器。
     * @bigoh O(1)
     */
    graph_iterator begin() const {
        return _nodes.begin();
    }

    /**
     * 返回位于图中最后一个顶点之后的 STL 迭代器。
     * @bigoh O(1)
     */
    graph_iterator end() const {
        return _nodes.end();
    }

    /**
     * 用于比较两个图的关系运算符。
     * ==、!= 运算符要求 ValueType 定义 == 运算符
     * 以便测试元素是否相等。
     * @bigoh O(V log V + E log E)
     */
    bool operator ==(const Graph& graph2) const;

    /**
     * 用于比较两个图的关系运算符。
     * ==、!= 运算符要求 ValueType 定义 == 运算符
     * 以便测试元素是否相等。
     * @bigoh O(V log V + E log E)
     */
    bool operator !=(const Graph& graph2) const;

    /**
     * 用于比较两个图的关系运算符。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     * @bigoh O(V log V + E log E)
     */
    bool operator <(const Graph& graph2) const;

    /**
     * 用于比较两个图的关系运算符。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     * @bigoh O(V log V + E log E)
     */
    bool operator <=(const Graph& graph2) const;

    /**
     * 用于比较两个图的关系运算符。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     * @bigoh O(V log V + E log E)
     */
    bool operator >(const Graph& graph2) const;

    /**
     * 用于比较两个图的关系运算符。
     * <、>、<=、>= 运算符要求 ValueType 定义 < 运算符
     * 以便逐对比较各元素。
     * @bigoh O(V log V + E log E)
     */
    bool operator >=(const Graph& graph2) const;

private:
    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

    /**
     * 此模板类规定节点和弧的排序方式。
     * 节点按节点名称的字母顺序处理；弧则
     * 比较方式基本相同，先查看起始节点，然后
     * 然后，如果起始节点
     * 匹配。不过，这些函数只有在以下情况下才表示相等
     * 参数相同，即它们位于同一
     * 地址。例如，如果两条不同的弧连接同一对
     * 节点（在图抽象中完全合法，并且可以
     * 例如，可用于表示以下对象之间的多种出行方式：
     * 两个节点），这些弧并不相同。
     *
     * @private
     */
    class GraphComparator {
    public:
        bool operator ()(NodeType* n1, NodeType* n2) {
            return compare(n1, n2) < 0;
        }

        bool operator ()(ArcType* a1, ArcType* a2) {
            return compare(a1, a2) < 0;
        }
    };

    Set<NodeType*> _nodes{GraphComparator()}; /* 图中的节点集合 */
    Set<ArcType*> _arcs{GraphComparator()};   /* 图中的弧集合  */
    Map<std::string, NodeType*> _nodeMap;     /* 从名称到节点的映射     */

public:
    /**
     * 这些函数是类的公共接口的一部分，但
     * 在此定义，以避免给 Graph 类增加混淆。
     *
     * @private
     */
    Graph& operator =(const Graph& src);

    /**
     * 这些函数是类的公共接口的一部分，但
     * 在此定义，以避免给 Graph 类增加混淆。
     *
     * @private
     */
    Graph(const Graph& src);

    /**
     * 比较两个节点在集合中的排序顺序。
     *
     * @private
     */
    static int compare(NodeType* n1, NodeType* n2) {
        if (n1 == n2) {
            return 0;
        }
        if (n1->name < n2->name) {
            return -1;
        }
        if (n1->name > n2->name) {
            return +1;
        }
        return (n1 < n2) ? -1 : +1;
    }

    /**
     * 比较两条弧在集合中的排序顺序。
     *
     * @private
     */
    static int compare(ArcType* a1, ArcType* a2) {
        if (a1 == a2) {
            return 0;
        }
        NodeType* n1 = a1->start;
        NodeType* n2 = a2->start;
        if (n1 != n2) {
            return compare(n1, n2);
        }
        n1 = a1->finish;
        n2 = a2->finish;
        if (n1 != n2) {
            return compare(n1, n2);
        }
        return (a1 < a2) ? -1 : +1;
    }

private:
    void deepCopy(const Graph& src);
    NodeType* getExistingNode(const std::string& name, const std::string& member = "") const;
    int graphCompare(const Graph& graph2) const;
    bool isExistingArc(ArcType* arc) const;
    bool isExistingNode(NodeType* node) const;
    void verifyExistingNode(NodeType* node, const std::string& member = "") const;
    void verifyNotNull(void* p, const std::string& member = "") const;
    NodeType* scanNode(TokenScanner& scanner);
};

/*
 * 实现说明：Graph 构造函数
 * ---------------------------------------
 * 尽管 Graph 构造函数主体为空，但重要的
 * 工作由初始化器完成，它确保节点和
 * 为 arcs 集合提供正确的比较函数。
 */

template <typename NodeType, typename ArcType>
Graph<NodeType, ArcType>::Graph() {
    // 空
}

template <typename NodeType, typename ArcType>
Graph<NodeType, ArcType>::Graph(const Graph& src) {
    deepCopy(src);
}

/*
 * 实现说明：Graph 析构函数
 * --------------------------------------
 * 析构函数必须释放此图使用的所有堆存储，以
 * 表示节点和弧。clear 方法还必须回收
 * 这块内存，因此析构函数只需调用
 * 清除以执行工作。
 */
template <typename NodeType, typename ArcType>
Graph<NodeType, ArcType>::~Graph() {
    clear();
}

/*
 * 实现说明：addArc
 * ----------------------------
 * addArc 方法有三种形式，如以下内容所述
 * 接口。不过，每种方法形式的代码
 * 相当直接。
 */
template <typename NodeType, typename ArcType>
ArcType* Graph<NodeType, ArcType>::addArc(const std::string& s1, const std::string& s2) {
    return addArc(getExistingNode(s1, "addArc"), getExistingNode(s2, "addArc"));
}

template <typename NodeType, typename ArcType>
ArcType* Graph<NodeType, ArcType>::addArc(NodeType* n1, NodeType* n2) {
    verifyExistingNode(n1, "addArc");
    verifyExistingNode(n2, "addArc");
    ArcType* arc = getArc(n1, n2);
    if (arc) {
        return arc;
    } else {
        arc = new ArcType();
        arc->start = n1;
        arc->finish = n2;
        return addArc(arc);
    }
}

template <typename NodeType, typename ArcType>
ArcType* Graph<NodeType, ArcType>::addArc(ArcType* arc) {
    verifyNotNull(arc, "addArc");
    if (!isExistingNode(arc->start)) {
        addNode(arc->start);
    }
    if (!isExistingNode(arc->finish)) {
        addNode(arc->finish);
    }
    arc->start->arcs.add(arc);
    _arcs.add(arc);
    return arc;
}

/*
 * 实现说明：addNode
 * -----------------------------
 * addNode 方法有两种形式：一种创建节点
 * 从其名称，以及假定客户端已创建的版本
 * 新节点。无论哪种情况，实现都必须添加该节点
 * 图的节点集合，并添加名称到节点的关联
 * 到节点映射中。
 */
template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::addNode(const std::string& name) {
    NodeType* node = getNode(name);
    if (node) {
        return node;   // 顶点已存在
    }
    node = new NodeType();
    node->arcs = Set<ArcType*>(GraphComparator());
    node->name = name;
    return addNode(node);
}

template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::addNode(NodeType* node) {
    verifyNotNull(node, "addNode");
    NodeType* existingNode = getNode(node->name);
    if (existingNode) {
        *existingNode = *node;   // 从参数复制状态
        return existingNode;
    } else {
        _nodes.add(node);
        _nodeMap[node->name] = node;
        return node;
    }
}

template <typename NodeType, typename ArcType>
int Graph<NodeType, ArcType>::arcCount() const {
    return getArcSet().size();
}

template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::back() const {
    if (this->isEmpty()) {
        error("Graph::back: graph is empty");
    }
    return this->_nodes.back();
}

/*
 * 实现说明：clear
 * ---------------------------
 * clear 的实现首先释放
 * 各自的集合，然后使用 Set 类的 clear 方法
 * 确保这些集合为空。
 */
template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::clear() {
    for (NodeType* node : _nodes) {
        delete node;
    }
    for (ArcType* arc : _arcs) {
        delete arc;
    }
    _arcs.clear();
    _nodes.clear();
    _nodeMap.clear();
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::clearArcs() {
    Set<ArcType*> arcsCopy = getArcSet();   // 创建副本
    for (ArcType* arc : arcsCopy) {
        removeArc(arc);
    }
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::clearArcs(NodeType* node) {
    if (isExistingNode(node)) {
        Set<ArcType*> arcsCopy = getArcSet(node);   // 创建副本
        for (ArcType* arc : arcsCopy) {
            removeArc(arc);
        }
    }
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::clearArcs(const std::string& name) {
    Set<ArcType*> arcsCopy = getArcSet(name);   // 创建副本
    for (ArcType* arc : arcsCopy) {
        removeArc(arc);
    }
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::containsArc(NodeType* node1, NodeType* node2) const {
    return getArc(node1, node2) != nullptr;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::containsArc(const std::string& node1, const std::string& node2) const {
    return getArc(node1, node2) != nullptr;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::containsArc(ArcType* arc) const {
    if (!arc) {
        return false;
    } else {
        return this->getArcSet().contains(arc);
    }
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::containsNode(const std::string& name) const {
    return _nodeMap.containsKey(name);
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::containsNode(NodeType* node) const {
    if (node) {
        return _nodes.contains(node);
    } else {
        return false;
    }
}


template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::equals(const Graph<NodeType, ArcType>& graph2) const {
    return *this == graph2;
}

template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::front() const {
    if (this->isEmpty()) {
        error("Graph::front: graph is empty");
    }
    return this->_nodes.front();
}

template <typename NodeType, typename ArcType>
ArcType* Graph<NodeType, ArcType>::getArc(NodeType* node1, NodeType* node2) const {
    if (!containsNode(node1) || !containsNode(node2)) {
        return nullptr;
    }
    for (ArcType* arc : getArcSet(node1)) {
        if (arc->finish == node2) {
            return arc;
        }
    }
    return nullptr;
}

template <typename NodeType, typename ArcType>
ArcType* Graph<NodeType, ArcType>::getArc(const std::string& node1, const std::string& node2) const {
    return getArc(getNode(node1), getNode(node2));
}

template <typename NodeType, typename ArcType>
const Set<ArcType*>& Graph<NodeType, ArcType>::getArcSet() const {
    return _arcs;
}

template <typename NodeType, typename ArcType>
const Set<ArcType*>& Graph<NodeType, ArcType>::getArcSet(NodeType* node) const {
    if (isExistingNode(node)) {
        return node->arcs;
    } else {
        static Set<ArcType*> set;   // 空
        return set;
    }
}

template <typename NodeType, typename ArcType>
const Set<ArcType*>& Graph<NodeType, ArcType>::getArcSet(const std::string& name) const {
    return getArcSet(getNode(name));
}

template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::getExistingNode(const std::string& name, const std::string& member) const {
    NodeType* node = _nodeMap.get(name);
    if (!node) {
        error("Graph::" + member + ": no node named " + name);
    }
    return node;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isExistingArc(ArcType* arc) const {
    return arc && _arcs.contains(arc);
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isExistingNode(NodeType* node) const {
    return node && _nodeMap.containsKey(node->name) && _nodeMap.get(node->name) == node;
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::verifyExistingNode(NodeType* node, const std::string& member) const {
    verifyNotNull(node, member);
    if (!isExistingNode(node)) {
        error("Graph::" + member + ": node not found in graph");
    }
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::verifyNotNull(void* p, const std::string& member) const {
    if (!p) {
        error("Graph::" + member + ": parameter cannot be null");
    }
}

template <typename NodeType, typename ArcType>
const Set<ArcType*> Graph<NodeType, ArcType>::getInverseArcSet(NodeType* node) const {
    Set<ArcType*> set;
    if (isExistingNode(node)) {
        for (ArcType* arc : getArcSet()) {
            if (arc->finish == node) {
                set.add(arc);
            }
        }
    }
    return set;
}

template <typename NodeType, typename ArcType>
const Set<ArcType*> Graph<NodeType, ArcType>::getInverseArcSet(const std::string& nodeName) const {
    return getInverseArcSet(getNode(nodeName));
}

template <typename NodeType, typename ArcType>
Set<std::string> Graph<NodeType, ArcType>::getInverseNeighborNames(NodeType* node) const {
    Set<std::string> set;
    if (isExistingNode(node)) {
        for (ArcType* arc : getArcSet()) {
            if (arc->finish == node) {
                set.add(arc->start->name);
            }
        }
    }
    return set;
}

template <typename NodeType, typename ArcType>
Set<std::string> Graph<NodeType, ArcType>::getInverseNeighborNames(const std::string& name) const {
    return getInverseNeighborNames(getNode(name));
}

template <typename NodeType, typename ArcType>
Set<NodeType*> Graph<NodeType, ArcType>::getInverseNeighbors(NodeType* node) const {
    Set<NodeType*> set;
    if (isExistingNode(node)) {
        for (ArcType* arc : getArcSet()) {
            if (arc->finish == node) {
                set.add(arc->start);
            }
        }
    }
    return set;
}

template <typename NodeType, typename ArcType>
Set<NodeType*> Graph<NodeType, ArcType>::getInverseNeighbors(const std::string& nodeName) const {
    return getInverseNeighbors(getNode(nodeName));
}

template <typename NodeType, typename ArcType>
Set<std::string> Graph<NodeType, ArcType>::getNeighborNames(NodeType* node) const {
    Set<std::string> neighbors;
    if (isExistingNode(node)) {
        for (ArcType* arc : node->arcs) {
            neighbors.add(arc->finish->name);
        }
    }
    return neighbors;
}

template <typename NodeType, typename ArcType>
Set<std::string> Graph<NodeType, ArcType>::getNeighborNames(const std::string& name) const {
    return getNeighborNames(getNode(name));
}

/*
 * 实现说明：getNeighbors
 * ----------------------------------
 * 此实现每次都会重新计算集合，这在合理范围内
 * 如果节点度数较小，则效率较高。
 */
template <typename NodeType, typename ArcType>
Set<NodeType*> Graph<NodeType, ArcType>::getNeighbors(NodeType* node) const {
    Set<NodeType*> nodesResult{GraphComparator{}};
    if (isExistingNode(node)) {
        for (ArcType* arc : node->arcs) {
            nodesResult.add(arc->finish);
        }
    }
    return nodesResult;
}

template <typename NodeType, typename ArcType>
Set<NodeType*> Graph<NodeType, ArcType>::getNeighbors(const std::string& name) const {
    return getNeighbors(getNode(name));
}

/*
 * 实现说明：getNode、getExistingNode
 * ----------------------------------------------
 * getNode 方法只是从映射中查找名称，这会正确地
 * 如果找不到名称，则返回 nullptr。以下对象中的其他方法
 * 实现中应改为调用私有方法 getExistingNode，
 * 它会检查 null 值并报告错误。
 */
template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::getNode(const std::string& name) const {
    return _nodeMap.get(name);
}

template <typename NodeType, typename ArcType>
Set<std::string> Graph<NodeType, ArcType>::getNodeNames() const {
    Set<std::string> nodeNames;
    for (NodeType* node : _nodes) {
        nodeNames.add(node->name);
    }
    return nodeNames;
}

/*
 * 实现说明：getNodeSet、getArcSet
 * -------------------------------------------
 * 这些方法只是返回客户端请求的集合。
 * 为提高效率，集合通过引用返回，因为这样做
 * 无需复制集合。
 */
template <typename NodeType, typename ArcType>
const Set<NodeType*>& Graph<NodeType, ArcType>::getNodeSet() const {
    return _nodes;
}

/*
 * 实现说明：isConnected
 * ---------------------------------
 * 如果从 n1 出发的任一弧终止于 n2，则节点 n1 与 n2 相连。
 * 此方法的两个版本允许以以下任一种方式指定节点：
 * 通过节点指针或名称。
 */
template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isConnected(NodeType* n1, NodeType* n2) const {
    // 不要在此调用 verifyExistingNode，因为它会抛出错误
    // 如果找不到 n1 或 n2；调用应当返回 false
    if (!isExistingNode(n1) || !isExistingNode(n2)) {
        return false;
    }
    for (ArcType* arc : n1->arcs) {
        if (arc->finish == n2) {
            return true;
        }
    }
    return false;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isConnected(const std::string& s1, const std::string& s2) const {
    // 不要在此调用 getExistingNode，因为它会抛出错误
    // 如果找不到 s1 或 s2；调用应当返回 false
    return isConnected(_nodeMap.get(s1), _nodeMap.get(s2));
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isNeighbor(const std::string& node1, const std::string& node2) const {
    return isConnected(node1, node2);
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isNeighbor(NodeType* node1, NodeType* node2) const {
    return isConnected(node1, node2);
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::isEmpty() const {
    return _nodes.isEmpty();
}

template <typename NodeType, typename ArcType>
int Graph<NodeType, ArcType>::nodeCount() const {
    return getNodeSet().size();
}

/*
 * 实现说明：removeArc
 * -------------------------------
 * 这些方法从图中移除弧，通常只需
 * 本质上是从两个集合中移除该弧：图中的弧集合以及
 * 整个图以及起始节点中的弧集合。该
 * 不过，对于通过端点指定弧的删除方法，
 * 必须考虑可能存在多个
 * 这样的弧并删除全部。
 */
template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeArc(const std::string& s1, const std::string& s2) {
    // 不要在此调用 getExistingNode，因为它会抛出错误
    // 如果找不到 s1 或 s2；调用应当不产生任何效果
    removeArc(_nodeMap.get(s1), _nodeMap.get(s2));
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeArc(NodeType* n1, NodeType* n2) {
    // 不要在此调用 verifyExistingNode，因为它会抛出错误
    // 如果找不到 n1 或 n2；调用应当不产生任何效果
    if (!isExistingNode(n1) || !isExistingNode(n2)) {
        return;
    }
    Vector<ArcType*> toRemove;
    for (ArcType* arc : _arcs) {
        if (arc->start == n1 && arc->finish == n2) {
            toRemove.add(arc);
        }
    }
    for (ArcType* arc : toRemove) {
        removeArc(arc);
    }
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeArc(ArcType* arc) {
    if (!isExistingArc(arc)) {
        return;
    }
    arc->start->arcs.remove(arc);
    _arcs.remove(arc);
    delete arc;
}

/*
 * 实现说明：removeNode
 * --------------------------------
 * removeNode 方法必须移除指定节点，但必须
 * 还要移除图中包含该节点的所有弧。为避免
 * 由于在迭代期间更改节点集合，此实现会创建
 * 需要删除的弧向量。
 */
template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeNode(const std::string& name) {
    // 不要在此调用 getExistingNode，因为它会抛出错误
    // 如果找不到 name；调用应当不产生任何效果
    removeNode(_nodeMap.get(name));
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::removeNode(NodeType* node) {
    // 不要在此调用 verifyExistingNode，因为它会抛出错误
    // 如果找不到节点；调用应当不产生任何效果
    if (!isExistingNode(node)) {
        return;
    }
    Vector<ArcType*> toRemove;
    for (ArcType* arc : _arcs) {
        if (arc->start == node || arc->finish == node) {
            toRemove.add(arc);
        }
    }
    for (ArcType* arc : toRemove) {
        removeArc(arc);
    }
    _nodes.remove(node);
    _nodeMap.remove(node->name);
    delete node;
}

/*
 * 实现说明：scanGraphEntry
 * ------------------------------------
 * scanGraphEntry 及其辅助方法接收一个已
 * 初始化为输入流，并启用 ignoreWhitespace 选项，
 * 已设置 scanStrings 和 scanNumbers。
 */
template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::scanGraphEntry(TokenScanner& scanner) {
    NodeType* n1 = scanNode(scanner);
    if (!n1) {
        return false;
    }
    std::string op = scanner.nextToken();
    if (op != "-" && op != "->") {
        scanner.saveToken(op);
        return true;
    }
    NodeType* n2 = scanNode(scanner);
    if (!n2) {
        return false;
    }
    ArcType* forward = new ArcType();
    forward->start = n1;
    forward->finish = n2;
    addArc(forward);
    ArcType* backward = nullptr;
    if (op == "-") {
        backward = new ArcType();
        backward->start = n2;
        backward->finish = n1;
        addArc(backward);
    }
    scanArcData(scanner, forward, backward);
    return true;
}

template <typename NodeType, typename ArcType>
NodeType* Graph<NodeType, ArcType>::scanNode(TokenScanner& scanner) {
    std::string token = scanner.nextToken();
    switch (scanner.getTokenType(token)) {
    case TokenScanner::WORD:
        break;
    case TokenScanner::STRING:
        token = scanner.getStringValue(token);
        break;
    default:
        scanner.saveToken(token);
        return nullptr;
    }
    NodeType* node = getNode(token);
    if (!node) {
        node = new NodeType();
        node->name = token;
        scanNodeData(scanner, node);
        addNode(node);
    }
    return node;
}

/*
 * 实现说明：size、isEmpty
 * -----------------------------------
 * 这些方法根据节点集合定义，因此实现
 * 只是将请求转发到那里。请注意，以下情况不可能发生
 * 若图中没有节点，则图不可能包含弧。
 */
template <typename NodeType, typename ArcType>
int Graph<NodeType, ArcType>::size() const {
    return _nodes.size();
}

template <typename NodeType, typename ArcType>
std::string Graph<NodeType, ArcType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

/*
 * 实现说明：operator =、复制构造函数
 * -------------------------------------------------
 * 这些方法确保复制图时会创建一个全新的
 * 节点和弧的并行结构。
 */
template <typename NodeType, typename ArcType>
Graph<NodeType,ArcType>&
Graph<NodeType, ArcType>::operator =(const Graph& src) {
    if (this != &src) {
        clear();
        deepCopy(src);
    }
    return *this;
}

/*
 * 私有方法：deepCopy
 * ------------------------
 * 从复制构造函数和 operator= 中提取的公共代码，用于
 * 从另一个图复制内容。
 */
template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::deepCopy(const Graph& src) {
    for (NodeType* oldNode : src._nodes) {
        NodeType* newNode = new NodeType();
        *newNode = *oldNode;
        newNode->arcs.clear();
        addNode(newNode);
    }
    for (ArcType* oldArc : src._arcs) {
        ArcType* newArc = new ArcType();
        *newArc = *oldArc;
        newArc->start = getExistingNode(oldArc->start->name, "deepCopy");
        newArc->finish = getExistingNode(oldArc->finish->name, "deepCopy");
        addArc(newArc);
    }
}


/**
 * 使用 <、<=、==、!=、>、>= 关系运算符比较两个图。
 * 比较顶点，包括其相邻弧。
 *
 * @private
 */
template <typename NodeType, typename ArcType>
int Graph<NodeType, ArcType>::graphCompare(const Graph<NodeType, ArcType>& graph2) const {
    // 优化：如果确实是同一图，则返回 true
    if (this == &graph2) {
        return 0;
    }

    auto itr1 = begin();
    auto itr2 = graph2.begin();
    auto g1end = end();
    auto g2end = graph2.end();

    while (itr1 != g1end && itr2 != g2end) {
        // 逐对比较迭代器中的各元素
        NodeType* node1 = *itr1;
        NodeType* node2 = *itr2;

        // 优化：如果确实是同一节点，则相等；无需比较
        if (node1 != node2) {
            // 首先检查名称
            if (node1->name != node2->name) {
                return node1->name.compare(node2->name);
            }

            // 然后两两检查所有弧
            auto eitr1 = node1->arcs.begin();
            auto eitr2 = node2->arcs.begin();
            auto e1end = node1->arcs.end();
            auto e2end = node2->arcs.end();
            while (eitr1 != e1end && eitr2 != e2end) {
                ArcType* arc1 = *eitr1;
                ArcType* arc2 = *eitr2;

                // 优化：如果确实是同一条弧，则相等；无需比较
                if (arc1 != arc2) {
                    // 先检查起始顶点名称，再检查终止顶点名称
                    if (arc1->start->name != arc2->start->name) {
                        return arc1->start->name.compare(arc2->start->name);
                    } else if (arc1->finish->name != arc2->finish->name) {
                        return arc1->finish->name.compare(arc2->finish->name);
                    }
                }
                eitr1++;
                eitr2++;
            }

            // 如果执行到这里，表示我的所有内容都与 graph2 匹配，因此要么弧相等，
            // 或其中一个更短（弧更少），因此更小
            if (eitr1 == e1end && eitr2 == e2end) {
                // 继续
            } else if (eitr1 == e1end) {
                return -1;
            } else {
                return 1;
            }
        }

        // 如果执行到这里，表示这两个顶点及其出弧
        // 两者相等；因此前进到下一个元素
        itr1++;
        itr2++;
    }

    // 如果执行到这里，表示我的所有内容都与 graph2 匹配，因此要么相等，
    // 或其中一个更短（顶点更少），因此更小
    if (itr1 == g1end && itr2 == g2end) {
        return 0;
    } else if (itr1 == g1end) {
        return -1;
    } else {
        return 1;
    }
}

/*
 * 运算符
 */
template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::operator ==(const Graph& graph2) const {
    // 优化：如果大小不同，则图不相等
    if (_nodes.size() != graph2._nodes.size()
            || _arcs.size() != graph2._arcs.size()
            || _nodeMap.size() != graph2._nodeMap.size()) {
        return false;
    }
    return graphCompare(graph2) == 0;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::operator !=(const Graph& graph2) const {
    return !(*this == graph2);
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::operator <(const Graph& graph2) const {
    return graphCompare(graph2) < 0;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::operator <=(const Graph& graph2) const {
    return graphCompare(graph2) <= 0;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::operator >(const Graph& graph2) const {
    return graphCompare(graph2) > 0;
}

template <typename NodeType, typename ArcType>
bool Graph<NodeType, ArcType>::operator >=(const Graph& graph2) const {
    return graphCompare(graph2) >= 0;
}

/**
 * 将给定图写入给定输出流。
 * 图的插入和提取运算符更加复杂
 * 比标准集合类型更复杂，因为节点和弧可以
 * 包含客户端特定数据。为确保此信息
 * 为了让这些运算符正确写入和读取，客户端必须重写
 * 方法 writeNodeData、writeArcData、scanNodeData 和 scanArcData。
 */
template <typename NodeType, typename ArcType>
std::ostream& operator <<(std::ostream& os, const Graph<NodeType, ArcType>& g) {
    os << "{";
    bool started = false;
    for (NodeType* node : g.getNodeSet()) {
        if (started) {
            os << ", ";
        }
        writeGenericValue(os, node->name, stringIsInteger(node->name) || stringIsReal(node->name));
        g.writeNodeData(os, node);
        started = true;
    }
    for (ArcType* arc : g.getArcSet()) {
        os << ", ";
        writeGenericValue(os, arc->start->name, stringIsInteger(arc->start->name) || stringIsReal(arc->start->name));
        os << " -> ";
        writeGenericValue(os, arc->finish->name, stringIsInteger(arc->finish->name) || stringIsReal(arc->finish->name));
        g.writeArcData(os, arc);
    }
    return os << "}";
}

/**
 * 从给定输入流读取给定图。
 * 图的插入和提取运算符更加复杂
 * 比标准集合类型更复杂，因为节点和弧可以
 * 包含客户端特定数据。为确保此信息
 * 为了让这些运算符正确写入和读取，客户端必须重写
 * 方法 writeNodeData、writeArcData、scanNodeData 和 scanArcData。
 */
template <typename NodeType, typename ArcType>
std::istream& operator >>(std::istream& is, Graph<NodeType, ArcType>& g) {
    TokenScanner scanner(is);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.scanStrings();
    scanner.addOperator("->");
    std::string token = scanner.nextToken();
    if (token != "{") {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    g.clear();
    while (g.scanGraphEntry(scanner)) {
        token = scanner.nextToken();
        if (token == "}") {
            scanner.saveToken(token);
        } else if (token != ",") {
            is.setstate(std::ios_base::failbit);
            return is;
        }
    }
    token = scanner.nextToken();
    if (token != "}") {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    return is;
}

/**
 * 用于图的模板哈希函数。
 */
template <typename NodeType, typename ArcType>
int hashCode(const Graph<NodeType, ArcType>& graph) {
    int code = hashSeed();
    for (NodeType* node : graph) {
        code = hashMultiplier() * code + hashCode(node->name);
    }
    for (ArcType* arc : graph.getArcSet()) {
        code = hashMultiplier() * code + hashCode(arc->start->name);
        code = hashMultiplier() * code + hashCode(arc->finish->name);
    }
    return (code & hashMask());
}

#endif // _graph_h
