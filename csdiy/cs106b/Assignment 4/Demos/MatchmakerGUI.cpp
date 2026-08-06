#include "Matchmaker.h"
#include "GUI/MiniGUI.h"
#include "GraphEditor/GraphEditor.h"
#include <fstream>
#include <algorithm>
#include "filelib.h"
using namespace std;
using namespace MiniGUI;

ostream& operator<< (ostream& out, const Pair& pair) {
    ostringstream builder;
    builder << "{ " << quotedVersionOf(pair.first()) << ", " << quotedVersionOf(pair.second()) << " }";
    return out << builder.str();
}

namespace {
    const string kUnsavedChanges = "You have unsaved changes.\n\nDo you want to save?";
    const string kUnsavedChangesTitle = "Unsaved Changes";

    const string kUntitledGraph = "(Untitled)";

    const string kBaseDir = "res/matchmaker/";
    const string kFileExtension = "";

    const string kWelcome = R"(Click "Load Graph" to choose a graph, or "New Graph" to make a new graph.)";

    const Font   kWelcomeFont(FontFamily::SERIF, FontStyle::BOLD_ITALIC, 24, "#4C5866"); // Marengo

    const string kInstructions = R"(Double-click to add a node.)";
    const Font&  kInstructionsFont  = kWelcomeFont;

    const string kBackgroundColor = "white";

    const string kNoPerfectMatching = "No perfect matching exists.";
    const string kNoPerfectMatchingTitle = "No Perfect Matching";

    const int kMinWeight = 1;
    const int kMaxWeight = 10;
    const int kDefaultWeight = 1;

    class MatchmakerGUI: public ProblemHandler {
    public:
        MatchmakerGUI(GWindow& window);

        /* 转发给相关监听器。 */
        void mouseDoubleClicked(double x, double y) override;
        void mouseMoved(double x, double y) override;
        void mousePressed(double x, double y) override;
        void mouseDragged(double x, double y) override;
        void mouseReleased(double x, double y) override;

        void actionPerformed(GObservable* source) override;
        void changeOccurredIn(GObservable* source) override;
        void windowResized() override;

        bool shuttingDown() override;

    protected:
        void repaint() override;

    private:
        shared_ptr<GraphEditor::Editor<>> editor;

        /* 当前匹配（如果有）。 */
        unique_ptr<Set<Pair>> currMatching;

        /* 面板布局：
         *
         * [文件名] [              删除按钮                  ]
         * [新建按钮 ] [              权重滑块                  ]
         * [保存按钮 ]
         * [加载按钮 ]
         *
         * [ 查找完美匹配 ][ 最大权重匹配  ]
         */
        Temporary<GContainer> controls;
        GLabel*  fileLabel;
        GButton* newButton;
        GButton* saveButton;
        GButton* loadButton;
        GButton* deleteButton;

        GContainer* graphControls;
        GButton* perfectMatchButton;
        GButton* maxWeightMatchButton;
        GSlider* edgeWeightSlider;

        void dirty(bool isDirty = true);
        void entitySelected(GraphEditor::Entity* entity);
        void entityCreated(GraphEditor::Entity* entity);

        void initEditor(shared_ptr<GraphEditor::Viewer<>> viewer);
        void initChrome();

        void deleteSelected();
        void setEditorBounds();

        void drawWelcomeMessage();
        void drawInstructions();

        GRectangle contentArea();

        void userLoad();
        void load(const string& filename);

        void newGraph();
        void userNewGraph();

        bool userSave();
        void save();

        bool handleUnsavedChanges();

        void findPerfectMatching();
        void findMaxWeightMatching();

        void drawGraph();

        /* 是否选中了任何内容？ */
        bool somethingSelected = false;

        /* 脏位。 */
        bool isDirty = false;

        /* 当前文件名。 */
        string currFilename;

        /* 这是否为新文件。 */
        bool isNew = false;
    };

    MatchmakerGUI::MatchmakerGUI(GWindow& window) : ProblemHandler(window) {
        initChrome();
        dirty(false);
    }

    void MatchmakerGUI::initChrome() {
        GContainer* leftPanel = new GContainer(GContainer::LAYOUT_FLOW_VERTICAL);
        fileLabel = new GLabel("Choose a Graph");
        newButton  = new GButton("New Graph");
        saveButton = new GButton("Save Graph");
        saveButton->setEnabled(false);
        loadButton = new GButton("Load Graph");

        leftPanel->add(fileLabel);
        leftPanel->add(newButton);
        leftPanel->add(saveButton);
        leftPanel->add(loadButton);

        deleteButton = new GButton("Delete");
        perfectMatchButton   = new GButton("Find Perfect Matching");
        maxWeightMatchButton = new GButton("Find Max-Weight Matching");

        edgeWeightSlider = new GSlider(kMinWeight, kMaxWeight, kDefaultWeight);

        controls = make_temporary<GContainer>(window(), "SOUTH", GContainer::LAYOUT_GRID);
        controls->addToGrid(leftPanel, 0, 0, 3, 1);
        controls->addToGrid(deleteButton, 1, 1);

        graphControls = new GContainer();
        graphControls->add(perfectMatchButton);
        graphControls->add(maxWeightMatchButton);
        graphControls->add(new GLabel("Edge weight: "));
        graphControls->add(edgeWeightSlider);
        controls->addToGrid(graphControls, 4, 0, 1, 2);

        graphControls->setEnabled(false);

        controls->setWidth(window().getWidth() * 0.9);

        /* 明确说明当前未选择任何内容。 */
        entitySelected(nullptr);
    }

    void MatchmakerGUI::initEditor(shared_ptr<GraphEditor::Viewer<>> viewer) {
        editor = make_shared<GraphEditor::Editor<>>(viewer);

        class Listener: public GraphEditor::Listener {
        public:
            Listener(MatchmakerGUI* owner) : owner(owner) {

            }

            void needsRepaint() {
                owner->requestRepaint();
            }
            void isDirty() {
                owner->dirty();
            }
            void entitySelected(GraphEditor::Entity* entity) {
                owner->entitySelected(entity);
            }
            void entityCreated(GraphEditor::Entity* entity) {
                owner->entityCreated(entity);
            }

        private:
            MatchmakerGUI* owner;
        };

        editor->addListener(make_shared<Listener>(this));
        setEditorBounds();
        entitySelected(nullptr);
        dirty(false);
        currMatching.reset();
        graphControls->setEnabled(true);
        requestRepaint();
    }

    void MatchmakerGUI::mouseDoubleClicked(double x, double y) {
        if (editor) editor->mouseDoubleClicked(x, y);
    }
    void MatchmakerGUI::mouseMoved(double x, double y) {
        if (editor) editor->mouseMoved(x, y);
    }
    void MatchmakerGUI::mousePressed(double x, double y) {
        if (editor) editor->mousePressed(x, y);
    }
    void MatchmakerGUI::mouseDragged(double x, double y) {
        if (editor) editor->mouseDragged(x, y);
    }
    void MatchmakerGUI::mouseReleased(double x, double y) {
        if (editor) editor->mouseReleased(x, y);
    }

    void MatchmakerGUI::repaint() {
        clearDisplay(window(), kBackgroundColor);
        if (editor) {
            if (editor->viewer()->numNodes() == 0) {
                drawInstructions();
            } else {
                drawGraph();
            }
        } else {
            drawWelcomeMessage();
        }
    }

    void MatchmakerGUI::entitySelected(GraphEditor::Entity* entity) {
        somethingSelected = !!entity;
        deleteButton->setEnabled(somethingSelected);

        /* 如果这是边，则调整权重滑块。 */
        if (auto* edge = dynamic_cast<GraphEditor::Edge*>(entity)) {
            edgeWeightSlider->setValue(stringToInteger(edge->label()));
        }

        /* 选择某项时清除任何已显示的匹配，以便
         * 颜色正确。
         */
        currMatching.reset();
    }

    void MatchmakerGUI::entityCreated(GraphEditor::Entity* entity) {
        /* 节点需要名称。 */
        if (auto* node = dynamic_cast<GraphEditor::Node*>(entity)) {
            node->label(string(1, 'a' + node->index()));
        }
        /* 边需要权重。 */
        if (auto* edge = dynamic_cast<GraphEditor::Edge*>(entity)) {
            edge->label(to_string(edgeWeightSlider->getValue()));
        }
    }

    void MatchmakerGUI::actionPerformed(GObservable* source) {
        if (source == loadButton) {
            userLoad();
        } else if (source == newButton) {
            userNewGraph();
        } else if (editor && source == saveButton) {
            userSave();
        } else if (editor && source == deleteButton) {
            if (somethingSelected) deleteSelected();
        } else if (editor && source == perfectMatchButton) {
            findPerfectMatching();
        } else if (editor && source == maxWeightMatchButton) {
            findMaxWeightMatching();
        }
    }

    /* 拖动滑块会更改边权重。 */
    void MatchmakerGUI::changeOccurredIn(GObservable* source) {
        if (editor && editor->selectedEdge() && source == edgeWeightSlider) {
            /* 查看这是否改变了值。如果是，需要将图标记为
             * 已变脏。
             */
            int nextValue = edgeWeightSlider->getValue();
            int currValue = stringToInteger(editor->selectedEdge()->label());

            if (nextValue != currValue) {
                editor->selectedEdge()->label(to_string(edgeWeightSlider->getValue()));
                requestRepaint();
                dirty();
            }
        }
    }

    void MatchmakerGUI::deleteSelected() {
        if (editor->selectedNode()) {
            editor->deleteNode(editor->selectedNode());
        } else if (editor->selectedEdge()) {
            editor->deleteEdge(editor->selectedEdge());
        } else {
            error("Something is selected, but no node or edge is selected?");
        }
    }

    void MatchmakerGUI::setEditorBounds() {
        if (editor) editor->viewer()->setBounds(contentArea());
    }

    void MatchmakerGUI::windowResized() {
        setEditorBounds();
        ProblemHandler::windowResized();
    }

    void MatchmakerGUI::drawWelcomeMessage() {
        auto render = TextRender::construct(kWelcome, contentArea(), kWelcomeFont);
        render->alignCenterVertically();
        render->alignCenterHorizontally();
        render->draw(window());
    }

    void MatchmakerGUI::drawInstructions() {
        auto render = TextRender::construct(kInstructions, contentArea(), kInstructionsFont);
        render->alignCenterVertically();
        render->alignCenterHorizontally();
        render->draw(window());
    }

    GRectangle MatchmakerGUI::contentArea() {
        return { 0, 0, window().getCanvasWidth(), window().getCanvasHeight() };
    }

    /* 序列化当前状态。 */
    void MatchmakerGUI::save() {
        /* TODO：写入完成前不要覆盖源文件。
         * 使用 mkstemp，写入该处，完成后再移动。
         */
        ofstream output(currFilename);
        if (!output) error("Cannot open " + currFilename + " for writing.");

        output << editor->viewer()->toJSON();
    }

    bool MatchmakerGUI::userSave() {
        if (isNew) {
            string newName = GFileChooser::showSaveDialog(&window(), "Save File", kBaseDir, "*" + kFileExtension);
            if (newName == "") return false;

            currFilename = newName;
            fileLabel->setLabel(getTail(currFilename));

            /* 不再是新文件——我们刚选择了该文件！ */
            isNew = false;
        }

        save();

        dirty(false);
        GOptionPane::showMessageDialog(&window(), "Graph " + currFilename + " was saved!");
        return true;
    }

    bool MatchmakerGUI::handleUnsavedChanges() {
        if (!isDirty) return true;

        auto result = GOptionPane::showConfirmDialog(&window(), kUnsavedChanges, kUnsavedChangesTitle, GOptionPane::CONFIRM_YES_NO_CANCEL);

        /* 明确的“否”表示“好的，我要丢弃这些内容。” */
        if (result == GOptionPane::CONFIRM_NO) {
            return true;
        }

        /* “取消”表示“等一下，我不是想这么做。” */
        if (result == GOptionPane::CONFIRM_CANCEL) {
            return false;
        }

        /* 否则，他们打算保存。 */
        return userSave();
    }

    void MatchmakerGUI::userNewGraph() {
        if (!handleUnsavedChanges()) return;

        newGraph();
        saveButton->setEnabled(true);
    }

    void MatchmakerGUI::newGraph() {
        currFilename = kUntitledGraph;

        auto viewer = make_shared<GraphEditor::Viewer<>>();
        viewer->type(GraphEditor::Type::UNDIRECTED);

        initEditor(viewer);

        isNew = true;
        dirty();
    }

    void MatchmakerGUI::load(const string& filename) {
        currFilename = filename;
        fileLabel->setLabel(getTail(currFilename));

        ifstream input(filename);
        if (!input) throw runtime_error("Error opening file: " + filename);
        initEditor(make_shared<GraphEditor::Viewer<>>(JSON::parse(input)));

        isNew = false;
    }

    void MatchmakerGUI::userLoad() {
        /* 警告用户存在未保存的更改。 */
        if (!handleUnsavedChanges()) {
            return;
        }

        /* 让用户选择文件；如果未选择，则不执行任何操作。 */
        string filename = GFileChooser::showOpenDialog(&window(), "Choose Graph", kBaseDir, "*" + kFileExtension);
        if (filename == "") return;

        load(filename);
        saveButton->setEnabled(true);
    }

    void MatchmakerGUI::dirty(bool dirtyBit) {
        if (dirtyBit) {
            if (!isDirty) {
                isDirty = true;
                fileLabel->setText(getTail(currFilename) + "*");
            }
        } else {
            if (isDirty) {
                isDirty = false;
                fileLabel->setText(getTail(currFilename));
            }
        }
    }

    bool MatchmakerGUI::shuttingDown() {
        return handleUnsavedChanges();
    }

    void MatchmakerGUI::findPerfectMatching() {
        /* 提取图。 */
        Map<string, Set<string>> graph;
        auto g = editor->viewer();

        /* 安装节点。 */
        g->forEachNode([&](GraphEditor::Node* node) {
            graph[node->label()] = {};
        });

        /* 安装边。 */
        g->forEachEdge([&](GraphEditor::Edge* edge) {
            auto src = edge->from()->label();
            auto dst = edge->to()->label();

            graph[src] += dst;
            graph[dst] += src;
        });

        /* 取消所有选择；当前不处理节点/边。
         *
         * 此操作必须最先执行，因为它会清除所有
         * 现有配对。
         */
        editor->setActive(nullptr);

        Set<Pair> matching;
        if (hasPerfectMatching(graph, matching)) {
            /* 存储此匹配。 */
            currMatching.reset(new Set<Pair>(matching));

            /* 需要重绘。 */
            requestRepaint();
        } else {
            currMatching.reset();
            requestRepaint();

            GOptionPane::showMessageDialog(&window(), kNoPerfectMatching, kNoPerfectMatchingTitle);
        }
    }

    void MatchmakerGUI::findMaxWeightMatching() {
        /* 提取图。 */
        Map<string, Map<string, int>> graph;
        auto g = editor->viewer();

        /* 安装节点。 */
        g->forEachNode([&](GraphEditor::Node* node) {
            graph[node->label()] = {};
        });

        /* 安装边。 */
        g->forEachEdge([&](GraphEditor::Edge* edge) {
            auto src = edge->from()->label();
            auto dst = edge->to()->label();

            graph[src][dst] = stringToInteger(edge->label());
            graph[dst][src] = stringToInteger(edge->label());
        });

        /* 取消所有选择；当前不处理节点/边。
         *
         * 此操作必须最先执行，因为它会清除所有
         * 现有配对。
         */
        editor->setActive(nullptr);

        /* 存储此匹配。 */
        currMatching.reset(new Set<Pair>(maximumWeightMatching(graph)));

        /* 需要重绘。 */
        requestRepaint();
    }

    const string kMatchedColor   = "#ffd320";     // 滑块高亮颜色
    const string kMatchedBorderColor = "#000000"; // 黑色

    const string kUnmatchedColor = "#e0e0e0";       // 灰色
    const string kUnmatchedBorderColor = "#c0c0c0"; // 更深的灰色


    void MatchmakerGUI::drawGraph() {
        unordered_map<GraphEditor::Node*, GraphEditor::NodeStyle> nodeStyles;
        unordered_map<GraphEditor::Edge*, GraphEditor::EdgeStyle> edgeStyles;

        /* 如果存在匹配，则相应地对节点进行颜色编码。 */
        if (currMatching) {
            auto graph = editor->viewer();

            /* 最初，所有节点都以未匹配状态绘制。 */
            GraphEditor::NodeStyle unmatchedNodeStyle;
            unmatchedNodeStyle.borderColor = kUnmatchedBorderColor;
            unmatchedNodeStyle.fillColor   = kUnmatchedColor;
            unmatchedNodeStyle.textColor   = kUnmatchedBorderColor;

            graph->forEachNode([&](GraphEditor::Node* node) {
                nodeStyles[node] = unmatchedNodeStyle;
            });

            /* 最初，所有边都未匹配。 */
            GraphEditor::EdgeStyle unmatchedEdgeStyle;
            unmatchedEdgeStyle.lineColor     = kUnmatchedBorderColor;
            unmatchedEdgeStyle.labelColor = kUnmatchedBorderColor;

            graph->forEachEdge([&](GraphEditor::Edge* edge) {
                edgeStyles[edge] = unmatchedEdgeStyle;
            });

            /* 高亮显示匹配的节点和边。 */
            GraphEditor::NodeStyle matchedNodeStyle;
            matchedNodeStyle.borderColor = kMatchedBorderColor;
            matchedNodeStyle.fillColor   = kMatchedColor;
            matchedNodeStyle.lineWidth  *= 2;

            GraphEditor::EdgeStyle matchedEdgeStyle;
            matchedEdgeStyle.lineColor      = kMatchedBorderColor;
            matchedEdgeStyle.lineWidth *= 2;

            for (Pair p: *currMatching) {
                auto src = graph->nodeLabeled(p.first());
                auto dst = graph->nodeLabeled(p.second());

                nodeStyles[src] = matchedNodeStyle;
                nodeStyles[dst] = matchedNodeStyle;

                auto edge = graph->edgeBetween(src, dst);
                edgeStyles[edge] = matchedEdgeStyle;
            }

        }

        editor->draw(window().getCanvas(), nodeStyles, edgeStyles);
    }
}

GRAPHICS_HANDLER("Matchmaker", GWindow& window) {
    return make_shared<MatchmakerGUI>(window);
}
