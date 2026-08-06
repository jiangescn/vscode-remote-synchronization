/*
 * 文件：basicgraph.h
 * ------------------
 * 此文件包含一些实用图类型的声明，
 * 具体来说，是典型图中使用的 Vertex 和 Edge 结构。
 * 在课堂上一起完成。我们还声明 BasicGraph，它是
 * 使用 Vertex 和 Edge 作为类型参数的 Stanford Graph 类。
 *
 * 由于该类是模板，大多数成员都在此文件中实现。
 * 某些非模板成员的实现见 BasicGraph.cpp。
 */


#ifndef _basicgraph_h
#define _basicgraph_h

#include <initializer_list>
#include <sstream>
#include <string>
#include <utility>

#include "gmath.h"
#include "graph.h"
#include "grid.h"
#include "hashset.h"
#include "linkedlist.h"
#include "observable.h"
#include "set.h"
#include "vector.h"

/**
 * Vertex/Edge 结构的前向声明，使它们可以相互引用
 * 彼此互相连接。
 * @private
 */
template <typename V = void*, typename E = void*>
class EdgeGen;

/**
 * Graph 类模板所需的标准 Vertex（Node）结构实现。
 * 每个 Vertex 结构表示图中的一个顶点。
 */
template <typename V = void*, typename E = void*>
class VertexGen : public Observable<int> {
public:
    /**
     * 顶点名称，以字符串表示。
     */
    std::string name;

    /**
     * 从此顶点向邻居发出的边。
     */
    Set<EdgeGen<V, E>*> arcs;     // Stanford Graph 所必需；

    /**
     * 从此顶点向邻居发出的边；
     * “arcs”成员的别名。
     */
    Set<EdgeGen<V, E>*>& edges;

#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    /**
     * 到达此顶点的成本；初始为 0。
     */
    double cost;

    /**
     * “cost”成员的别名。
     */
    double& weight;

    /**
     * 此顶点此前是否访问过；初始为 false。
     */
    bool visited;

    /**
     * 此顶点之前的顶点；初始为 null。
     */
    VertexGen* previous;
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS

    /**
     * 以下指针可指向顶点所需的任何额外数据。
     * 此字段通常不需要，可以忽略。
     */
    V data;

    /**
     * @private
     */
    V& extraData;       // data 的别名；它们是同一个字段

    /**
     * 构造具有给定名称的顶点。
     */
    VertexGen(const std::string& name = "");

    /**
     * 复制构造函数。
     */
    VertexGen(const VertexGen& other);

    /**
     * 释放此顶点动态分配的任何内存。
     */
    ~VertexGen();

    /**
     * 返回此顶点的颜色（如果有）。初始为 WHITE。
     */
    /* 颜色 */ int getColor() const;

    /**
     * 将此顶点的附加数据重置为初始状态。
     * 具体来说，将 cost 设为 0、visited 设为 false、previous 设为 nullptr。
     */
    void resetData();

    /**
     * 将此顶点的颜色设为给定颜色。
     * 颜色必须是 WHITE、GRAY、YELLOW 或 GREEN 之一。
     * 之后调用 getColor 将返回你在此传入的颜色。
     */
    void setColor(/* 颜色 */ int c);

    /**
     * 返回此顶点用于调试的字符串表示，例如
     * “Vertex{name=r13c42, cost=11, visited=true, previous=r12c41, neighbors={r12c41, r12c43}}”。
     */
    std::string toString() const;

    /**
     * 复制赋值运算符。
     */
    VertexGen& operator =(const VertexGen& other);

    /**
     * 移动赋值运算符。
     */
    VertexGen& operator =(VertexGen&& other);

private:
    /* 颜色 */ int _color;   // 传给 setColor 的顶点颜色
};

/**
 * 使顶点可打印到输出流。
 * 有关输出格式示例，请参阅 toString。
 * 请注意，打印顶点不同于打印顶点指针。
 * 若尝试输出指针，只会看到其十六进制地址。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const VertexGen<V, E>& v);

/**
 * Graph 类模板所需的标准 Edge（Arc）结构实现。
 * 每个 Edge 结构表示图中的一条边。
 */
template <typename V, typename E>
class EdgeGen {
public:
    /**
     * 边的起始顶点。
     */
    VertexGen<V, E>* start;

    /**
     * 边的终止顶点。
     */
    VertexGen<V, E>* finish;   // Stanford Graph 所必需；

    /**
     * finish 的别名；它们是同一个字段。
     */
    VertexGen<V, E>*& end;

    /**
     * 边的权重；默认为 0。
     */
    double cost;

    /**
     * “cost”成员的别名。
     */
    double& weight;

#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    /**
     * 此边此前是否访问过；初始为 false。
     */
    bool visited;
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS

    /**
     * 可指向顶点所需任何额外数据的指针。
     * 此字段通常不需要，可以忽略。
     */
    void* data;

    /**
     * “data”成员的别名。
     */
    void*& extraData;

    /**
     * 在给定起点/终点顶点之间构造具有以下属性的新边：
     * 给定的成本。
     */
    EdgeGen(VertexGen<V, E>* start = nullptr, VertexGen<V, E>* finish = nullptr, double cost = 0.0);

    /**
     * 释放此边动态分配的任何内存。
     */
    ~EdgeGen();

    /**
     * 将此边的附加数据重置为初始状态。
     */
    void resetData();

    /**
     * 返回此边用于调试的字符串表示，例如
     * “Arc{start=r12c42, finish=r12c41, cost=0.75}”。
     */
    std::string toString() const;

    /**
     * 复制赋值运算符。
     */
    EdgeGen& operator =(const EdgeGen& other);

    /**
     * 移动赋值运算符。
     */
    EdgeGen& operator =(EdgeGen&& other);
};

/**
 * 使边可打印到输出流。
 * 有关输出格式示例，请参阅 toString。
 * 请注意，打印边不同于打印边指针。
 * 若尝试输出指针，只会看到其十六进制地址。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const EdgeGen<V, E>& edge);


/**
 * BasicGraph 基本上只是使用 Vertex 和 Edge 对 Graph 的实例化
 * 作为其模板参数。它还添加了一些便利函数，例如
 * 以及使用更熟悉的等价名称镜像“addArc”等成员
 * 例如 "addEdge"。
 *
 * 还有一些与邻居相关的便捷函数，例如 isNeighbor。
 * BasicGraph 包含一个名为 isReachable 的 DFS 实现，在以下位置找不到
 * 在标准 Stanford Graph 类中。
 *
 * 还添加了若干函数，使边更便于使用：
 * 使用 getEdge(v1, v2) 获取给定顶点对之间的边，
 * 并使用 getInverseEdge(edge) 获取给定边 v1 -> v2 的反向边 v2 -> v1。
 */
template <typename V = void*, typename E = void*>
class BasicGraphGen : public Graph<VertexGen<V, E>, EdgeGen<V, E>> {
public:
    /**
     * 构造新的空图。
     * @bigoh O(1)
     */
    BasicGraphGen();

    /**
     * 构造包含给定顶点的新图。
     * @bigoh O(V)
     */
    BasicGraphGen(std::initializer_list<std::string> vertexList);

    /**
     * 向图中添加一条从顶点 v1 到顶点 v2 的有向边。
     * 注意，同一对顶点之间允许存在多条边。
     *
     * 返回指向边的指针，但客户端无需保存该指针；
     * 之后可调用 getEdge 并传入两个顶点，再次获取该指针。
     *
     * 等价于 addNode。
     *
     * @return 指向所创建边的指针
     * @bigoh O(log V + log E)
     */
    EdgeGen<V, E>* addEdge(const std::string& v1, const std::string& v2, double cost = 0.0, bool directed = true);

    /**
     * 向图中添加一条从顶点 v1 到顶点 v2 的有向边。
     * 若在图中找不到任一顶点，则将该顶点添加到图中。
     * 注意，同一对顶点之间允许存在多条边。
     *
     * 返回指向边的指针，但客户端无需保存该指针；
     * 之后可调用 getEdge 并传入两个顶点，再次获取该指针。
     *
     * 等价于 addNode。
     *
     * @return 指向所创建边的指针
     * @throw 如果任一顶点为空，则抛出 ErrorException
     * @bigoh O(log V + log E)
     */
    EdgeGen<V, E>* addEdge(VertexGen<V, E>* v1, VertexGen<V, E>* v2, double cost = 0.0, bool directed = true);

    /**
     * 将给定有向边从顶点 v1 到顶点 v2 添加到图中。
     * 若在图中找不到任一顶点，则将该顶点添加到图中。
     * 注意，同一对顶点之间允许存在多条边。
     *
     * 返回指向边的指针，但客户端无需保存该指针；
     * 之后可调用 getEdge 并传入两个顶点，再次获取该指针。
     *
     * 等价于 addNode。
     *
     * @return 指向所创建边的指针
     * @throw 如果任一顶点为空，则抛出 ErrorException
     * @bigoh O(log V + log E)
     */
    EdgeGen<V, E>* addEdge(EdgeGen<V, E>* e, bool directed = true);

    /**
     * 若图中尚不存在同名顶点，则向图中添加顶点。
     * 此方法的这个版本接受字符串作为顶点名称，
     * 创建适当类型的新顶点并初始化其字段。
     * 返回指向顶点的指针，但客户端无需存储该指针；
     * 之后可以通过调用 getVertex 并传入相同名称再次获取该指针。
     *
     * 图中的顶点必须具有唯一名称。
     * 若此图已包含给定名称的顶点，
     * 不会添加该顶点，并且图的状态不会改变。
     *
     * 等价于 addNode。
     *
     * @return 指向所创建顶点的指针
     * @bigoh O(log V)
     */
    VertexGen<V, E>* addVertex(const std::string& name);

    /**
     * 若图中尚不存在同名顶点，则向图中添加顶点。
     * 此方法的这个版本接受字符串作为顶点名称，
     * 创建适当类型的新顶点并初始化其字段。
     * 另一个接受表示顶点及其数据的结构。
     * 返回指向顶点的指针，但客户端无需存储该指针；
     * 之后可以通过调用 getVertex 并传入相同名称再次获取该指针。
     *
     * 图中的顶点必须具有唯一名称。
     * 若此图已包含给定名称的顶点，
     * 不会添加该顶点，并且图的状态不会改变。
     *
     * 调用此函数时，你将放弃对 Vertex 的所有权
     * 将该结构的生命周期绑定到图；图使用完后会释放它。
     *
     * 等价于 addNode。
     *
     * @return 指向所创建顶点的指针
     * @throw 如果 vertex 为 null，则抛出 ErrorException
     * @bigoh O(log V)
     */
    VertexGen<V, E>* addVertex(VertexGen<V, E>* v);

    /**
     * 从图中删除所有边。
     * 释放内部作为堆存储分配的任何边对象。
     *
     * 等价于 clearArcs。
     * @bigoh O(E log E)
     */
    void clearEdges();

    /**
     * 从图中移除给定顶点的所有出边。
     * 顶点本身不会被移除。
     * 如果该顶点为 null 或在图中找不到，则不产生任何效果。
     *
     * 等价于 clearArcs。
     * @bigoh O(E log E)
     * @bigoh O(log V + E)
     */
    void clearEdges(VertexGen<V, E>* v);

    /**
     * 从图中移除给定顶点的所有出边。
     * 顶点本身不会被移除。
     * 如果在图中找不到该顶点，则不产生任何效果。
     *
     * 等价于 clearArcs。
     * @bigoh O(E log E)
     */
    void clearEdges(const std::string& v);

    /**
     * 如果图中存在从 v1 到 v2 的边，则返回 true。
     * 若任一所给顶点为空或在图中找不到，则返回 false。
     *
     * 等价于 containsArc。
     * @bigoh O(log E)
     */
    bool containsEdge(VertexGen<V, E>* v1, VertexGen<V, E>* v2) const;

    /**
     * 如果图中存在从 v1 到 v2 的边，则返回 true。
     * 若在图中找不到任一所给顶点，则返回 false。
     *
     * 等价于 containsArc。
     * @bigoh O(log E)
     */
    bool containsEdge(const std::string& v1, const std::string& v2) const;

    /**
     * 如果图包含给定边，则返回 true。
     * 如果边结构为 null，则返回 false。
     *
     * 等价于 containsArc。
     * @bigoh O(log E)
     */
    bool containsEdge(EdgeGen<V, E>* edge) const;

    /**
     * 返回图是否包含给定名称的顶点。
     *
     * 等价于 containsNode。
     * @bigoh O(log V)
     */
    bool containsVertex(const std::string& name) const;

    /**
     * 返回图是否包含给定顶点。
     * 如果传入空指针，则返回 false。
     *
     * 等价于 containsNode。
     * @bigoh O(log V)
     */
    bool containsVertex(VertexGen<V, E>* v) const;

    /**
     * 返回图中的边数量。
     *
     * 等价于 arcCount。
     * @bigoh O(log V)
     */
    int edgeCount() const;

    /**
     * 返回表示图中从 v1 到 v2 的边的结构。
     * 如果提供的任一顶点为 null 或在图中找不到，函数将返回 nullptr。
     * 若给定顶点对之间有多条边，返回哪一条边未作规定。
     *
     * 等价于 getArc。
     *
     * @param v1 起始顶点
     * @param v2 结束顶点
     * @return 从 v1 到 v2 的边；若不存在，则为 nullptr
     * @bigoh O(log V + log E)
     */
    EdgeGen<V, E>* getEdge(VertexGen<V, E>* v1, VertexGen<V, E>* v2) const;

    /**
     * 返回表示图中从 v1 到 v2 的边的结构。
     * 如果提供的任一顶点在图中找不到，函数将返回 nullptr。
     * 若给定顶点对之间有多条边，返回哪一条边未作规定。
     *
     * 等价于 getArc。
     *
     * @param v1 起始顶点
     * @param v2 结束顶点
     * @return 从 v1 到 v2 的边；若不存在，则为 nullptr
     * @bigoh O(log V + log E)
     */
    EdgeGen<V, E>* getEdge(const std::string& v1, const std::string& v2) const;

    /**
     * 返回图中所有边的集合。
     *
     * 等价于 getArcSet。
     * @bigoh O(1)
     */
    const Set<EdgeGen<V, E>*>& getEdgeSet() const;

    /**
     * 返回从指定顶点出发的所有边的集合。
     * 若提供的顶点为空或在图中找不到，
     * 该函数会返回空集合。
     *
     * 等价于 getArcSet。
     * @bigoh O(1)
     */
    const Set<EdgeGen<V, E>*>& getEdgeSet(VertexGen<V, E>* v) const;

    /**
     * 返回从指定顶点出发的所有边的集合。
     * 如果提供的顶点在图中找不到，
     * 该函数会返回空集合。
     *
     * 等价于 getArcSet。
     * @bigoh O(1)
     */
    const Set<EdgeGen<V, E>*>& getEdgeSet(const std::string& v) const;

    /**
     * 返回给定边的反向边；
     * 也就是说，如果指定边 e 从 v1 开始并在 v2 结束，
     * 将返回从 v2 开始并在 v1 结束的边，
     * 若图中存在这样的边。
     *
     * 若提供的边为 nullptr、在图中找不到，
     * 或不存在逆矩阵，函数将返回 nullptr。
     *
     * 若给定顶点对之间有多条边，
     * 未规定将返回其中哪条边。
     *
     * 等价于 getInverseEdge。
     * @bigoh O(E)
     */
    EdgeGen<V, E>* getInverseArc(EdgeGen<V, E>* edge) const;

    /**
     * 返回给定边的反向边；
     * 也就是说，如果指定边 e 从 v1 开始并在 v2 结束，
     * 将返回从 v2 开始并在 v1 结束的边，
     * 若图中存在这样的边。
     *
     * 若提供的边为 nullptr、在图中找不到，
     * 或不存在逆矩阵，函数将返回 nullptr。
     *
     * 若给定顶点对之间有多条边，
     * 未规定将返回其中哪条边。
     *
     * 等价于 getInverseArc。
     * @bigoh O(E)
     */
    EdgeGen<V, E>* getInverseEdge(EdgeGen<V, E>* edge) const;

    /**
     * 返回图中终止于指定顶点的所有边的集合。
     * 若提供的顶点为空或在图中找不到，
     * 该函数会返回空集合。
     *
     * 等价于 getInverseArcSet。
     * @bigoh O(E)
     */
    const Set<EdgeGen<V, E>*> getInverseEdgeSet(VertexGen<V, E>* v) const;

    /**
     * 返回图中终止于指定顶点的所有边的集合。
     * 若提供的顶点为空或在图中找不到，
     * 该函数会返回空集合。
     *
     * 等价于 getInverseArcSet。
     * @bigoh O(E)
     */
    const Set<EdgeGen<V, E>*> getInverseEdgeSet(const std::string& v) const;

    /**
     * 按名称在图中查找顶点，并返回指向它的指针
     * 其内部数据结构。
     * 如果不存在指定名称的顶点，则返回 nullptr。
     * @bigoh O(log V)
     */
    VertexGen<V, E>* getVertex(const std::string& name) const;

    /**
     * 返回图中所有顶点名称的集合。
     * 顶点将按名称以区分大小写的字母顺序排序。
     * @bigoh O(V log V)
     */
    Set<std::string> getVertexNames() const;

    /**
     * 返回图中所有顶点的集合。
     * 顶点将按名称以区分大小写的字母顺序排序。
     * @bigoh O(V log V)
     */
    const Set<VertexGen<V, E>*>& getVertexSet() const;

    /**
     * 从图中移除从 v1 到 v2 的边。
     * 若有多条边连接指定端点，则全部移除。
     * 如果提供的任一顶点在图中找不到，
     * 调用此函数不会对图产生任何影响。
     * @bigoh O(E + log V)
     */
    void removeEdge(const std::string& v1, const std::string& v2, bool directed = true);

    /**
     * 从图中移除从 v1 到 v2 的边。
     * 若有多条边连接指定端点，则全部移除。
     * 如果提供的任一顶点为 null 或在图中找不到，
     * 调用此函数不会对图产生任何影响。
     * @bigoh O(E + log V)
     */
    void removeEdge(VertexGen<V, E>* v1, VertexGen<V, E>* v2, bool directed = true);

    /**
     * 从图中删除给定边。
     * 如果提供的边在图中找不到，
     * 调用此函数不会对图产生任何影响。
     * @bigoh O(log E + log V)
     */
    void removeEdge(EdgeGen<V, E>* e, bool directed = true);

    /**
     * 从图中移除给定顶点。
     * 如果在图中找不到该顶点，则调用不产生任何效果。
     * @bigoh O(E + log V)
     */
    void removeVertex(const std::string& name);

    /**
     * 从图中移除给定顶点。
     * 如果该顶点为 null 或在图中找不到，则调用不产生任何效果。
     * @bigoh O(E + log V)
     */
    void removeVertex(VertexGen<V, E>* v);

    /**
     * 将每个顶点和边中存储的数据恢复为原始值
     * 通过对每个顶点和边调用 resetData。
     * @private
     * @bigoh O(V + E)
     */
    void resetData();

    /**
     * 设置 resetData 方法是否启用（默认 true）。
     * @private
     * @bigoh O(1)
     */
    void setResetEnabled(bool enabled);

    /* @inherit */
    virtual void scanArcData(TokenScanner& scanner, EdgeGen<V, E>* edge, EdgeGen<V, E>* inverse);

    /* @inherit */
    virtual void writeArcData(std::ostream& out, EdgeGen<V, E>* edge) const;

    /**
     * 返回表示与此图等价的邻接表的 Map。
     * 每个顶点的名称是映射中的键，其相邻顶点的名称
     * 作为与该键关联的值存储在 Set 中。
     * 需要注意，此成员不会保留边的权重
     * 位于相邻顶点之间，因此不适合用于加权图。
     * @bigoh O(V + E)
     */
    Map<std::string, Set<std::string>> toMap() const;

    /**
     * 返回图中的顶点数量。
     * 等价于 size。
     * @bigoh O(1)
     */
    int vertexCount() const;

    /**
     * 重载 <code>[]</code>，根据顶点名称返回顶点指针。
     * @bigoh O(log V)
     */
    VertexGen<V, E>* operator [](const std::string& name);

    /**
     * 重载 <code>[]</code>，根据顶点名称返回顶点指针。
     * @bigoh O(log V)
     */
    const VertexGen<V, E>* operator [](const std::string& name) const;

private:
    bool m_resetEnabled;
};

/**
 * BasicGraphGen 的哈希函数。
 */
template <typename V, typename E>
int hashCode(const BasicGraphGen<V, E>& graph);

/*
 * 将 Vertex 定义为数据绑定为 void* 的 VertexGen。
 * 为向后兼容而保留。
 */
typedef VertexGen<void*, void*> Vertex;
#define VertexV VertexGen

/*
 * 如有需要，可以将 Vertex 称为 Node。
 */
#define Node Vertex

/*
 * 将 Edge 定义为数据绑定为 void* 的 EdgeGen。
 * 为向后兼容而保留。
 */
typedef EdgeGen<void*, void*> Edge;
#define EdgeV EdgeGen

/*
 * 如有需要，可以将 Edge 称为 Arc。
 */
#define Arc Edge

/*
 * 将 BasicGraph 定义为数据绑定为 void* 的 BasicGraphGen。
 * 为向后兼容而保留。
 */
typedef BasicGraphGen<void*, void*> BasicGraph;
#define BasicGraphV BasicGraphGen

/**
 * BasicGraph 的哈希函数。
 */
int hashCode(const BasicGraph& graph);


/*
 * Vertex 成员的实现
 */
template <typename V, typename E>
VertexGen<V, E>::VertexGen(const std::string& theName)
        : name(theName),
          edges(arcs),
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
          weight(cost),
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
          data(V()),
          extraData(data) {
    resetData();
}

template <typename V, typename E>
VertexGen<V, E>::VertexGen(const VertexGen& other)
    : name(other.name),
      arcs(other.arcs),
      edges(arcs),
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
      cost(other.cost),
      weight(cost),
      visited(other.visited),
      previous(other.previous),
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
      data(other.data),
      extraData(data),
      _color(other._color) {
    // 空
}

template <typename V, typename E>
VertexGen<V, E>::~VertexGen() {
    // 空
}

template <typename V, typename E>
int VertexGen<V, E>::getColor() const {
    return _color;
}

template <typename V, typename E>
void VertexGen<V, E>::resetData() {
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    cost = 0.0;
    previous = nullptr;
    visited = false;
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    _color = /* 未着色 */ 0;
}

template <typename V, typename E>
void VertexGen<V, E>::setColor(int c) {
    _color = c;
    notifyObservers();
}

template <typename V, typename E>
std::string VertexGen<V, E>::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

template <typename V, typename E>
VertexGen<V, E>& VertexGen<V, E>::operator =(const VertexGen& other) {
    if (this != &other) {
        name = other.name;
        arcs = other.arcs;
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
        cost = other.cost;
        visited = other.visited;
        previous = other.previous;
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
        data = other.data;
        _color = other._color;
    }
    return *this;
}

template <typename V, typename E>
VertexGen<V, E>& VertexGen<V, E>::operator =(VertexGen&& other) {
    if (this != &other) {
        name = other.name;
        arcs = other.arcs;
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
        cost = other.cost;
        visited = other.visited;
        previous = other.previous;
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
        data = other.data;
        _color = other._color;
    }
    return *this;
}

template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const VertexGen<V, E>& v) {
    out << "Vertex{name=" << v.name;

#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    if (!floatingPointEqual(v.cost, 0.0)) {
        out << ", cost=" << v.cost;
    }
    out << ", visited=" << (v.visited ? "true" : "false");
    out << ", previous=" << (v.previous == nullptr ? std::string("nullptr") : v.previous->name);
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS

    // 打印邻居
    out << ", neighbors={";
    int i = 0;
    for (EdgeGen<V, E>* edge : v.edges) {
        if (i > 0) {
            out << ", ";
        }
        i++;
        if (edge->finish) {
            out << edge->finish->name;
        } else {
            out << "nullptr";
        }
    }
    out << "}";   // 邻居结束

    out << "}";   // Vertex 结束
    return out;
}


/*
 * Edge 成员实现
 */
template <typename V, typename E>
EdgeGen<V, E>::EdgeGen(VertexGen<V, E>* theStart, VertexGen<V, E>* theFinish, double theCost)
        : start(theStart),
          finish(theFinish),
          end(this->finish),
          cost(theCost),
          weight(this->cost),
          data(nullptr),
          extraData(data) {
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    this->extraData = nullptr;
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    this->resetData();
}

template <typename V, typename E>
EdgeGen<V, E>::~EdgeGen() {
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    if (this->extraData != nullptr) {
        this->extraData = nullptr;
        // delete this->extraData;
    }
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
}

template <typename V, typename E>
void EdgeGen<V, E>::resetData() {
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    this->visited = false;
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
}

template <typename V, typename E>
std::string EdgeGen<V, E>::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

template <typename V, typename E>
EdgeGen<V, E>& EdgeGen<V, E>::operator =(const EdgeGen& other) {
    if (this != &other) {
        start = other.start;
        finish = other.finish;
        cost = other.cost;
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
        visited = other.visited;
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    }
    return *this;
}

template <typename V, typename E>
EdgeGen<V, E>& EdgeGen<V, E>::operator =(EdgeGen&& other) {
    start = other.start;
    finish = other.finish;
    cost = other.cost;
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    visited = other.visited;
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    return *this;
}

/**
 * 将给定边结构写入给定输出流。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const EdgeGen<V, E>& edge) {
    out << "Edge{start=";
    if (!edge.start) {
        out << "nullptr";
    } else {
        out << edge.start->name;
    }
    out << ", finish=";
    if (!edge.finish) {
        out << "nullptr";
    } else {
        out << edge.finish->name;
    }
    if (!floatingPointEqual(edge.cost, 0.0)) {
        out << ", cost=" << edge.cost;
    }
#ifdef SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    if (edge.visited) {
        out << ", visited=" << (edge.visited ? "true" : "false");
    }
#endif // SPL_BASICGRAPH_VERTEX_EDGE_RICH_MEMBERS
    out << "}";
    return out;
}


/*
 * BasicGraph 成员实现
 */
template <typename V, typename E>
BasicGraphGen<V, E>::BasicGraphGen() : Graph<VertexGen<V, E>, EdgeGen<V, E>>() {
    m_resetEnabled = true;
}

template <typename V, typename E>
BasicGraphGen<V, E>::BasicGraphGen(std::initializer_list<std::string> vertexList)
        : Graph<VertexGen<V, E>, EdgeGen<V, E>>() {
    m_resetEnabled = true;
    for (const std::string& vertexName : vertexList) {
        this->addVertex(vertexName);
    }
}

template <typename V, typename E>
void BasicGraphGen<V, E>::clearEdges() {
    this->clearArcs();
}

template <typename V, typename E>
void BasicGraphGen<V, E>::clearEdges(VertexGen<V, E>* v) {
    this->clearArcs(v);
}

template <typename V, typename E>
void BasicGraphGen<V, E>::clearEdges(const std::string& v) {
    this->clearArcs(v);
}

template <typename V, typename E>
bool BasicGraphGen<V, E>::containsEdge(VertexGen<V, E>* v1, VertexGen<V, E>* v2) const {
    return this->containsArc(v1, v2);
}

template <typename V, typename E>
bool BasicGraphGen<V, E>::containsEdge(const std::string& v1, const std::string& v2) const {
    return this->containsArc(v1, v2);
}

template <typename V, typename E>
bool BasicGraphGen<V, E>::containsEdge(EdgeGen<V, E>* edge) const {
    return this->containsArc(edge);
}

template <typename V, typename E>
bool BasicGraphGen<V, E>::containsVertex(const std::string& name) const {
    return this->containsNode(name);
}

template <typename V, typename E>
bool BasicGraphGen<V, E>::containsVertex(VertexGen<V, E>* v) const {
    return this->containsNode(v);
}

template <typename V, typename E>
int BasicGraphGen<V, E>::edgeCount() const {
    return this->arcCount();
}

template <typename V, typename E>
EdgeGen<V, E>* BasicGraphGen<V, E>::getEdge(VertexGen<V, E>* v1, VertexGen<V, E>* v2) const {
    return this->getArc(v1, v2);
}

template <typename V, typename E>
EdgeGen<V, E>* BasicGraphGen<V, E>::getEdge(const std::string& v1, const std::string& v2) const {
    return this->getArc(v1, v2);
}

template <typename V, typename E>
EdgeGen<V, E>* BasicGraphGen<V, E>::getInverseArc(EdgeGen<V, E>* edge) const {
    return this->getArc(edge->finish, edge->start);
}

template <typename V, typename E>
EdgeGen<V, E>* BasicGraphGen<V, E>::getInverseEdge(EdgeGen<V, E>* edge) const {
    return this->getInverseArc(edge);
}

template <typename V, typename E>
void BasicGraphGen<V, E>::resetData() {
    if (m_resetEnabled) {
        for (VertexGen<V, E>* v : this->getVertexSet()) {
            v->resetData();
        }
        for (EdgeGen<V, E>* e : this->getEdgeSet()) {
            e->resetData();
        }
    }
}

template <typename V, typename E>
void BasicGraphGen<V, E>::setResetEnabled(bool enabled) {
    m_resetEnabled = enabled;
}

template <typename V, typename E>
EdgeGen<V, E>* BasicGraphGen<V, E>::addEdge(const std::string& v1, const std::string& v2, double cost, bool directed) {
    if (!this->containsVertex(v1)) {
        this->addVertex(v1);
    }
    if (!this->containsVertex(v2)) {
        this->addVertex(v2);
    }
    return this->addEdge(this->getVertex(v1), this->getVertex(v2), cost, directed);
}

template <typename V, typename E>
EdgeGen<V, E>* BasicGraphGen<V, E>::addEdge(VertexGen<V, E>* v1, VertexGen<V, E>* v2, double cost, bool directed) {
    EdgeGen<V, E>* e = new EdgeGen<V, E>(v1, v2, cost);
    return this->addEdge(e, directed);
}

template <typename V, typename E>
EdgeGen<V, E>* BasicGraphGen<V, E>::addEdge(EdgeGen<V, E>* e, bool directed) {
    EdgeGen<V, E>* result = this->addArc(e);
    if (!directed) {
        EdgeGen<V, E>* result2 = this->addArc(e->finish, e->start);
        result2->cost = e->cost;
    }
    return result;
}

template <typename V, typename E>
VertexGen<V, E>* BasicGraphGen<V, E>::addVertex(const std::string& name) {
    return this->addNode(name);
}

template <typename V, typename E>
VertexGen<V, E>* BasicGraphGen<V, E>::addVertex(VertexGen<V, E>* v) {
    return this->addNode(v);
}

template <typename V, typename E>
const Set<EdgeGen<V, E>*>& BasicGraphGen<V, E>::getEdgeSet() const {
    return this->getArcSet();
}

template <typename V, typename E>
const Set<EdgeGen<V, E>*>& BasicGraphGen<V, E>::getEdgeSet(VertexGen<V, E>* v) const {
    return this->getArcSet(v);
}

template <typename V, typename E>
const Set<EdgeGen<V, E>*>& BasicGraphGen<V, E>::getEdgeSet(const std::string& v) const {
    return this->getArcSet(v);
}

template <typename V, typename E>
const Set<EdgeGen<V, E>*> BasicGraphGen<V, E>::getInverseEdgeSet(VertexGen<V, E>* v) const {
    return this->getInverseArcSet(v);
}

template <typename V, typename E>
const Set<EdgeGen<V, E>*> BasicGraphGen<V, E>::getInverseEdgeSet(const std::string& v) const {
    return this->getInverseArcSet(v);
}


template <typename V, typename E>
VertexGen<V, E>* BasicGraphGen<V, E>::getVertex(const std::string& name) const {
    return this->getNode(name);
}

template <typename V, typename E>
Set<std::string> BasicGraphGen<V, E>::getVertexNames() const {
    return this->getNodeNames();
}


template <typename V, typename E>
const Set<VertexGen<V, E>*>& BasicGraphGen<V, E>::getVertexSet() const {
    return this->getNodeSet();
}

template <typename V, typename E>
void BasicGraphGen<V, E>::removeEdge(const std::string& v1, const std::string& v2, bool directed) {
    this->removeEdge(this->getVertex(v1), this->getVertex(v2), directed);
}

template <typename V, typename E>
void BasicGraphGen<V, E>::removeEdge(VertexGen<V, E>* v1, VertexGen<V, E>* v2, bool directed) {
    this->removeArc(v1, v2);
    if (!directed) {
        this->removeArc(v2, v1);
    }
}

template <typename V, typename E>
void BasicGraphGen<V, E>::removeEdge(EdgeGen<V, E>* e, bool directed) {
    this->removeArc(e);
    if (!directed) {
        this->removeArc(e->finish, e->start);
    }
}

template <typename V, typename E>
void BasicGraphGen<V, E>::removeVertex(const std::string& name) {
    this->removeNode(name);
}

template <typename V, typename E>
void BasicGraphGen<V, E>::removeVertex(VertexGen<V, E>* v) {
    this->removeNode(v);
}

template <typename V, typename E>
Map<std::string, Set<std::string>> BasicGraphGen<V, E>::toMap() const {
    Map<std::string, Set<std::string>> result;
    for (Vertex* v : this->getVertexSet()) {
        Set<std::string> neighborSet;
        for (Vertex* neighbor : this->getNeighbors(v)) {
            neighborSet += neighbor->name;
        }
        result[v->name] = neighborSet;
    }
    return result;
}

template <typename V, typename E>
int BasicGraphGen<V, E>::vertexCount() const {
    return this->nodeCount();
}

template <typename V, typename E>
VertexGen<V, E>* BasicGraphGen<V, E>::operator [](const std::string& name) {
    return this->getVertex(name);
}

template <typename V, typename E>
const VertexGen<V, E>* BasicGraphGen<V, E>::operator [](const std::string& name) const {
    return this->getVertex(name);
}

template <typename V, typename E>
void BasicGraphGen<V, E>::scanArcData(TokenScanner& scanner, EdgeGen<V, E>* edge, EdgeGen<V, E>* inverse) {
    std::string colon = scanner.nextToken();   // “:”，跳过
    if (colon == ":") {
        std::string costStr = scanner.nextToken();
        edge->cost = stringToReal(costStr);
        if (inverse) {
            inverse->cost = edge->cost;
        }
    } else {
        // 此边无成本（成本 0）；退回冒号令牌，因为
        // 它实际上可能不是冒号
        scanner.saveToken(colon);
    }
}

template <typename V, typename E>
void BasicGraphGen<V, E>::writeArcData(std::ostream& out, EdgeGen<V, E>* edge) const {
    if (!floatingPointEqual(edge->cost, 0.0)) {
        out << " : ";
        out << edge->cost;
    }
}

/**
 * 用于图的模板哈希函数。
 */
template <typename V, typename E>
int hashCode(const BasicGraphGen<V, E>& graph) {
    int code = hashSeed();
    for (VertexGen<V, E>* v : graph) {
        code = hashMultiplier() * code + hashCode(v->name);
    }
    for (EdgeGen<V, E>* e : graph.getEdgeSet()) {
        code = hashMultiplier() * code + hashCode(e->start->name);
        code = hashMultiplier() * code + hashCode(e->finish->name);
    }
    return (code & hashMask());
}

/**
 * 用于打印边指针集合的重载运算符。
 * 通常不建议重载指针的输出运算符，
 * 因为该指针可能为空或包含无效值。
 * 但在此情况下，我们认为让学生的
 * 使顶点和边集合的输出易于阅读。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const HashSet<EdgeGen<V, E>*>& sete) {
    out << "{";
    if (!sete.isEmpty()) {
        bool first = true;
        for (EdgeGen<V, E>* e : sete) {
            if (!first) {
                out << ", ";
            }
            first = false;
            if (e) {
                if (e->start) {
                    out << e->start->name;
                } else {
                    out << "null";
                }
                out << " -> ";
                if (e->finish) {
                    out << e->finish->name;
                } else {
                    out << "null";
                }
            } else {
                out << "null";
            }
        }
    }
    out << "}";
    return out;
}

/**
 * 用于打印顶点指针集合的重载运算符。
 * 通常不建议重载指针的输出运算符，
 * 因为该指针可能为空或包含无效值。
 * 但在此情况下，我们认为让学生的
 * 使顶点和边集合的输出易于阅读。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const HashSet<VertexGen<V, E>*>& setv) {
    out << "{";
    if (!setv.isEmpty()) {
        bool first = true;
        for (VertexGen<V, E>* v : setv) {
            if (!first) {
                out << ", ";
            }
            first = false;
            if (v) {
                out << v->name;
            } else {
                out << "null";
            }
        }
    }
    out << "}";
    return out;
}

/**
 * 用于打印边指针列表的重载运算符。
 * 通常不建议重载指针的输出运算符，
 * 因为该指针可能为空或包含无效值。
 * 但在此情况下，我们认为让学生的
 * 使顶点和边集合的输出易于阅读。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const LinkedList<EdgeGen<V, E>*>& liste) {
    out << "{";
    if (!liste.isEmpty()) {
        bool first = true;
        for (EdgeGen<V, E>* e : liste) {
            if (!first) {
                out << ", ";
            }
            first = false;
            if (e) {
                if (e->start) {
                    out << e->start->name;
                } else {
                    out << "null";
                }
                out << " -> ";
                if (e->finish) {
                    out << e->finish->name;
                } else {
                    out << "null";
                }
            } else {
                out << "null";
            }
        }
    }
    out << "}";
    return out;
}

/**
 * 用于打印顶点指针列表的重载运算符。
 * 通常不建议重载指针的输出运算符，
 * 因为该指针可能为空或包含无效值。
 * 但在此情况下，我们认为让学生的
 * 使顶点和边集合的输出易于阅读。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const LinkedList<VertexGen<V, E>*>& lst) {
    out << "{";
    if (!lst.isEmpty()) {
        bool first = true;
        for (VertexGen<V, E>* v : lst) {
            if (!first) {
                out << ", ";
            }
            first = false;
            if (v) {
                out << v->name;
            } else {
                out << "null";
            }
        }
    }
    out << "}";
    return out;
}

/**
 * 用于打印边指针集合的重载运算符。
 * 通常不建议重载指针的输出运算符，
 * 因为该指针可能为空或包含无效值。
 * 但在此情况下，我们认为让学生的
 * 使顶点和边集合的输出易于阅读。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const Set<EdgeGen<V, E>*>& sete) {
    out << "{";
    if (!sete.isEmpty()) {
        bool first = true;
        for (EdgeGen<V, E>* e : sete) {
            if (!first) {
                out << ", ";
            }
            first = false;
            if (e) {
                if (e->start) {
                    out << e->start->name;
                } else {
                    out << "null";
                }
                out << " -> ";
                if (e->finish) {
                    out << e->finish->name;
                } else {
                    out << "null";
                }
            } else {
                out << "null";
            }
        }
    }
    out << "}";
    return out;
}

/**
 * 用于打印顶点指针集合的重载运算符。
 * 通常不建议重载指针的输出运算符，
 * 因为该指针可能为空或包含无效值。
 * 但在此情况下，我们认为让学生的
 * 使顶点和边集合的输出易于阅读。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const Set<VertexGen<V, E>*>& setv) {
    out << "{";
    if (!setv.isEmpty()) {
        bool first = true;
        for (VertexGen<V, E>* v : setv) {
            if (!first) {
                out << ", ";
            }
            first = false;
            if (v) {
                out << v->name;
            } else {
                out << "null";
            }
        }
    }
    out << "}";
    return out;
}

/**
 * 用于打印边指针向量的重载运算符。
 * 通常不建议重载指针的输出运算符，
 * 因为该指针可能为空或包含无效值。
 * 但在此情况下，我们认为让学生的
 * 使顶点和边集合的输出易于阅读。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const Vector<EdgeGen<V, E>*>& vece) {
    out << "{";
    if (!vece.isEmpty()) {
        bool first = true;
        for (EdgeGen<V, E>* e : vece) {
            if (!first) {
                out << ", ";
            }
            first = false;
            if (e) {
                if (e->start) {
                    out << e->start->name;
                } else {
                    out << "null";
                }
                out << " -> ";
                if (e->finish) {
                    out << e->finish->name;
                } else {
                    out << "null";
                }
            } else {
                out << "null";
            }
        }
    }
    out << "}";
    return out;
}

/**
 * 用于打印顶点指针向量的重载运算符。
 * 通常不建议重载指针的输出运算符，
 * 因为该指针可能为空或包含无效值。
 * 但在此情况下，我们认为让学生的
 * 使顶点和边集合的输出易于阅读。
 */
template <typename V, typename E>
std::ostream& operator <<(std::ostream& out, const Vector<VertexGen<V, E>*>& vec) {
    out << "{";
    if (!vec.isEmpty()) {
        bool first = true;
        for (VertexGen<V, E>* v : vec) {
            if (!first) {
                out << ", ";
            }
            first = false;
            if (v) {
                out << v->name;
            } else {
                out << "null";
            }
        }
    }
    out << "}";
    return out;
}

#endif // _basicgraph_h
