#pragma once
#include <vector>

enum class GraphType {
    EDGE_LIST,
    ADJACENCY_MATRIX,
    ADJACENCY_LIST
};

void show_graph(std::vector<std::vector<int>>& edge_list, GraphType type);