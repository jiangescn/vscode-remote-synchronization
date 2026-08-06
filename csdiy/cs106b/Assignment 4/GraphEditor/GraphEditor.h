#pragma once

#include "GraphViewer.h"

namespace GraphEditor {
    /* 监听器接口。 */
    class Listener {
    public:
        virtual ~Listener() = default;

        virtual void needsRepaint();
        virtual void isDirty();
        virtual void entitySelected(Entity* entity);
        virtual void entityHovered(Entity* entity);
        virtual void entityCreated(Entity* entity);
    };

    /* 所有编辑器的基类型。你不应直接使用此类型；它用于
     * 仅供内部使用。
     */
    class EditorBase {
    public:
        /* 处理这些鼠标事件，以支持拖动、添加新线条、
         * 等等。转发这些消息，让编辑器处理拖动，
         * 创建新项目等。
         */
        void mouseDoubleClicked(double x, double y);
        void mouseMoved(double x, double y);
        void mousePressed(double x, double y);
        void mouseDragged(double x, double y);
        void mouseReleased(double x, double y);

        /* 回调注册。 */
        void addListener(std::shared_ptr<Listener> listener);

        /* 绘制底层查看器。请使用此方法，而不是手动
         * 要求查看器绘制，以便我们能够正确高亮
         * 所有内容。
         *
         * 如有需要，可以在此指定节点和边的样式。
         * 如果这样做，你指定的节点和边样式将覆盖
         * 对选中/悬停节点和边应用的任何样式。
         */
        void draw(GCanvas* canvas,
                  const std::unordered_map<Node*, NodeStyle>& nodeStyles = {},
                  const std::unordered_map<Edge*, EdgeStyle>& edgeStyles = {});

        /* 设置当前活动的实体（如果有）。 */
        void setActive(GraphEditor::Entity* active);

    private:
        EditorBase(std::shared_ptr<ViewerBase>);
        std::shared_ptr<ViewerBase> mViewer;

        std::vector<std::shared_ptr<Listener>> mListeners;

        /* 活动/悬停项目。 */
        Node* activeNode = nullptr;
        Node* hoverNode  = nullptr;
        Edge* activeEdge = nullptr;
        Edge* hoverEdge  = nullptr;

        /* 用于拖动对象。 */
        GPoint lastState;

        /* 用于拖动边。 */
        GPoint dragEdge0, dragEdge1;
        Node* edgeStart = nullptr;

        /* 我们正在进行哪种拖动？ */
        enum class DragType {
            NONE,
            NODE,
            EDGE
        };
        DragType dragType = DragType::NONE;

        void drawGraph(GCanvas* canvas,
                       const std::unordered_map<Node*, NodeStyle>& nodeStyles,
                       const std::unordered_map<Edge*, EdgeStyle>& edgeStyles);
        void drawDraggedEdge(GCanvas* canvas);

        /* 以两种方式之一处理拖动。 */
        void dragState(GPoint pt);
        void dragTransition(GPoint pt);

        /* 添加新转移时处理鼠标释放事件。 */
        void finishCreatingEdge(GPoint pt);

        /* 更改悬停节点/边。 */
        void setHover(GraphEditor::Entity* hover);

        void setActiveNode(GraphEditor::Node* state);
        void setActiveEdge(GraphEditor::Edge* transition);
        void setHoverNode(GraphEditor::Node* state);
        void setHoverEdge(GraphEditor::Edge* transition);

        Node* selectedNode();
        Edge* selectedEdge();

        void dirty();
        void requestRepaint();

        /* 与基类隔离。我们保证类型可用。 */
        virtual Node* newNode(const GPoint& pt) = 0;
        virtual Edge* newEdge(Node* from, Node* to) = 0;
        virtual Edge* edgeBetween(Node* from, Node* to) = 0;

        template <typename Viewer> friend class Editor;
    };

    /* 专为交互式编辑而设计的 Viewer 接口
     * 底层图结构。它以
     * 底层查看器
     */
    template <typename Viewer = GraphEditor::Viewer<>> class Editor: public EditorBase {
    public:
        using NodeType = typename Viewer::NodeType;
        using EdgeType = typename Viewer::EdgeType;

        /* 构建连接到指定 Viewer 的编辑器。 */
        Editor(std::shared_ptr<Viewer> viewer);

        /* 选中了哪个节点或边（如果有）？ */
        NodeType* selectedNode();
        EdgeType* selectedEdge();

        /* 删除给定节点/边。 */
        void deleteNode(NodeType* node);
        void deleteEdge(EdgeType* edge);

        /* 获取底层编辑器。 */
        std::shared_ptr<Viewer> viewer();

    protected:
        virtual Node* newNode(const GPoint& pt) override;
        virtual Edge* newEdge(Node* from, Node* to) override;
        virtual Edge* edgeBetween(Node* from, Node* to) override;

    private:
        std::shared_ptr<Viewer> mViewer;
    };

    template <typename Viewer>
    Editor<Viewer>::Editor(std::shared_ptr<Viewer> viewer) : EditorBase(viewer), mViewer(viewer) {
        // 已在上方处理
    }

    template <typename Viewer>
    std::shared_ptr<Viewer> Editor<Viewer>::viewer() {
        return mViewer;
    }

    template <typename Viewer>
    void Editor<Viewer>::deleteNode(NodeType* node) {
        /* 删除状态。 */
        mViewer->removeNode(node);

        /* 如果这是活动节点，则取消选中它。 */
        if (node == activeNode) setActive(nullptr);
        if (node == hoverNode)  setHover(nullptr);

        /* 取消选择活动过渡；它可能不再有效！ */
        if (activeEdge) setActive(nullptr);
        if (hoverEdge)  setHover(nullptr);

        dirty();
    }

    template <typename Viewer>
    void Editor<Viewer>::deleteEdge(EdgeType* edge) {
        /* 从转移列表中删除。 */
        mViewer->removeEdge(edge);

        if (activeEdge == edge) setActive(nullptr);
        if (hoverEdge  == edge) setHover(nullptr);
        dirty();
    }

    template <typename Viewer>
    Node* Editor<Viewer>::newNode(const GPoint& pt) {
        return mViewer->newNode(pt);
    }

    template <typename Viewer>
    Edge* Editor<Viewer>::newEdge(Node* src, Node* dst) {
        return mViewer->newEdge(static_cast<NodeType*>(src), static_cast<NodeType*>(dst));
    }

    template <typename Viewer>
    Edge* Editor<Viewer>::edgeBetween(Node* src, Node* dst) {
        return mViewer->edgeBetween(static_cast<NodeType*>(src), static_cast<NodeType*>(dst));
    }

    template <typename Viewer>
    typename Editor<Viewer>::NodeType* Editor<Viewer>::selectedNode() {
        return static_cast<NodeType*>(EditorBase::selectedNode());
    }

    template <typename Viewer>
    typename Editor<Viewer>::EdgeType* Editor<Viewer>::selectedEdge() {
        return static_cast<EdgeType*>(EditorBase::selectedEdge());
    }
}
