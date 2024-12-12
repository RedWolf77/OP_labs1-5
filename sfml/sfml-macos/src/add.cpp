#include "add.h"
#include <iostream>

void show_graph(std::vector<std::vector<int>>& graph, GraphType type) {
    switch (type) {
        case GraphType::EDGE_LIST:
            std::cout << "Список ребер" << std::endl;
            for (const std::vector<int>& edge : graph) {
                std::cout << "{" << edge[0] << ", " << edge[1] << "}, ";
            }
            std::cout << std::endl;
            break;
        case GraphType::ADJACENCY_MATRIX:
            std::cout << "Матрица смежности" << std::endl;
            for (const std::vector<int>& row : graph) {
                for (const int& elem : row) {
                    std::cout << elem << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            break;
        case GraphType::ADJACENCY_LIST:
            std::cout << "Список смежности" << std::endl;
            for (int i = 0; i < graph.size(); i++) {
                std::cout << i + 1 << ": ";
                for (const int& elem : graph[i]) {
                    std::cout << elem << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        default:
            break;
    }

}
