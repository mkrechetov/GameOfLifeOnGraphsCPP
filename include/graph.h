#ifndef GAMEOFLIFEONGRAPHSCPP_GRAPH_H
#define GAMEOFLIFEONGRAPHSCPP_GRAPH_H
#include "string"
#include "vector"

class Graph{
public:
    std::vector<std::vector<size_t>> adjm;

    Graph()= default;;
    Graph(std::string g6);
    Graph(int n, int m, int seed);
    void PrintAdjM();
};

#endif //GAMEOFLIFEONGRAPHSCPP_GRAPH_H