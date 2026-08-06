#pragma once

#include <vector>

namespace EdRothberg {
    struct node_entry {
        int degree;
        struct edge_ent *adj_list;
    };
    typedef struct node_entry *Graph;

    struct edge_ent {
        int endpoint;
        int label;
        int label2;
        struct edge_ent *nextedge;
        struct edge_ent *prevedge;
        struct edge_ent *otheredge;
    };
    typedef struct edge_ent *Edge;

    Graph NewGraph(int size);
    int RemoveEdge(Graph graph, Edge edge), NumEdges(Graph g);
    Edge FindEdge(Graph graph, int i, int j);
    void FreeGraph(Graph graph);
    
    /* 向图中添加一条边。如果该边已存在，则会创建
     * 平行边。
     */
    void AddEdge (Graph g, int n, int m, int label);

    /* 计算一般图中的最大权重匹配。返回值为
     * 所有匹配对的列表，其中每个匹配恰好出现一次。
     * 未匹配的顶点会被省略。
     *
     * 此函数计算最大权匹配，但不一定是
     * 完美匹配。可以通过缩放来强制匹配为完美匹配
     * 边上的权重，使不选择某条边的惩罚
     * 超过其他边可能的最大总和。
     */
    std::vector<std::pair<int, int>> WeightedMatch (Graph gptr);
}
