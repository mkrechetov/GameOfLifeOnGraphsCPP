#include "gol.h"

GOL::GOL(int a, int d, int r, Graph *g, std::set<size_t> alive) {
    this->a = a;
    this->d = d;
    this->r = r;
    this->graph = g;
    this->alive = std::move(alive);
}

std::set<size_t> GOL::Evolve() {
    size_t n = graph->adjm.size();

    // update alive vertices
    std::set<size_t> new_alive;
    for (size_t i=0; i<n; ++i) {
        int n_alive = 0;
        int n_dead = 0;

        for (size_t j=0; j<n; ++j) {
            if ((i != j) and (graph->adjm[i][j] == 1)){
                auto it = this->alive.find(j);
                if (it == this->alive.end()) {
                    n_dead += 1;
                }
                else {
                    n_alive += 1;
                }
            }
        }

        auto it = this->alive.find(i);
        if (it == this->alive.end()) {
            if (n_alive == this->r) {
                new_alive.insert(i);
            }
        }
        else {
            if ((n_alive >= this->a) and (n_dead >= this->d)) {
                new_alive.insert(i);
            }
        }


    }

    this->alive = new_alive;
    return new_alive;
}

size_t GOL::Complexity() {

    std::set<std::set<size_t>> history;
    history.insert(this->alive);
    size_t complexity = 1;

    while (true) {
        std::set<size_t> new_alive = this->Evolve();
        if (new_alive.empty()) {
            return complexity;
        }
        else {
            auto it = history.find(new_alive);
            if (it == history.end()) {
                history.insert(new_alive);
                complexity += 1;
            }
            else {
                return complexity;
            }
        }
    }
}
