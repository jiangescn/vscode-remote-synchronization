#include "MazeGenerator.h"
#include <utility>
#include <random>
#include <vector>
#include <map>
#include "strlib.h"
#include "grid.h"
#include "hashset.h"
#include "queue.h"
#include "vector.h"
using namespace std;

namespace {
    /* 创建给定大小的空白网格迷宫。 */
    Grid<MazeCell*> blankMaze(int numRows, int numCols) {
        Grid<MazeCell*> result(numRows, numCols);
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                result[row][col] = new MazeCell();
            }
        }
        return result;
    }

    /* 表示迷宫中一条可能边的类型。两个 MazeCell 各自
     * 也包含在这里，以及用于链接它们的字段。
     */
    struct EdgeBuilder {
        /* 要连接哪两条边。 */
        MazeCell* first;
        MazeCell* second;

        /* 如何链接它们。 */
        MazeCell* MazeCell::* firstField;
        MazeCell* MazeCell::* secondField;
    };

    /* 在指定范围内生成随机数。我们使用它代替
     * 使用 std::uniform_int_distribution，因为 std::uniform_int_distribution
     * 不具备跨平台兼容性。
     */
    int mtRandomBetween(int low, int high, mt19937& generator) {
        return low + generator() % (high - low + 1);
    }

    /* 生成 0 到 1 之间的随机实数。我们使用它代替
     * 使用 std::uniform_real_distribution，因为 std::uniform_real_distribution
     * 不具备跨平台兼容性。
     */
    double mtRandomProbability(mt19937& generator) {
        while (true) {
            uint32_t value = generator();
            uint32_t max   = numeric_limits<decltype(value)>::max();

            if (value != max) {
                return double(value) / max;
            }
        }
    }

    /* 返回网格迷宫中可能出现的所有边。 */
    vector<EdgeBuilder> allPossibleEdgesFor(const Grid<MazeCell*>& maze) {
        vector<EdgeBuilder> result;
        for (int row = 0; row < maze.numRows(); row++) {
            for (int col = 0; col < maze.numCols(); col++) {
                if (row + 1 < maze.numRows()) {
                    result.push_back({ maze[row][col], maze[row + 1][col], &MazeCell::south, &MazeCell::north });
                }
                if (col + 1 < maze.numCols()) {
                    result.push_back({ maze[row][col], maze[row][col + 1], &MazeCell::east, &MazeCell::west });
                }
            }
        }
        return result;
    }

    /* 并查集 FIND 操作。 */
    MazeCell* repFor(const map<MazeCell*, MazeCell*>& reps, MazeCell* cell) {
        while (reps.at(cell) != cell) {
            cell = reps.at(cell);
        }
        return cell;
    }

    /* 使用 Fischer-Yates 洗牌算法打乱边。我们提供自己的
     * 实现，因为 Windows、Mac 上的 std::shuffle 实现
     * Windows 和 Linux 上不保证具有相同的行为。
     */
    void shuffleEdges(vector<EdgeBuilder>& edges, mt19937& generator) {
        for (size_t i = 0; i < edges.size(); i++) {
            size_t j = mtRandomBetween(i, edges.size() - 1, generator);
            swap(edges[i], edges[j]);
        }
    }

    /* 使用随机化 Kruskal 算法创建给定大小的随机迷宫
     * 算法。边会被打乱并逐条加回，前提是
     * 使每次插入都连接两个不连通区域。
     */
    Grid<MazeCell*> makeMaze(int numRows, int numCols, mt19937& generator) {
        auto maze = blankMaze(numRows, numCols);

        auto edges = allPossibleEdgesFor(maze);
        shuffleEdges(edges, generator);

        /* 并查集结构；由于 N 很小，因此未使用路径压缩。 */
        map<MazeCell*, MazeCell*> representatives;
        for (auto* elem: maze) {
            representatives[elem] = elem;
        }

        /* 运行随机化 Kruskal 算法构建迷宫。 */
        int edgesLeft = numRows * numCols - 1;
        for (size_t i = 0; edgesLeft > 0 && i < edges.size(); i++) {
            auto edge = edges[i];

            /* 查看它们是否已经链接。 */
            auto* rep1 = repFor(representatives, edge.first);
            auto* rep2 = repFor(representatives, edge.second);

            /* 如果尚未链接，则链接它们。 */
            if (rep1 != rep2) {
                representatives[rep1] = rep2;

                edge.first->*edge.firstField   = edge.second;
                edge.second->*edge.secondField = edge.first;

                edgesLeft--;
            }
        }
        if (edgesLeft != 0) error("Unable to build maze.");

        return maze;
    }

    /* 清除给定节点组之间的所有链接。 */
    void clearGraph(Vector<MazeCell*>& nodes) {
        for (auto* node: nodes) {
            *node = MazeCell();
        }
    }

    /* 从给定节点返回随机未分配链接；如果没有则返回 nullptr
     * 它们都已赋值。
     */
    MazeCell* MazeCell::* randomFreePortOf(MazeCell* cell, mt19937& generator) {
        Vector<MazeCell* MazeCell::*> ports;
        if (cell->east  == nullptr) ports += &MazeCell::east;
        if (cell->west  == nullptr) ports += &MazeCell::west;
        if (cell->north == nullptr) ports += &MazeCell::north;
        if (cell->south == nullptr) ports += &MazeCell::south;
        if (ports.isEmpty()) return nullptr;

        int port = mtRandomBetween(0, ports.size() - 1, generator);
        return ports[port];
    }

    /* 使用 Erdos-Renyi 随机图模型的变体。我们设置
     * 任意节点对连通的概率为 ln(n) / n，
     * 然后人为约束图，使任何节点的度数都不
     * 四个或更多。我们以此方式生成迷宫，直到找到一个
     * 已连接。
     */
    bool erdosRenyiLink(Vector<MazeCell*>& nodes, mt19937& generator) {
        /* 所有内容连通的概率很高。 */
        double threshold = log(nodes.size()) / nodes.size();

        for (int i = 0; i < nodes.size(); i++) {
            for (int j = i + 1; j < nodes.size(); j++) {
                if (mtRandomProbability(generator) <= threshold) {
                    auto iLink = randomFreePortOf(nodes[i], generator);
                    auto jLink = randomFreePortOf(nodes[j], generator);

                    /* 糟糕，没有空闲链接。 */
                    if (iLink == nullptr || jLink == nullptr) {
                        return false;
                    }

                    nodes[i]->*iLink = nodes[j];
                    nodes[j]->*jLink = nodes[i];
                }
            }
        }

        return true;
    }

    /* 返回给定迷宫是否完全连通。 */
    bool isConnected(const Vector<MazeCell*>& maze) {
        HashSet<MazeCell*> visited;
        Queue<MazeCell*> frontier;
        frontier.enqueue(maze[0]);

        while (!frontier.isEmpty()) {
            auto* curr = frontier.dequeue();

            if (!visited.contains(curr)) {
                visited += curr;

                if (curr->east  != nullptr) frontier.enqueue(curr->east);
                if (curr->west  != nullptr) frontier.enqueue(curr->west);
                if (curr->north != nullptr) frontier.enqueue(curr->north);
                if (curr->south != nullptr) frontier.enqueue(curr->south);
            }
        }

        return visited.size() == maze.size();
    }

    /* 生成随机曲折迷宫。其工作方式是反复生成
     * 不断生成随机图，直到找到连通图。
     */
    Vector<MazeCell*> makeTwistyMaze(int numNodes, mt19937& generator) {
        Vector<MazeCell*> result;
        for (int i = 0; i < numNodes; i++) {
            result += new MazeCell();
        }

        /* 不断生成迷宫，直到得到连通迷宫。 */
        do {
            clearGraph(result);
        } while (!erdosRenyiLink(result, generator) || !isConnected(result));

        return result;
    }

    /* 返回两个节点是否相邻。 */
    bool areAdjacent(MazeCell* first, MazeCell* second) {
        return first->east  == second ||
               first->west  == second ||
               first->north == second ||
               first->south == second;
    }

    /* 使用 Floyd-Warshall 算法计算所有
     * 迷宫中的节点对。结果是一个表，其中 table[i][j] 为
     * maze[i] 与 maze[j] 之间的最短路径距离。
     */
    Grid<int> allPairsShortestPaths(const Vector<MazeCell*>& maze) {
        /* Floyd-Warshall 算法。用“无穷大”值填充网格。 */
        Grid<int> result(maze.size(), maze.size(), maze.size() + 1);

        /* 将节点到自身的距离设为 0。 */
        for (int i = 0; i < maze.size(); i++) {
            result[i][i] = 0;
        }

        /* 将边的距离设为 1。 */
        for (int i = 0; i < maze.size(); i++) {
            for (int j = 0; j < maze.size(); j++) {
                if (areAdjacent(maze[i], maze[j])) {
                    result[i][j] = 1;
                }
            }
        }

        /* 动态规划步骤。通过允许以下路径继续扩展路径
         * 节点之间。
         */
        for (int i = 0; i < maze.size(); i++) {
            Grid<int> next(result.numRows(), result.numCols());
            for (int j = 0; j < maze.size(); j++) {
                for (int k = 0; k < maze.size(); k++) {
                    next[j][k] = min(result[j][k], result[j][i] + result[i][k]);
                }
            }
            result = next;
        }

        return result;
    }

    /* 给定不同节点列表，返回其距离“分数”，
     * 它是按排序顺序表示两两距离的数字序列
     * 顺序。
     */
    Vector<int> scoreOf(const Vector<int>& nodes, const Grid<int>& distances) {
        Vector<int> result;

        for (int i = 0; i < nodes.size(); i++) {
            for (int j = i + 1; j < nodes.size(); j++) {
                result += distances[nodes[i]][nodes[j]];
            }
        }

        sort(result.begin(), result.end());
        return result;
    }

    /* 给定网格，返回四个节点的组合，使其总分
     * （两两距离的有序列表）在某种意义下尽可能大
     * 字典序意义上。
     */
    Vector<int> remoteLocationsIn(const Grid<int>& distances) {
        Vector<int> result = {0, 1, 2, 3};

        /* 可以递归完成此操作，但由于“只有”四层循环
         * 那我们就直接这样做。:-)
         */
        for (int i = 0; i < distances.numRows(); i++) {
            for (int j = i + 1; j < distances.numRows(); j++) {
                for (int k = j + 1; k < distances.numRows(); k++) {
                    for (int l = k + 1; l < distances.numRows(); l++) {
                        Vector<int> curr = { i, j, k, l };
                        if (scoreOf(curr, distances) > scoreOf(result, distances)) {
                            result = curr;
                        }
                    }
                }
            }
        }

        return result;
    }

    /* 将文本迷宫中的项目复制到网格迷宫。 */
    void fillItems(Grid<MazeCell*>& maze, const Vector<string>& textMaze) {
        for (int row = 0; row < maze.numRows(); row++) {
            for (int col = 0; col < maze.numCols(); col++) {
                /* 奇数编号的位置是间隙位置。 */
                switch (textMaze[2 * row][2 * col]) {
                case 'S':
                    maze[row][col]->whatsHere = Item::SPELLBOOK;
                    break;
                case 'P':
                    maze[row][col]->whatsHere = Item::POTION;
                    break;
                case 'W':
                    maze[row][col]->whatsHere = Item::WAND;
                    break;
                case '*':
                    maze[row][col]->whatsHere = Item::NOTHING;
                    break;
                default:
                    error("Unknown character found when copying items.");
                }
            }
        }
    }

    /* 根据文本模式填充迷宫中的墙。 */
    void addWalls(Grid<MazeCell*>& maze, const Vector<string>& textMaze) {
        for (int row = 0; row < maze.numRows(); row++) {
            for (int col = 0; col < maze.numCols(); col++) {
                /* 如果可以，则向下查看。 */
                if (row + 1 < maze.numRows() && textMaze[2 * row + 1][2 * col] == '|') {
                    maze[row][col]->south = maze[row + 1][col];
                    maze[row + 1][col]->north = maze[row][col];
                }
                /* 如果可以，则向左查看。 */
                if (col + 1 < maze.numCols() && textMaze[2 * row][2 * col + 1] == '-') {
                    maze[row][col]->east = maze[row][col + 1];
                    maze[row][col + 1]->west = maze[row][col];
                }
            }
        }
    }

    /* 验证文本迷宫的结构是否正确。 */
    void validateMaze(const Vector<string>& textMaze) {
        /* 行数应为奇数，因为每隔一个位置才是一个地点。
         * 列数同样如此。
         */
        if (textMaze.size() % 2 != 1) {
            error("Maze should have an odd number of rows.");
        }
        if (textMaze[0].size() % 2 != 1) {
            error("Maze should have an odd number of columns.");
        }

        int numRows = 1 + textMaze.size() / 2;
        int numCols = 1 + textMaze[0].size() / 2;

        for (int row = 0; row < numRows; row++) {
            if (textMaze[row].size() != textMaze[0].size()) {
                error("Not all rows in the maze have the same size.");
            }
        }

        /* 确认所有奇数/奇数坐标对处都是空格。 */
        for (int row = 0; row + 1 < numRows; row++) {
            for (int col = 0; col + 1 < numCols; col++) {
                if (textMaze[2 * row + 1][2 * col + 1] != ' ') {
                    error("Found non-blank character where blank was expected.");
                }
            }
        }

        /* 确认每个位置都是 *、S、P 或 W。 */
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                switch (textMaze[2 * row][2 * col]) {
                case 'P': case 'S': case 'W': case '*':
                    /* 不执行任何操作。 */
                    break;
                default:
                    error("Unknown character found at lattice point.");
                }
            }
        }

        /* 确认每面墙都是 -、| 或空白。 */
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                if (row + 1 < numRows &&
                    textMaze[2 * row + 1][2 * col] != ' ' &&
                    textMaze[2 * row + 1][2 * col] != '|') {
                    error("Unknown wall character.");
                }
                if (col + 1 < numCols &&
                    textMaze[2 * row][2 * col + 1] != ' ' &&
                    textMaze[2 * row][2 * col + 1] != '-') {
                    error("Unknown wall character.");
                }
            }
        }
    }
}

const int kNumRows = 4;
const int kNumCols = 4;

MazeCell* mazeFor(const string& name) {
    /* 使用提供的种子初始化生成器。从此时起，只
     * 使用此来源生成随机数。
     */
    mt19937 generator(hashCode(name, kNumRows, kNumCols));
    auto maze = makeMaze(kNumRows, kNumCols, generator);

    /* 将物品和起始位置彼此远离放置。 */
    Vector<MazeCell*> linearMaze;
    for (MazeCell* cell: maze) {
        linearMaze += cell;
    }
    auto distances = allPairsShortestPaths(linearMaze);
    auto locations = remoteLocationsIn(distances);

    /* 放置物品。 */
    linearMaze[locations[1]]->whatsHere = Item::SPELLBOOK;
    linearMaze[locations[2]]->whatsHere = Item::POTION;
    linearMaze[locations[3]]->whatsHere = Item::WAND;

    /* 我们从位置 0 开始。 */
    return linearMaze[locations[0]];
}

const int kNumTwistyRooms = 12;

MazeCell* twistyMazeFor(const string& name) {
    /* 使用提供的种子初始化生成器。从此时起，只
     * 使用此来源生成随机数。
     */
    mt19937 generator(hashCode(name, kNumTwistyRooms));
    auto maze = makeTwistyMaze(kNumTwistyRooms, generator);

    /* 找出所有节点对之间的距离。 */
    auto distances = allPairsShortestPaths(maze);

    /* 选择一个四元组，使各点之间的最小距离最大，
     * 并将其用作物品/起始位置。
     */
    auto locations = remoteLocationsIn(distances);

    /* 将物品放在那里。 */
    maze[locations[1]]->whatsHere = Item::SPELLBOOK;
    maze[locations[2]]->whatsHere = Item::POTION;
    maze[locations[3]]->whatsHere = Item::WAND;

    return maze[locations[0]];
}

/* 将迷宫的文本表示转换为 Grid<MazeCell*> 对象。 */
Grid<MazeCell*> toMaze(const Vector<string>& textMaze) {
    validateMaze(textMaze);

    int numRows = 1 + textMaze.size() / 2;
    int numCols = 1 + textMaze[0].size() / 2;

    auto result = blankMaze(numRows, numCols);
    fillItems(result, textMaze);
    addWalls(result, textMaze);
    return result;
}
