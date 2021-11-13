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
    void print_adjm();
};

std::vector<Graph> read_file(std::string filename);

#endif //GAMEOFLIFEONGRAPHSCPP_GRAPH_H