#include "gol.h"

#include <utility>

GOL::GOL(int a, int d, int r, Graph *g, std::set<size_t> alive) {
    this->a = a;
    this->d = d;
    this->r = r;
    this->graph = g;
    this->alive = std::move(alive);
}

void GOL::Evolve() {
    size_t n = graph->adjm.size();
    std::set<size_t> new_alive;

    for (int i=0; i<n; ++i) {



    }
}
