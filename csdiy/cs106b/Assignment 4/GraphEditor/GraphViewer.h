/******************************************************************************
 * 通用图渲染器。无需做任何复杂工作，即可渲染
 * 抽象空间中的图。
 */

#pragma once

#include "gobjects.h"
#include "gwindow.h"
#include "../GUI/Font.h"
#include "Utilities/JSON.h"
#include <string>
#include <set>
#include <unordered_map>
#include <memory>
#include <functional>
#include <istream>

namespace GraphEditor {
    class ViewerBase;
    class Node;
    class Edge;

    class NodeArgs;
    class EdgeArgs;

    /* 查看器的宽高比。公开此值是为了让项目能够正确定位
     * 在逻辑空间中适当地处理。
     */
    const double kDefaultAspectRatio = 5.0 / 3.0;

    /* 图形系统中节点的大小。公开此值，以便控制器可以
     * 确定某项距离节点中心有多近（例如用于确定
     * 我们是在拖动节点还是引入新节点。
     */
    const double kNodeRadius = 0.035;

    /* 边的宽度。公开此值是为了让控制器能够绘制表示
     * 新边。
     */
    const double kEdgeWidth = 3.0 / 1000; // 1000px 窗口上的 3px；

    /* 悬停边的宽度。公开此值是为了让控制器能够判断
     * 某条边是否处于悬停状态。
     */
    const double kEdgeTolerance = 16.0 / 1000;

    const MiniGUI::Font kEdgeFont(MiniGUI::FontFamily::UNICODE_MONOSPACE, MiniGUI::FontStyle::NORMAL, 18, "black");
    const MiniGUI::Font kNodeFont(MiniGUI::FontFamily::UNICODE_SERIF,     MiniGUI::FontStyle::ITALIC, 18, "black");

    /* 默认图形参数。 */
    const double kNodeBorderWidth = 3.0 / 1000; // 1000px 窗口上的 3px
    const std::string kNodeColor = "white";
    const std::string kNodeBorderColor = "black";
    const std::string kEdgeColor = "black";

    /* 节点样式。 */
    struct NodeStyle {
        double radius           = kNodeRadius;
        double lineWidth        = kNodeBorderWidth;
        std::string fillColor   = kNodeColor;
        std::string borderColor = kNodeBorderColor;
        std::string textColor   = kNodeBorderColor;
    };

    /* 转移样式。 */
    struct EdgeStyle {
        double lineWidth       = kEdgeWidth;
        std::string lineColor  = kEdgeColor;
        std::string labelColor = kEdgeColor;
    };

    /* 图实体的基类型。 */
    class Entity {
    public:
        virtual ~Entity() = default;
    };

    /* 图中的一个节点。 */
    class Node: public Entity {
    public:
        virtual ~Node() = default;

        /* 每个节点会被分配从 0 开始的连续编号。这些编号
         * 递增计数，且如果节点被删除则回收。
         */
        std::size_t index();

        /* 设置/读取标签。默认标签为空。 */
        const std::string& label();
        void label(const std::string& label);

        /* 州的位置以世界坐标给出，其中 (0, 0) 是左上角
         * 内容区域的角，(1, 1 / kAspectRatio) 是右下角。
         */
        const GPoint& position();
        void  position(const GPoint& pt);

        /* 绘制给定节点。 */
        virtual void draw(ViewerBase* base,        // 用于单位转换
                          GCanvas*    canvas,      // 绘制位置
                          const NodeStyle& style); // 样式

        /* 将辅助数据序列化为 JSON。默认情况下仅返回 null，
         * 但可覆盖此方法以自定义保存的数据。
         */
        virtual JSON toJSON();

    protected:
        /* 此项存在是为了让 Node 能直接使用。它完全忽略
         * 辅助数据。你不需要使用此构造函数。
         */
        Node(ViewerBase* viewer,
             const NodeArgs& args,
             JSON /* 已忽略 */);

        Node(ViewerBase* viewer, const NodeArgs& args);

    private:
        ViewerBase* owner;

        /* 逻辑空间中的位置。 */
        GPoint mPos;

        std::size_t mIndex;

        std::string mLabel;

        friend class ViewerBase;
        template <typename N, typename T> friend class Viewer;
    };

    /* 图的边。在有向图（默认）中，"from" 和 "to" 的含义
     * 定义明确。在无向情况下，“from”和“to”的含义应
     * 应改为理解成“一个端点”和“另一个端点”。
     */
    class Edge: public Entity {
    public:
        virtual ~Edge() = default;

        Node* from();
        Node* to();

        std::string label();
        void label(const std::string& label);

        /* 将辅助数据序列化为 JSON。默认情况下仅返回 null，
         * 但可覆盖此方法以自定义保存的数据。
         */
        virtual JSON toJSON();

    protected:
        /* 此项存在是为了让你能将 Edge 用作查看器的默认类型。
         * 你应该无需直接使用此构造函数。
         */
        Edge(ViewerBase* owner, const EdgeArgs& args,
             JSON /* 已忽略 */);

        Edge(ViewerBase* owner, const EdgeArgs& args);

    private:
        ViewerBase* mOwner;

        /* 起点/终点。 */
        Node* mFrom, *mTo;

        /* 标签（如果有）。 */
        std::string mLabel;

        /* 使用的转移样式。 */
        std::shared_ptr<struct EdgeRender> style;

        friend class ViewerBase;
        template <typename N, typename T> friend class Viewer;
    };

    /* 图的类型。默认为有向图。 */
    enum class Type {
        DIRECTED,
        UNDIRECTED
    };

    /* 包含绘制图形逻辑的基类型。你可能不会
     * 无需直接使用此类型；请改用参数化的
     * 查看器类型。
     */
    class ViewerBase {
    public:
        virtual ~ViewerBase() = default;

        /* 宽高比。 */
        double aspectRatio();
        void aspectRatio(double ratio);

        /* 将 Viewer 序列化为 JSON 对象。 */
        JSON toJSON();

        /* 设置 Viewer 绘制图时使用的边界框。
         * 默认为空矩形。
         */
        void setBounds(const GRectangle& bounds);

        /* 除以下部分外，所有位置都使用默认图形参数
         * 覆盖它的显式状态和过渡。
         */
        void draw(GCanvas* canvas,
                  const std::unordered_map<Node*, NodeStyle>& nodeStyles = {},
                  const std::unordered_map<Edge*, EdgeStyle>& edgeStyles = {});

        /* 要求我们填充的矩形。 */
        GRectangle bounds() const;

        /* 计算得到的、包含所有内容的矩形。 */
        GRectangle computedBounds() const;

        /* 设置图类型。
         *
         * 如果从无向图切换为有向图，
         * 现有边将被任意且随意地
         * 分配一个方向。
         *
         * 如果从有向图切换为无向图，
         * 所有自环都将被移除，所有相互指向的边对
         * 每个方向会任意且武断地有一条边
         * 分配一个方向。
         *
         * 因此，建议你先设置类型，然后再
         * 添加或移除任何边。
         */
        Type type() const;
        void type(Type type);

        /* 坐标变化。 */
        double     graphicsToWorld(double width);
        GPoint     graphicsToWorld(GPoint pt);
        GRectangle graphicsToWorld(GRectangle r);
        double     worldToGraphics(double width);
        GPoint     worldToGraphics(GPoint pt);
        GRectangle worldToGraphics(GRectangle r);

        /* 在世界中绘制箭头。公开此函数是因为某些客户端需要
         * 执行此操作。所有坐标均为世界坐标，而非图形坐标。
         */
        void drawArrow(GCanvas* canvas, const GPoint& from, const GPoint& to,
                       double thickness, const std::string& color);

        std::size_t numNodes();
    protected:
        virtual JSON auxData();

    private:

        /* 几何。 */
        double baseX = 0, baseY = 0;
        double width = 0, height = 0;
        double mAspectRatio = kDefaultAspectRatio;

        /* 指定给我们的绘制位置。 */
        GRectangle rawBounds;

        /* 所有节点/边的列表。 */
        std::set<std::shared_ptr<Node>> nodes;

        /* 转换，编码为 节点 -> 节点 -> 边信息。
         *
         * 不变量：如果图是无向的，边始终从索引较低的节点流向
         * 节点指向索引更高的节点。这样能在保存和加载之间保持一致。
         */
        std::unordered_map<Node*, std::unordered_map<Node*, std::shared_ptr<Edge>>> edges;

        /* 可供州使用的数字；如果为空，则使用 states 的大小
         * 作为下一个空闲槽位。
         */
        std::set<int> freeNodeIDs;

        /* 图类型。 */
        Type mType = Type::DIRECTED;

        JSON nodesToJSON();
        JSON edgesToJSON();
        JSON typeToJSON();

        JSON toJSON(Node* node);
        JSON toJSON(Edge* edge);

        Edge* edgeBetween(Node* from, Node* to);
        Node* nodeLabeled(const std::string& label);

        /* 图形处理例程。 */
        void drawTransition(GCanvas* canvas, std::shared_ptr<Edge> transition);

        void drawEdgeLabel(GCanvas* canvas, const GPoint& p0, const GPoint& p1,
                                 const std::string& label,
                                 const std::string& color,
                                 bool hugLine);
        void drawArrowhead(GCanvas* canvas, const GPoint& from, const GPoint& to,
                           double thickness, const std::string& color);

        /* 重新计算每个转移的渲染器。 */
        void calculateEdgeEndpoints();

        /* 供子类型使用。 */
        bool hasEdge(Node* from, Node* to);
        void forEachNode(std::function<void(Node*)>);
        void forEachEdge(std::function<void(Edge*)>);
        Node* nodeAt(const GPoint& pt);
        Edge* edgeAt(const GPoint& pt);
        void removeEdge(Edge* edge);

        friend struct LineEdge;
        friend struct LoopEdge;
        friend class  Node;
        friend class  Edge;

        template <typename NodeType, typename EdgeType>
        friend class Viewer;

        friend class EditorBase;
        template <typename Viewer> friend class Editor;
    };

    /* 底层图的查看器/编辑器。它以以下类型为参数
     * 节点和边，以便你可按需替换为自己的类型。
     *
     * 为了正常工作，节点和边类型必须是 Node 的子类型
     * 和 Edge。
     */
    template <typename N = Node, typename E = Edge>
    class Viewer: public ViewerBase {
    public:
        using NodeType = N;
        using EdgeType = E;

        /* 构造新的空查看器。 */
        Viewer() = default;

        /* 根据给定 JSON 数据反序列化查看器。JSON 数据
         * 假定由之前的 Viewer 写入。
         *
         * 此 JSON 对象可能包含名为 "aux" 的字段。如果存在，该数据
         * 纯粹供子类使用，可按最合适的方式使用
         * 适合 Viewer。
         */
        Viewer(JSON data);

        NodeType* newNode(const GPoint& location);
        void removeNode(NodeType* state);
        NodeType* nodeLabeled(const std::string& name);

        /* TODO：如果转换已存在，其语义是什么？ */
        EdgeType* newEdge(NodeType* from, NodeType* to, const std::string& label = "");
        void removeEdge(EdgeType* edge);

        /* 此位置有什么？ */
        NodeType* nodeAt(const GPoint& pt);
        EdgeType* edgeAt(const GPoint& pt);

        void forEachNode(std::function<void(NodeType*)>);
        void forEachEdge(std::function<void(EdgeType*)>);

        EdgeType* edgeBetween(NodeType* from, NodeType* to);

    private:
        /* 完整构造函数。 */
        std::shared_ptr<NodeType> newNode(const GPoint& pt, size_t index, const std::string& label, JSON aux);
        std::shared_ptr<EdgeType> newEdge(NodeType* from, NodeType* to, const std::string& label,   JSON aux);
    };



    /***** 此处以下为实现部分 *****/

    /* 节点和边的构造函数参数。 */
    class NodeArgs {
        GPoint pt;
        std::size_t index;
        std::string label;

        NodeArgs(const GPoint& pt, std::size_t index, const std::string& label) : pt(pt), index(index), label(label) {}

        friend class Node;
        template <typename, typename> friend class Viewer;
    };

    class EdgeArgs {
        Node* from;
        Node* to;
        std::string label;

        EdgeArgs(Node* from, Node* to, const std::string& label) : from(from), to(to), label(label) {}


        friend class Edge;
        template <typename, typename> friend class Viewer;
    };

    template <typename NodeType, typename EdgeType>
    NodeType* Viewer<NodeType, EdgeType>::newNode(const GPoint& pt) {
        /* 获取此状态的 ID。 */
        size_t id = numNodes();
        if (!freeNodeIDs.empty()) {
            id = *freeNodeIDs.begin();
            freeNodeIDs.erase(freeNodeIDs.begin());
        }

        auto result = newNode(pt, id, "", nullptr);
        return result.get();
    }

    template <typename NodeType, typename EdgeType>
    std::shared_ptr<NodeType> Viewer<NodeType, EdgeType>::newNode(const GPoint& pt, size_t index, const std::string& label, JSON j) {
        auto result = std::shared_ptr<NodeType>(new NodeType(this, NodeArgs{pt, index, label}, j));
        nodes.insert(result);

        /* 重新定位到该点；这会强制该点位于边界内。 */
        result->position(pt);
        return result;
    }

    template <typename NodeType, typename EdgeType>
    EdgeType* Viewer<NodeType, EdgeType>::newEdge(NodeType* from, NodeType* to, const std::string& label) {
        return newEdge(from, to, label, nullptr).get();
    }

    template <typename NodeType, typename EdgeType>
    std::shared_ptr<EdgeType> Viewer<NodeType, EdgeType>::newEdge(NodeType* from, NodeType* to, const std::string& label, JSON aux) {
        /* 如果图是无向的且两个端点相同，则不执行任何操作。 */
        if (type() == Type::UNDIRECTED && from == to) return nullptr;

        /* 如有必要，规范化顺序。 */
        if (type() == Type::UNDIRECTED && from->index() >= to->index()) {
            std::swap(from, to);
        }

        auto edge = std::shared_ptr<EdgeType>(new EdgeType(this, EdgeArgs{from, to, label}, aux));
        edges[from][to] = edge;
        calculateEdgeEndpoints();
        return edge;
    }

    template <typename NodeType, typename EdgeType>
    NodeType* Viewer<NodeType, EdgeType>::nodeAt(const GPoint& pt) {
        return static_cast<NodeType*>(ViewerBase::nodeAt(pt));
    }

    template <typename NodeType, typename EdgeType>
    EdgeType* Viewer<NodeType, EdgeType>::edgeAt(const GPoint& pt) {
        return static_cast<EdgeType*>(ViewerBase::edgeAt(pt));
    }

    template <typename NodeType, typename EdgeType>
    void Viewer<NodeType, EdgeType>::removeNode(NodeType* node) {
        auto itr = find_if(nodes.begin(), nodes.end(), [&](std::shared_ptr<Node> n) {
             return n.get() == node;
        });
        if (itr == nodes.end()) return;

        /* 删除从该状态出发的转移。 */
        edges.erase(node);

        /* 删除指向该状态的转移。 */
        for (auto& e1: edges) {
            auto itr = e1.second.begin();
            while (itr != e1.second.end()) {
                if (itr->first == node) {
                    itr = e1.second.erase(itr);
                } else {
                    ++itr;
                }
            }
        }

        freeNodeIDs.insert(node->index());

        /* 只有在最后才应从节点集合中删除该节点。
         * 这样做可能会断开指向节点的最后一个指针，此时
         * 节点失效。
         */
        nodes.erase(itr);

        /* 现在，在不包含此节点的情况下重新计算边。 */
        calculateEdgeEndpoints();
    }

    template <typename NodeType, typename EdgeType>
    void Viewer<NodeType, EdgeType>::removeEdge(EdgeType* edge) {
        ViewerBase::removeEdge(edge);
    }

    template <typename NodeType, typename EdgeType>
    EdgeType* Viewer<NodeType, EdgeType>::edgeBetween(NodeType* from, NodeType* to) {
        return static_cast<EdgeType*>(ViewerBase::edgeBetween(from, to));
    }

    template <typename NodeType, typename EdgeType>
    NodeType* Viewer<NodeType, EdgeType>::nodeLabeled(const std::string& label) {
        return static_cast<NodeType*>(ViewerBase::nodeLabeled(label));
    }

    /* 反序列化。 */
    template <typename NodeType, typename EdgeType>
    Viewer<NodeType, EdgeType>::Viewer(JSON j) {
        /* 解压节点。 */
        std::size_t maxIndex = 0;
        std::map<std::size_t, Node*> byIndex;
        for (JSON jNode: j["nodes"]) {
            std::size_t index = jNode["index"].asInteger();
            std::string label = jNode["label"].asString();
            GPoint pos        = { jNode["pos"][0].asDouble(), jNode["pos"][1].asDouble() };

            auto node = newNode(pos, index, label, jNode["aux"]);

            byIndex[node->index()] = node.get();

            maxIndex = std::max(maxIndex, index);
        }

        /* 再次遍历节点，填入缺失的节点 ID。 */
        for (size_t i = 0; i < maxIndex; i++) {
            freeNodeIDs.insert(i);
        }
        for (auto node: nodes) {
            freeNodeIDs.erase(node->index());
        }

        /* 解压边。 */
        for (JSON jEdge: j["edges"]) {
            std::size_t from  = jEdge["from"].asInteger();
            std::size_t to    = jEdge["to"].asInteger();
            std::string label = jEdge["label"].asString();
            auto edge         = newEdge(static_cast<NodeType*>(byIndex.at(from)),
                                        static_cast<NodeType*>(byIndex.at(to)),
                                        label,
                                        jEdge["aux"]);
        }

        /* 是否有类型信息？ */
        if (j.contains("type")) {
            if (j["type"].asString() == "directed") {
                type(Type::DIRECTED);
            } else if (j["type"].asString() == "undirected") {
                type(Type::UNDIRECTED);
            } else {
                error("Unknown graph type: " + j["type"].asString());
            }
        }
    }

    template <typename NodeType, typename EdgeType>
    void Viewer<NodeType, EdgeType>::forEachNode(std::function<void(NodeType*)> callback) {
        return ViewerBase::forEachNode([&](Node* node) {
            return callback(static_cast<NodeType*>(node));
        });
    }

    template <typename NodeType, typename EdgeType>
    void Viewer<NodeType, EdgeType>::forEachEdge(std::function<void(EdgeType*)> callback) {
        return ViewerBase::forEachEdge([&](Edge* edge) {
            return callback(static_cast<EdgeType*>(edge));
        });
    }
}
