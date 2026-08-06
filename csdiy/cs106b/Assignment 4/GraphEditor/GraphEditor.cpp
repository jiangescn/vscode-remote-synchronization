#include "GraphEditor.h"
#include "GVector.h"

namespace GraphEditor {
    namespace {
        /* 活动状态以高亮颜色显示。 */
        const std::string kActiveStateColor = "#ffd320"; // 滑块高亮颜色

        /* 悬停状态使用更粗的特殊边框显示。 */
        const std::string kHoverBorderColor = "blue";
        const double kHoverBorderWidth = 16.0 / 1000; // 1000px 窗口上的 8px

        /* 需要移动多远（弧度）才算作自环。 */
        const double kSelfTransitionThreshold = M_PI / 3;

        const double kNewTransitionWidth = 3.0 / 1000; // 1000px 窗口上的 3px
        const std::string kNewTransitionColor = "red";

        const std::string kActiveTransitionColor = "#ff950e";
        const double kActiveTransitionWidth = GraphEditor::kEdgeTolerance;
        const std::string kHoverTransitionColor = "blue"; // 滑块高亮深色
    }

    EditorBase::EditorBase(std::shared_ptr<ViewerBase> viewer) : mViewer(viewer) {
        // 已在上方处理
    }

    void EditorBase::setActive(Entity* active) {
        if (auto* node = dynamic_cast<Node*>(active)) {
            setActiveNode(node);
        } else if (auto* edge = dynamic_cast<Edge*>(active)) {
            setActiveEdge(edge);
        } else {
            setActiveNode(nullptr);
            setActiveEdge(nullptr);
        }

        /* 将此情况告知用户。 */
        for (auto listener: mListeners) {
            listener->entitySelected(active);
        }
    }

    void EditorBase::setHover(Entity* hover) {
        if (auto* node = dynamic_cast<GraphEditor::Node*>(hover)) {
            setHoverNode(node);
        } else if (auto* edge = dynamic_cast<GraphEditor::Edge*>(hover)) {
            setHoverEdge(edge);
        } else {
            setHoverNode(nullptr);
            setHoverEdge(nullptr);
        }

        /* 将此情况告知用户。 */
        for (auto listener: mListeners) {
            listener->entityHovered(hover);
        }
    }

    void EditorBase::setActiveNode(Node* state) {
        if (activeNode != state) requestRepaint();
        activeNode = state;

        if (activeNode) {
            activeEdge = nullptr;
        }
    }

    void EditorBase::setActiveEdge(Edge* transition) {
        if (activeEdge != transition) requestRepaint();
        activeEdge = transition;

        if (activeEdge != nullptr) {
            activeNode = nullptr;
        }
    }

    void EditorBase::setHoverNode(Node* state) {
        if (hoverNode != state) requestRepaint();
        hoverNode = state;

        if (hoverNode) {
            hoverEdge = nullptr;
        }
    }

    void EditorBase::setHoverEdge(Edge* transition) {
        if (hoverEdge != transition) requestRepaint();
        hoverEdge = transition;

        if (hoverEdge) {
            hoverNode = nullptr;
        }
    }

    void EditorBase::mouseDoubleClicked(double x, double y) {
        GPoint pos = mViewer->graphicsToWorld(GPoint{x, y});

        /* 那里有内容吗？如果有，则不执行任何操作。 */
        if (mViewer->nodeAt(pos)) return;
        if (mViewer->edgeAt(pos)) return;

        auto node = newNode(pos);
        for (auto listener: mListeners) {
            listener->entityCreated(node);
        }

        setHover(node);
        setActive(node);
        requestRepaint();
        dirty();
    }

    void EditorBase::mouseMoved(double x, double y) {
        /* 如果正在拖动鼠标，则跳过此步骤。 */
        if (dragType != DragType::NONE) return;

        GPoint pt = mViewer->graphicsToWorld(GPoint{x, y});

        /* 查看是否点击了某个状态。 */
        if (auto over = mViewer->nodeAt(pt)) {
            setHover(over);
        } else if (auto over = mViewer->edgeAt(pt)) {
            setHover(over);
        } else {
            setHover(nullptr);
        }
    }

    namespace {
        bool isCloseTo(GPoint p0, GPoint p1, double distance) {
            double dx = p0.x - p1.x;
            double dy = p0.y - p1.y;

            return dx * dx + dy * dy <= distance * distance;
        }
    }

    void EditorBase::mousePressed(double x, double y) {
        GPoint pt = mViewer->graphicsToWorld(GPoint{x, y});

        /* 是否命中某个状态？ */
        if (auto over = mViewer->nodeAt(pt)) {
            /* 强制将其同时设为悬停项。这可防止
             * 防止我们在
             * 发生 mousePressed 事件后、期间没有发生其他事件的事件
             * mouseMoved 事件。
             */
            setHover(over);
            setActive(over);

            /* 计算到州中心的距离。 */
            if (isCloseTo(pt, hoverNode->position(), GraphEditor::kNodeRadius - GraphEditor::kEdgeTolerance)) {
                /* 开始拖动状态。 */
                lastState = pt;
                dragType = DragType::NODE;
            } else {
                dragEdge0 = dragEdge1 = pt;
                edgeStart = hoverNode;
                dragType = DragType::EDGE;
            }
        }
        /* 是否命中某个过渡？ */
        else if (auto over = mViewer->edgeAt(pt)) {
            setActive(over);
        }
        /* 没有命中任何内容。 */
        else {
            setActive(nullptr);
        }
    }

    void EditorBase::dragState(GPoint pt) {
        /* TODO：与其他州发生碰撞？ */
        if (hoverNode) {
            hoverNode->position(hoverNode->position() + (lastState - hoverNode->position()));
            lastState = pt;
            requestRepaint();
            dirty();
        }
    }

    void EditorBase::dragTransition(GPoint pt) {
        dragEdge1 = pt;

        setHover(mViewer->nodeAt(pt));
        requestRepaint();
    }

    void EditorBase::mouseDragged(double x, double y) {
        if (dragType == DragType::NODE) {
            dragState(mViewer->graphicsToWorld(GPoint{x, y}));
        } else if (dragType == DragType::EDGE) {
            dragTransition(mViewer->graphicsToWorld(GPoint{x, y}));
        }
    }

    void EditorBase::mouseReleased(double x, double y) {
        if (dragType == DragType::EDGE) {
            finishCreatingEdge(mViewer->graphicsToWorld(GPoint{ x, y }));
        }
        dragType = DragType::NONE;
        requestRepaint();
    }

    void EditorBase::finishCreatingEdge(GPoint pt) {
        /* 首先看看命中了什么。 */
        auto end = mViewer->nodeAt(pt);

        /* 如果这不是状态，则无需执行任何操作。 */
        if (end == nullptr) {
            edgeStart = nullptr;
            return;
        }

        /* 如果这是同一状态，则确认拖动距离足以进行此次
         * 计为自环。
         */
        if (end == edgeStart) {
            double theta0 = angleOf(dragEdge0 - edgeStart->position());
            double theta1 = angleOf(dragEdge1 - edgeStart->position());

            /* 每个角度都在 (-pi, pi] 中，因此差值位于 [-2pi, 2pi]。我们需要一个位于
             * (-pi, pi]。为此，先将其变换到 [0, 2pi]。
             */
            double thetaDiff = theta0 - theta1;
            if (thetaDiff < 0) {
                thetaDiff = fmod(thetaDiff + 2 * M_PI, 2 * M_PI);
            }

            /* 现在，将范围从 [0, 2pi] 平移到 [-pi, pi]。 */
            if (thetaDiff > M_PI) {
                thetaDiff -= 2 * M_PI;
            }

            if (fabs(thetaDiff) < kSelfTransitionThreshold) {
                edgeStart = nullptr;
                return;
            }
        }

        /* 如果边已存在，则选中它且不执行其他操作。 */
        auto* edge = edgeBetween(edgeStart, end);
        if (!edge) {
            edge = newEdge(edgeStart, end);
            for (auto listener: mListeners) {
                listener->entityCreated(edge);
            }
            dirty();
        }

        setActive(edge);
    }

    void EditorBase::dirty() {
        for (auto listener: mListeners) {
            listener->isDirty();
        }
    }

    void EditorBase::drawGraph(GCanvas* canvas,
                               const std::unordered_map<Node*, NodeStyle>& clientNodeStyles,
                               const std::unordered_map<Edge*, EdgeStyle>& clientEdgeStyles) {
        /* 配置样式。 */
        std::unordered_map<Node*, NodeStyle> nodeStyles = clientNodeStyles;
        std::unordered_map<Edge*, EdgeStyle> edgeStyles = clientEdgeStyles;

        /* 活动状态和悬停状态并非互斥！ */
        if (activeNode && !clientNodeStyles.count(activeNode)) {
            nodeStyles[activeNode].fillColor = kActiveStateColor;
        }
        if (hoverNode && !clientNodeStyles.count(hoverNode)) {
            nodeStyles[hoverNode].borderColor = kHoverBorderColor;
            nodeStyles[hoverNode].lineWidth   = kHoverBorderWidth;
            nodeStyles[hoverNode].radius     -= kHoverBorderWidth / 2.0;
        }

        /* 活动过渡始终优先于悬停过渡。 */
        if (hoverEdge && !clientEdgeStyles.count(hoverEdge)) {
            edgeStyles[hoverEdge].lineColor = kHoverTransitionColor;
            edgeStyles[hoverEdge].lineWidth = GraphEditor::kEdgeTolerance;
        }
        if (activeEdge && !clientEdgeStyles.count(activeEdge)) {
            edgeStyles[activeEdge].lineColor = kActiveTransitionColor;
            edgeStyles[activeEdge].lineWidth = kActiveTransitionWidth;
        }

        mViewer->draw(canvas, nodeStyles, edgeStyles);
    }

    void EditorBase::drawDraggedEdge(GCanvas* canvas) {
        if (dragType == DragType::EDGE) {
            mViewer->drawArrow(canvas, dragEdge0, dragEdge1, kNewTransitionWidth, kNewTransitionColor);
        }
    }

    void EditorBase::draw(GCanvas* canvas,
                          const std::unordered_map<Node*, NodeStyle>& nodeStyles,
                          const std::unordered_map<Edge*, EdgeStyle>& edgeStyles) {
        drawGraph(canvas, nodeStyles, edgeStyles);
        drawDraggedEdge(canvas);
    }

    void EditorBase::requestRepaint() {
        for (auto listener: mListeners) {
            listener->needsRepaint();
        }
    }

    void EditorBase::addListener(std::shared_ptr<Listener> listener) {
        mListeners.push_back(listener);
    }

    Node* EditorBase::selectedNode() {
        return activeNode;
    }

    Edge* EditorBase::selectedEdge() {
        return activeEdge;
    }

    /**** 默认监听器接口。****/
    void Listener::isDirty() {
        // 不执行任何操作
    }

    void Listener::needsRepaint() {
        // 不执行任何操作
    }

    void Listener::entityHovered(Entity *) {
        // 不执行任何操作
    }

    void Listener::entitySelected(Entity *) {
        // 不执行任何操作
    }

    void Listener::entityCreated(Entity *) {
        // 不执行任何操作
    }
}
