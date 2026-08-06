#include "Matchmaker.h"
#include "Matching/graphtypes.h"
#include <limits>
using namespace std;

Set<Pair> fastMaxWeightMatching(const Map<string, Map<string, int>>& links) {
    /* 将链接线性化为可预测顺序。 */
    Map<int, string> order;
    Map<string, int> toIndex;
    for (string name: links) {
        int index = order.size() + 1;
        order[index] = name;
        toIndex[name] = index;
    }

    /* 构建图。 */
    auto graph = EdRothberg::NewGraph(links.size());
    for (const auto& src: links) {
        for (const auto& dst: links[src]) {
            if (toIndex[src] < toIndex[dst]) {
                EdRothberg::AddEdge(graph, toIndex[src], toIndex[dst], links[src][dst]);
            }
        }
    }

    /* 运行匹配。 */
    auto matching = EdRothberg::WeightedMatch(graph);
    EdRothberg::FreeGraph(graph);

    /* 转换为键值对。 */
    Set<Pair> result;
    for (const auto& entry: matching) {
        result.add({ order[entry.first], order[entry.second] });
    }

    return result;
}

namespace {
    Set<Pair> fastMaxCardinalityMatching(const Map<string, Set<string>>& links) {
        /* 转换为每条边成本均为 1 的图。 */
        Map<string, Map<string, int>> newLinks;
        for (const auto& src: links) {
            for (const auto& dst: links[src]) {
                newLinks[src][dst] = 1;
            }
        }

        /* 现在，在这个新图中寻找最大权重匹配。 */
        return fastMaxWeightMatching(newLinks);
    }
}

bool hasPerfectMatching(const Map<string, Set<string>>& possibleLinks, Set<Pair>& matching) {
    matching = fastMaxCardinalityMatching(possibleLinks);
    return matching.size() * 2 == possibleLinks.size();
}

Set<Pair> fastMWMCMatching(const Map<string, Map<string, int>>& possibleLinks) {
    /* 人为将所有边成本增加一定数值，使选择以下方案始终更好：
     * 边越多，而不是越少。
     */
    int maxEdge = 0;
    for (const string& src: possibleLinks) {
        for (const string& dst: possibleLinks[src]) {
            maxEdge = max(maxEdge, possibleLinks[src][dst]);
        }
    }

    Map<string, Map<string, int>> newLinks;
    for (const string& src: possibleLinks) {
        for (const string& dst: possibleLinks[src]) {
            /* 每条边的增量等于所有项目按以下方式配对时得到的分数：
             * 最大值。现在，任何匹配都必须包含最多数量的边。
             */
            newLinks[src][dst] = possibleLinks[src][dst] + (maxEdge + 1) * possibleLinks.size();
        }
    }

    return fastMaxWeightMatching(newLinks);
}
