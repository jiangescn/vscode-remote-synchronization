#include "GraphViewer.h"
#include "../GUI/MiniGUI.h"
#include "GVector.h"
#include "Utilities/Unicode.h"
#include <cmath>
#include <set>
#include <unordered_map>
#include <sstream>
#include <cctype>
using namespace MiniGUI;

namespace GraphEditor {
    namespace {
        /* 有用，但并非必需。 */
        const std::string kNonbreakingSpace = toUTF8(0xA0);

        /* 边的图形参数。 */
        const double kLoopEdgeRadius = GraphEditor::kNodeRadius * 0.75;

        /* 用于绘制环形边内容的不可见线长度。 */
        const double kLoopLabelLength = 150 / 1000.0;

        /* 边的字体和高度。 */
        const double kEdgeTextHeight = 48.0 / 1000; // 1000px 窗口中的 24pt

        /* 标签相对于边的偏移量。 */
        const double kEdgeLabelYOffset = 8.0 / 1000;
        const double kLoopEdgeYOffset  = 30.0 / 1000;

        /* 移动状态时，原点需要旋转的弧度。
         * 边的起始位置。
         */
        const double kAvoidanceRotation = -M_PI / 6;

        /* 箭头参数。 */
        const double kArrowheadRotation = M_PI / 8;
        const double kArrowheadSize     = 0.02;

        /* 用于避免与自环碰撞的参数。 */
        const int kLowAngle = -5;
        const int kHighAngle = 355;
        const int kAngleStep = 10;
    }

    /* 边可以是线形边或环形边。 */
    struct EdgeRender {
        EdgeRender(ViewerBase* editor, Edge* edge): editor(editor), edge(edge) {}
        virtual ~EdgeRender() = default;

        virtual void draw(GCanvas* canvas, double thickness, const std::string& lineColor, const std::string& textColor) const = 0;
        virtual bool contains(const GPoint& pt) const = 0;

        ViewerBase* editor;
        Edge* edge;
    };

    /* 直线边。 */
    struct LineEdge: EdgeRender {
        LineEdge(ViewerBase* editor, Edge* edge, GPoint from, GPoint to) : EdgeRender(editor, edge), lineStart(from), lineEnd(to) {}

        void draw(GCanvas* canvas, double thickness, const std::string& lineColor, const std::string& textColor) const override;
        bool contains(const GPoint& pt) const override;

        GPoint lineStart, lineEnd;
    };

    /* 自环。 */
    struct LoopEdge: EdgeRender {
        LoopEdge(ViewerBase* editor, Edge* edge, const GPoint& center, const GPoint& arrowPt) : EdgeRender(editor, edge), center(center), arrowPt(arrowPt) {}

        void draw(GCanvas* canvas, double thickness, const std::string& lineColor, const std::string& textColor) const override;
        bool contains(const GPoint& pt) const override;

        /* 边由圆表示。该圆的中心在哪里
         * 圆？
         */
        GPoint center;

        /* 绘制箭头的位置。 */
        GPoint arrowPt;
    };

    void ViewerBase::draw(GCanvas* canvas,
                      const std::unordered_map<Node*, NodeStyle>& nodeStyles,
                      const std::unordered_map<Edge*, EdgeStyle>& edgeStyles) {
        /* TODO：此代码仅用于测试。请将其删除。 */
        canvas->setColor("red");
        canvas->drawRect(baseX, baseY, width, height);

        /* 现有边绘制在节点下方，因此看不到线段。 */
        for (auto start: edges) {
            for (auto end: start.second) {
                /* 可能存在 null 条目；跳过它们。 */
                /* TODO：这是真的吗？ */
                if (end.second) {
                    auto style = edgeStyles.count(end.second.get()) ? edgeStyles.at(end.second.get()) : EdgeStyle();
                    end.second->style->draw(canvas, style.lineWidth, style.lineColor, style.labelColor);
                }
            }
        }

        /* 节点。 */
        for (auto node: nodes) {
            auto style = nodeStyles.count(node.get())? nodeStyles.at(node.get()) : NodeStyle();

            node->draw(this, canvas, style);
        }
    }

    namespace {
        bool isCloseTo(GPoint p0, GPoint p1, double distance) {
            double dx = p0.x - p1.x;
            double dy = p0.y - p1.y;

            return dx * dx + dy * dy <= distance * distance;
        }
    }

    double ViewerBase::graphicsToWorld(double width) {
        return width / this->width;
    }
    GPoint ViewerBase::graphicsToWorld(GPoint in) {
        return { (in.x - baseX) / width, (in.y - baseY) / width };
    }
    GRectangle ViewerBase::graphicsToWorld(GRectangle in) {
        auto top = graphicsToWorld(GPoint{ in.x, in.y });
        auto bot = graphicsToWorld(GPoint{ in.x + in.width, in.y + in.height });
        return { top.x, top.y, bot.x - top.x, bot.y - top.y };
    }

    double ViewerBase::worldToGraphics(double width) {
        return width * this->width;
    }
    GPoint ViewerBase::worldToGraphics(GPoint in) {
        return { in.x * width + baseX, in.y * width + baseY };
    }
    GRectangle ViewerBase::worldToGraphics(GRectangle in) {
        auto top = worldToGraphics(GPoint{ in.x, in.y });
        auto bot = worldToGraphics(GPoint{ in.x + in.width, in.y + in.height });
        return { top.x, top.y, bot.x - top.x, bot.y - top.y };
    }

    /* 所有参数均采用世界坐标。 */
    void ViewerBase::drawArrow(GCanvas* canvas, const GPoint& from, const GPoint& to,
                               double thickness, const std::string& color) {
        GLine line(worldToGraphics(from), worldToGraphics(to));
        line.setLineWidth(ceil(thickness * width));
        line.setColor(color);

        canvas->draw(&line);

        drawArrowhead(canvas, from, to, thickness, color);
    }

    void ViewerBase::drawArrowhead(GCanvas* canvas, const GPoint& from, const GPoint& to,
                                   double thickness, const std::string& color) {
        /* 如果图是无向的，则跳过箭头。 */
        if (type() == Type::UNDIRECTED) return;

        /* 绘制箭头。首先获取一个从终点指向起点的向量，以便
         * 可以移动它来计算端点。
         */
        GVector v = normalizationOf(from - to);

        /* 计算两个端点。 */
        GPoint left  = to + rotate(v, kArrowheadRotation)  * kArrowheadSize;
        GPoint right = to + rotate(v, -kArrowheadRotation) * kArrowheadSize;

        GLine line(worldToGraphics(left), worldToGraphics(to));
        line.setLineWidth(ceil(thickness * width));
        line.setColor(color);
        canvas->draw(&line);

        line.setStartPoint(worldToGraphics(right));
        canvas->draw(&line);
    }

    namespace {
        /* 给定二次方程，返回是否存在满足以下条件的解：
         * 对应于线/圆交点。这会在存在解时发生
         * 除非两个交点都小于零，或者两个交点都
         * 大于一。
         */
        size_t quadraticSolnsInRange(double a, double b, double c) {
            double discriminant = b * b - 4 * a * c;
            if (discriminant < 0) return 0;

            double x1 = (-b + sqrt(discriminant)) / (2 * a);
            double x2 = (-b - sqrt(discriminant)) / (2 * a);

            return !((x1 < 0 && x2 < 0) || (x1 > 1 && x2 > 1));
        }

        /* 统计一个圆与一组线段的碰撞数。 */
        size_t collisionsBetween(const GPoint& center, double radius,
                                 const std::vector<std::pair<GPoint, GPoint>>& lines) {
            /* 圆上的任意点 (x, y) 满足
             *
             *    (x - x_c)^2 + (y - y_c)^2 = r^2.
             *
             * 从 p0 到 p1 的线段上的任意点具有参数形式
             *
             *    (x(t), y(t)) = p0 + t(p1 - p0).
             *
             * 代入后得到
             *
             *    (p0x + t(p1x - p0x) - x_c)^2 + (p0y + t(p1y - p0y) - y_c)^2 = r^2
             *
             * 这里除 t 外的所有内容都是常量。分离 t 并化简后得到
             *
             *    (t(p1x - p0x) + p0x - x_c)^2 + (t(p1y - p0y) + p0y - y_c)^2 = r^2
             *       --- dx --                     --- dy ---
             *
             *    (t * dx + p0x - x_c)^2 + (t * dy + p0y - y_c)^2 = r^2
             *              --- sx --                -- sy ---
             *
             *    (t * dx + sx)^2 + (t * dy + sy)^2 = r^2
             *
             *    ((dx)^2 t^2 + 2*dx*sx*t + (sx)^2) + ((dy)^2 t^2 + 2*dy*dy*t + (sy)^2) = r^2
             *
             *    ((dx)^2 + (dy)^2) t^2 + 2(dx*sx + dy*sy) t + ((sx)^2 + (sy)^2 - r^2) = 0
             *        dot(d, d) t^2 + 2 dot(d, s) t + (dot(s, s) - r^2) = 0
             *
             * 此时这是一个二次方程，只需计算解的数量。
             */
            size_t solns = 0;
            for (const auto& line: lines) {
                GVector d = line.second - line.first;
                GVector s = line.first - center;

                solns += quadraticSolnsInRange(dot(d, d), 2 * dot(d, s), dot(s, s) - radius * radius);
            }
            return solns;
        }

        size_t collisionsBetween(const GPoint&, double,
                                 const std::vector<std::pair<GPoint, double>>&) {
            /* TODO：实现此函数以统计圆/圆碰撞。 */
            return 0;
        }

        /* 给定一组圆和线以及一个新圆，确定有多少
         * 存在多少冲突。此处统计的是发生冲突的实体数量，而不是
         * 总体碰撞点数量。
         */
        size_t collisionsBetween(const GPoint& center, double radius,
                                 const std::vector<std::pair<GPoint, GPoint>>& lines,
                                 const std::vector<std::pair<GPoint, double>>& circles) {
            return collisionsBetween(center, radius, lines) +
                   collisionsBetween(center, radius, circles);
        }

        /* 确定自环的最佳朝向角度，即
         * 与其他对象相交数量最少。
         */
        double bestThetaFor(const GPoint& nodeCenter, const std::vector<std::pair<GPoint, GPoint>>& lines,
                            const std::vector<std::pair<GPoint, double>>& circles) {
            /* 放置圆的算法如下。我们遍历固定的
             * 可使用的潜在角度数量。对于每个角度，我们统计
             * 如果将圆放在那里会产生的碰撞数量，并形成一个数组
             * 可将其视为碰撞的“高度图”。
             *
             * 然后找出最小碰撞次数，并寻找最长范围
             * 数组中（记得结束时循环回开头！），这
             * 对应于我们能找到的最大误差范围。然后从那里
             * 选择该范围的中点。
             *
             * TODO：如果使用某种良好的方式来实现，会优雅得多
             * 以及严谨的数学，而不是反复试错。你能改进它吗？
             */
            std::vector<std::size_t> collisions;
            for (int degAngle = kLowAngle; degAngle < kHighAngle; degAngle += kAngleStep) {
                double theta = degAngle * M_PI / 180;
                GPoint center = nodeCenter + unitToward(theta) * kNodeRadius;

                collisions.push_back(collisionsBetween(center, kLoopEdgeRadius, lines, circles));
            }

            /* 找到最小冲突数。 */
            size_t min = *min_element(collisions.begin(), collisions.end());

            /* 找到最小值的最长连续范围。 */
            size_t bestStart  = 0;
            size_t bestLength = 0;

            size_t currStart  = 0;
            size_t currLength = 0;

            /* 为处理回绕，请从数组末尾向前扫描并查找
             * 第一个不是最小值的位置。
             */
            for (size_t i = collisions.size(); i > 0; --i) {
                if (collisions[i - 1] != min) break;

                /* 后退一步。 */
                currStart = (currStart + collisions.size() - 1) % collisions.size();
                currLength++;
            }

            for (size_t i = 0; i < collisions.size(); i++) {
                /* 不匹配？必须停止。 */
                if (collisions[i] != min) {
                    if (bestLength < currLength) {
                        bestLength = currLength;
                        bestStart  = currStart;
                    }
                    currLength = 0;
                    currStart  = i+1;
                }
                /* 否则，扩展。 */
                else {
                    currLength++;
                }
            }

            /* 处理在末尾找到最优项的边界情况。 */
            if (bestLength < currLength) {
                bestLength = currLength;
                bestStart  = currStart;
            }

            /* 此处必须转换为 double，以避免负数导致奇怪的整数溢出
             * 角度会变成极大的正无符号角度！
             */
            double lowTheta   = (kLowAngle + double(bestStart * kAngleStep)) * M_PI / 180;
            double highTheta  = (kLowAngle + double(bestStart + bestLength - 1) * kAngleStep) * M_PI / 180;
            return (lowTheta + highTheta) / 2;
        }

        /* 给定节点中心和环中心所在点，返回
         * 它们相交的点——可在此处绘制箭头。
         */
        GPoint loopArrowPointFor(const GPoint& nodeCenter, const GPoint& loopCenter) {
            /* 开始三角计算！这里有两个圆，其中一个的圆心位于
             * 另一个。然后我们希望找到其中一个交点。如何
             * 执行它？
             *
             * 现在假设所有内容都共线，如下所示：
             *
             *                *
             *               / \
             *           r  /   \ r'
             *             /  r  \
             *            * ----- *
             *          节点      环
             *         居中     居中
             *
             * 我们想知道节点中心与
             * 环的中心，以及第三个三角形顶点（两者的交点）。
             * 余弦定理告诉我们
             *
             *       r'^2 = r^2 + r^2 - 2r^2 cos theta
             *
             * 经过一些整理后，得到
             *
             *       theta = arccos(1 - r'^2 / 2r^2)
             *
             * 使用此值获取该角度大小。
             */
            double theta = acos(1 - kLoopEdgeRadius * kLoopEdgeRadius / (2 * kNodeRadius * kNodeRadius));

            /* 将从节点到环中心的向量旋转此角度。 */
            return nodeCenter + rotate(loopCenter - nodeCenter, theta);
        }

        /* 以线段表示的世界边界。 */
        std::vector<std::pair<GPoint, GPoint>> worldBoundaries(double aspectRatio) {
            const double lft = 0;
            const double rgt = 1;
            const double top = 0;
            const double bot = 1 / aspectRatio;

            return {
                { { lft, top }, { rgt, top } },
                { { lft, bot }, { rgt, bot } },
                { { lft, top }, { lft, bot } },
                { { rgt, top }, { rgt, bot } },
            };
        }
    }

    /* 确定每条边的起点和终点。其间存在依赖关系
     * 跨越这些边，因此需要一次性完成此操作。
     */
    void ViewerBase::calculateEdgeEndpoints() {
        /* 所有使用过的线段列表。 */
        std::vector<std::pair<GPoint, GPoint>> lines = worldBoundaries(mAspectRatio);

        /* 首先处理线形边。 */
        forEachEdge([&](Edge* edge) {
            if (edge->from() != edge->to()) {
                /* 中心坐标。 */
                GPoint p0 = edge->from()->position();
                GPoint p1 = edge->to()->position();

                /* 如果存在一条反方向的边，需要偏移
                 * 将这条边移过去，以免与其重叠。
                 *
                 * 如果图是无向的，则跳过此步骤。
                 */
                if (type() == Type::DIRECTED && hasEdge(edge->to(), edge->from())) {
                    /* 指向 p0 -> p1 方向的单位向量，表示需要旋转多少。 */
                    auto p0Delta = rotate(normalizationOf(p1 - p0), kAvoidanceRotation);

                    /* 指向 p1 -> p0 方向的单位向量，表示需要旋转多少。 */
                    auto p1Delta = rotate(normalizationOf(p0 - p1), -kAvoidanceRotation);

                    /* 在边界处。 */
                    p0 += p0Delta * kNodeRadius;
                    p1 += p1Delta * kNodeRadius;
                }
                /* 否则，将中心点平移到边界。 */
                else {
                    p0 += normalizationOf(p1 - p0) * kNodeRadius;
                    p1 += normalizationOf(p0 - p1) * kNodeRadius;
                }

                edge->style = std::make_shared<LineEdge>(this, edge, p0, p1);
                lines.push_back(std::make_pair(p0, p1));
            }
        });

        /* 所有已放置的圆。最初就是所有节点。 */
        std::vector<std::pair<GPoint, double>> circles;
        for (auto node: nodes) {
            circles.push_back(std::make_pair(node->position(), kNodeRadius));
        }

        /* 现在，放置所有自环。 */
        forEachEdge([&](Edge* edge) {
            if (edge->from() == edge->to()) {
                double theta = bestThetaFor(edge->from()->position(), lines, circles);

                GPoint center  = edge->from()->position() + unitToward(theta) * kNodeRadius;
                GPoint arrowPt = loopArrowPointFor(edge->from()->position(), center);

                edge->style = std::make_shared<LoopEdge>(this, edge, center, arrowPt);
                circles.push_back(std::make_pair(center, kNodeRadius));
            }
        });
    }

    /* 直线边实现。 */
    bool LineEdge::contains(const GPoint& pt) const {
        /* 目标是同时查看：（1）离线多远；（2）沿线多远
         * 在线段上的进度位置。
         *
         * 为此，我们将改变坐标系。令 b1 为一个指向
         * 相对于该线向右旋转 90 度，并令 b2 为指向下方的向量
         * 该直线。由此得到以下坐标系：
         *
         *              b2
         *              ^
         *              |
         *              |
         *          ----+----> b1
         *
         * 现在，我们在此坐标系中重写光标位置。这样做是为了
         * 通过将光标向量乘以旋转矩阵 [b1, b2]。
         *
         * 从这里可以看到当前位置。对于“足够接近”，我们规定
         * 光标的 x 坐标需要使其位于悬停宽度内，
         * 并且它需要具有介于零和线段长度之间的 y 坐标。
         */

        /* 切换坐标系，将边的原点放在 (0, 0)。 */
        GVector cursor = pt - lineStart;

        /* 获取向量 b1 和 b2。 */
        GVector lineVec = lineEnd - lineStart;

        GVector b2 = lineVec / magnitudeOf(lineVec);
        GVector b1 = rotate(b2, M_PI / 2);

        /* 计算光标在此系统中的表示，即
         *
         * | b1x b2x | |cx|
         * | b1y b2y | |cy|
         */
        GVector result = GMatrix(b1, b2) * cursor;

        /* 确保位于范围内。 */
        return fabs(result.x) <= kEdgeTolerance / 2.0 &&
               result.y >= 0 && result.y <= magnitudeOf(lineVec);
    }

    namespace {
        /* 这是空白字符吗？ */
        bool isSpace(char32_t ch) {
            return ch >= 0 && ch <= 127 && isspace(ch);
        }

        /* 给定字符串，将字符串中的所有空格替换为不换行空格。
         *
         * TODO：删除此项并替换为 LineBreak::NO_BREAK_SPACES。
         */
        std::string toNonbreakingSpaces(const std::string& input) {
            std::string result;
            for (char32_t ch: utf8Reader(input)) {
                if (isSpace(ch)) {
                    result += kNonbreakingSpace;
                } else {
                    result += toUTF8(ch);
                }
            }

            return result;
        }
    }

    void ViewerBase::drawEdgeLabel(GCanvas* canvas,
                                   const GPoint& p0, const GPoint& p1,
                                   const std::string& labelText,
                                   const std::string& color,
                                   bool hugLine) {
        GPoint from = worldToGraphics(p0);
        GPoint to   = worldToGraphics(p1);

        std::string label = toNonbreakingSpaces(labelText);

        /* 确定此线段的长度。 */
        double length = magnitudeOf(to - from);

        /* 通过计算文本渲染结果确定标签应使用的字体
         * 并提取其使用的字体。
         */
        Font font = TextRender::construct(label, {0, 0, length, width * kEdgeTextHeight }, kEdgeFont.color(color))->computedFont();

        /* 为标签创建图形对象。 */
        GText text(label);
        text.setFont(font.stanfordCPPLibFontString());
        text.setColor(font.color());

        /* 确定标签需要放置的位置。 */
        double theta = angleOf(to - from);

        /* 绝不倒置绘制文本。判断我们位于线的上方还是下方。 */
        if (theta < -M_PI / 2 || theta > M_PI / 2) {
            /* 位于线下方。将角度旋转 180 度并交换以下角色：
             * 端点。
             */
            theta += M_PI;
            std::swap(to, from);

            /* 如果应当贴着线，需要额外一步并偏移
             * 将线的位置移开，使我们在其上绘制时看起来像刚刚
             * 仅翻转，而不是翻转并平移。
             */
            if (hugLine) {
                /* 获取垂直于线段的向量。 */
                GVector normal = rotate(normalizationOf(to - from), M_PI / 2) * text.getHeight();
                from += normal;
                to   += normal;
            }
        }

        /* 我们将以边作为基线进行绘制，
         * 因此需要计算边中心的 (x, y) 坐标。
         *
         * ... 但它并非精确中心，而是以下对象的中心：
         * 边，并偏移标签宽度的一半。换句话说，我们希望
         * 走到中心，然后再向前移动一点
         */
        GPoint target = from + normalizationOf(to - from) * (length - text.getWidth()) / 2.0;

        /* 现在，向上移离该线。 */
        target += rotate(normalizationOf(to - from), -M_PI / 2) * ceil(width * kEdgeLabelYOffset);

        /* GText 旋转时的行为比较特殊。旋转围绕
         * 图形原点 (0, 0)，而不是对象的中心。
         * 这意味着我们需要重新定位标签，使其旋转
         * 将文本放入我们需要的精确位置。
         *
         * 目标：给定目标位置 (x, y)，找到一个位置
         * (x', y')，使其旋转后与 (x, y) 重合。
         *
         * 给定旋转角度 theta，对象的实际位置
         * 其位置为 ROT(theta) (x', y')。
         *
         * 因此需要 ROT(theta) (x', y') = (x, y)，这意味着
         * (x', y') = ROT(-theta)(x, y)。
         */
        GPoint textPos = rotation(-theta) * target;

        /* GText 的旋转角度以度为单位。 */
        text.rotate(theta * 180 / M_PI);
        text.setLocation(textPos);
        canvas->draw(&text);
    }

    Node* ViewerBase::nodeAt(const GPoint& pt) {
        /* TODO：是否需要反向执行，以便我们选择
         * 最上方节点？
         */
        for (auto node: nodes) {
            if (isCloseTo(pt, node->position(), kNodeRadius)) {
                return node.get();
            }
        }

        return nullptr;
    }

    Edge* ViewerBase::edgeAt(const GPoint& pt) {
        for (const auto& one: edges) {
            for (const auto& two: one.second) {
                /* 获取边本身。 */
                auto edge = two.second;

                if (edge->style->contains(pt)) {
                    return edge.get();
                }
            }
        }

        return nullptr;
    }

    void LineEdge::draw(GCanvas* canvas, double thickness, const std::string& lineColor, const std::string& labelColor) const {
        editor->drawArrow(canvas, lineStart, lineEnd, thickness, lineColor);
        editor->drawEdgeLabel(canvas, lineStart, lineEnd, edge->label(), labelColor, false);
    }

    bool LoopEdge::contains(const GPoint& pt) const {
        /* 如果到圆心的距离在圆的
         * 实际半径。
         */
        return fabs(magnitudeOf(pt - center) - kLoopEdgeRadius) < kEdgeTolerance;
    }

    void LoopEdge::draw(GCanvas* canvas, double width, const std::string& lineColor, const std::string& labelColor) const {
        double size = 2 * editor->width * kLoopEdgeRadius;
        GPoint pt = editor->worldToGraphics(center);

        GOval toDraw(pt.x - size / 2, pt.y - size / 2, size, size);
        toDraw.setColor(lineColor);
        toDraw.setLineWidth(ceil(editor->width * width));
        canvas->draw(&toDraw);

        /* 绘制箭头。你可能会认为箭头应当
         * 使其看起来像是沿圆的法线方向进入节点
         * 在交点处，但令人意外的是，这样看起来并不好。
         * 相反，最好看起来像是击中了圆
         * 与节点中心和环中心之间所画线条相切
         * 中心。
         */
        GPoint exterior = arrowPt + (center - edge->from()->position());
        editor->drawArrowhead(canvas, exterior, arrowPt, width, lineColor);


        /* 我们将想象存在一条不可见的切线来绘制边的内容
         * 连接到我们将覆盖绘制的圆的线。
         */

        /* 获取一个远离圆心的向量。 */
        GVector out = normalizationOf(center - edge->from()->position());

        /* 向外移动到循环末端。 */
        GPoint tangentPoint = center + out * (kLoopEdgeRadius + kLoopEdgeYOffset);

        /* 构造垂直向量并用它形成一条线。 */
        GVector tangent = rotate(out, M_PI / 2);
        GPoint p0 = tangentPoint + tangent * kLoopLabelLength / 2;
        GPoint p1 = tangentPoint - tangent * kLoopLabelLength / 2;
        editor->drawEdgeLabel(canvas, p0, p1, edge->label(), labelColor, true);
    }

    void ViewerBase::forEachNode(std::function<void (Node *)> callback) {
        for (const auto& node: nodes) {
            callback(node.get());
        }
    }

    void ViewerBase::forEachEdge(std::function<void (Edge *)> callback) {
        for (const auto& e1: edges) {
            for (const auto& e2: e1.second) {
                callback(e2.second.get());
            }
        }
    }

    bool ViewerBase::hasEdge(Node* from, Node* to) {
        return edgeBetween(from, to) != nullptr;
    }

    Edge* ViewerBase::edgeBetween(Node* from, Node* to) {
        /* 如果图是无向的，则将 from 和 to 调整为正确顺序。 */
        if (type() == Type::UNDIRECTED && from->index() >= to->index()) {
            std::swap(from, to);
        }

        if (!edges.count(from) || !edges.at(from).count(to)) return nullptr;
        return edges.at(from).at(to).get();
    }

    Type ViewerBase::type() const {
        return mType;
    }

    void ViewerBase::type(Type type) {
        /* 如果类型已与底层类型匹配，这可能是空操作。 */
        if (type == mType) return;

        /* 将无向图转换为有向图在内部基本上是空操作。 */
        if (type == Type::DIRECTED) {
            // 无需执行任何操作
        }
        /* 将有向图转换为无向图需要删除所有自环
         * 并用于在边对之间打破平局。
         */
        else if (type == Type::UNDIRECTED) {
            std::vector<Edge*> toNix;
            std::vector<Edge*> toFlip;
            forEachEdge([&](Edge* edge) {
                /* 确保所有边满足 from() < to() 的不变式。 */
                if (edge->from()->index() >= edge->to()->index()) {
                    /* 如果反向边存在，则删除它。这也会处理
                     * 自环。
                     */
                    if (edgeBetween(edge->to(), edge->from())) {
                        toNix.push_back(edge);
                    } else {
                        toFlip.push_back(edge);
                    }
                }
            });

            /* 删除所有需要处理的边。 */
            for (Edge* edge: toNix) {
                removeEdge(edge);
            }

            /* 翻转所有其他边。 */
            for (Edge* flip: toFlip) {
                /* 反转底层映射。 */
                edges[flip->to()][flip->from()] = edges[flip->from()][flip->to()];
                edges[flip->from()][flip->to()].reset();

                /* 更改底层边的详细信息。 */
                std::swap(flip->mFrom, flip->mTo);
            }
        }

        /* 设置类型以供后续使用。 */
        mType = type;
    }

    void ViewerBase::removeEdge(Edge* edge) {
        edges[edge->from()].erase(edge->to());
        calculateEdgeEndpoints();
    }

    Node* ViewerBase::nodeLabeled(const std::string& label) {
        for (auto node: nodes) {
            if (node->label() == label) return node.get();
        }

        return nullptr;
    }

    GRectangle ViewerBase::bounds() const {
        return rawBounds;
    }

    GRectangle ViewerBase::computedBounds() const {
        return { baseX, baseY, width, height };
    }

    size_t ViewerBase::numNodes() {
        return nodes.size();
    }

    void ViewerBase::setBounds(const GRectangle& bounds) {
        rawBounds = bounds;

        /* 太窄了吗？ */
        if (bounds.width / bounds.height <= mAspectRatio) {
            width = bounds.width;
            height = width / mAspectRatio;
        } else {
            height = bounds.height;
            width = height * mAspectRatio;
        }

        baseX = bounds.x + (bounds.width  - width)  / 2.0;
        baseY = bounds.y + (bounds.height - height) / 2.0;
    }

    double ViewerBase::aspectRatio() {
        return mAspectRatio;
    }

    void ViewerBase::aspectRatio(double ratio) {
        mAspectRatio = ratio;
        setBounds(rawBounds); // 重新计算到最后提供的矩形。
    }

    Node::Node(ViewerBase* editor, const NodeArgs& args, JSON)
        : Node(editor, args) {
        // 已转发！
    }

    Node::Node(ViewerBase* editor, const NodeArgs& args)
        : owner(editor), mPos(args.pt), mIndex(args.index), mLabel(args.label) {
        owner->calculateEdgeEndpoints();
    }

    const std::string& Node::label() {
        return mLabel;
    }
    void Node::label(const std::string& label) {
        mLabel = label;
    }

    const GPoint& Node::position() {
        return mPos;
    }

    size_t Node::index() {
        return mIndex;
    }

    void Node::position(const GPoint& pt) {
        /* 限制到适当边界。 */
        double x = pt.x;
        if (x < kNodeRadius) x = kNodeRadius;
        if (x > 1 - kNodeRadius) x = 1 - kNodeRadius;

        double y = pt.y;
        if (y < kNodeRadius) y = kNodeRadius;
        if (y > 1 / owner->aspectRatio() - kNodeRadius) y = 1 / owner->aspectRatio() - kNodeRadius;

        mPos = { x, y };
        owner->calculateEdgeEndpoints();
    }

    void Node::draw(ViewerBase* editor, GCanvas* canvas, const NodeStyle& style) {
        /* 计算节点大小。 */
        double size = 2.0 * style.radius;
        auto bounds = editor->worldToGraphics({ position().x - size / 2.0, position().y - size / 2.0, size, size });

        GOval mainNode(bounds.x, bounds.y, bounds.width, bounds.height);

        mainNode.setFilled(true);
        mainNode.setFillColor(style.fillColor);
        mainNode.setLineWidth(ceil(editor->worldToGraphics(style.lineWidth)));
        mainNode.setColor(style.borderColor);
        canvas->draw(&mainNode);

        /* 绘制节点名称。 */
        auto render = TextRender::construct(label(), bounds, kNodeFont.color(style.textColor));
        render->alignCenterVertically();
        render->alignCenterHorizontally();
        render->draw(canvas);
    }

    Edge::Edge(ViewerBase* owner, const EdgeArgs& args, JSON)
        : Edge(owner, args) {
        // 已转发
    }

    Edge::Edge(ViewerBase* owner, const EdgeArgs& args)
        : mOwner(owner), mFrom(args.from), mTo(args.to), mLabel(args.label) {
        owner->calculateEdgeEndpoints();
    }

    Node* Edge::to() {
        return mTo;
    }

    Node* Edge::from() {
        return mFrom;
    }

    std::string Edge::label() {
        return mLabel;
    }

    void Edge::label(const std::string& label) {
        mLabel = label;
    }

    /*** 序列化/反序列化 ***/

    /* JSON 格式为
     *
     * {"nodes", [<节点数据>],
     *  “edges”，[<边数据>]，
     *  “aux”，<辅助数据>，
     *  “type”，<图类型>}
     *
     * 这里，每个节点编码为
     *
     *   { "index": <索引>, "label": <标签>, "pos": [<x>, <y>], "aux": <辅助数据> }
     *
     * 每条边编码为
     *
     *   { "from": <索引>, "to": <索引>, "label": <标签> }
     */

    JSON ViewerBase::nodesToJSON() {
        std::vector<JSON> result;
        for (auto node: nodes) {
            result.push_back(toJSON(node.get()));
        }
        return result;
    }

    JSON ViewerBase::toJSON(Node* node) {
        return JSON::object({
            { "index", node->index() },
            { "label", node->label() },
            { "pos",   JSON::array(node->position().x, node->position().y) },
            { "aux",   node->toJSON() }
        });
    }

    JSON ViewerBase::edgesToJSON() {
        std::vector<JSON> result;
        forEachEdge([&](Edge* edge) {
            result.push_back(toJSON(edge));
        });
        return result;
    }

    JSON ViewerBase::typeToJSON() {
        if (mType == Type::DIRECTED) {
            return "directed";
        } else if (mType == Type::UNDIRECTED) {
            return "undirected";
        } else {
            error("Unknown graph type?");
        }
    }

    /* 默认辅助数据为空。 */
    JSON ViewerBase::auxData() {
        return nullptr;
    }

    JSON ViewerBase::toJSON(Edge* edge) {
        return JSON::object({
            { "from",  edge->from()->index() },
            { "to",    edge->to()->index()   },
            { "label", edge->label()         },
            { "aux",   edge->toJSON()        }
        });
    }

    /* 序列化为 JSON。 */
    JSON ViewerBase::toJSON() {
        /* 将其与序列化的 NFA 配对。 */
        return JSON::object({
            { "nodes", nodesToJSON() },
            { "edges", edgesToJSON() },
            { "aux",   auxData()     },
            { "type",  typeToJSON()  }
        });
    }

    /* 默认序列化器。 */
    JSON Node::toJSON() {
        return nullptr;
    }
    JSON Edge::toJSON() {
        return nullptr;
    }
}
