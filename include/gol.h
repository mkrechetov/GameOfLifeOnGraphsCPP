#ifndef GAMEOFLIFEONGRAPHSCPP_GOL_H
#define GAMEOFLIFEONGRAPHSCPP_GOL_H

#include "set"
#include "vector"
#include "graph.h"

class GOL {
private:
    int a, d, r;
    Graph* graph;
public:
    std::set<size_t> alive;

    GOL(){};
    GOL(int a, int d, int r, Graph* g, std::set<size_t> alive);
    void Evolve();
};

#endif //GAMEOFLIFEONGRAPHSCPP_GOL_H
