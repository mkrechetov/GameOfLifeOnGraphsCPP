#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <chrono>

#include "graph.h"
#include "gol.h"

bool if_isomorphic_hash(Graph g, Graph h, size_t max_iter) {
    if (g.adjm.size() != h.adjm.size()) {
        return false;
    }
    size_t n = g.adjm.size();

    std::vector<GOL> g_games, h_games;
    g_games.reserve(n);
    h_games.reserve(n);

    for (size_t i=0; i<n; ++i) {
        std::set<size_t> i_alive{ i };
        g_games.emplace_back(1, 1, 1, &g, i_alive);
        h_games.emplace_back(1, 1, 1, &h, i_alive);
    }

    std::vector<size_t> g_labels, h_labels, g_labels_new, h_labels_new, g_labels_sorted, h_labels_sorted;
    for (size_t i=0; i<n; ++i) {
        g_labels.push_back(1);
        h_labels.push_back(1);
        g_labels_new.push_back(1);
        h_labels_new.push_back(1);
        g_labels_sorted.push_back(1);
        h_labels_sorted.push_back(1);
    }

    std::hash<size_t> hasher;

    for (size_t k=0; k<max_iter; ++k) {
        for (size_t i=0; i<n; ++i) {
            g_games[i].Evolve();
            h_games[i].Evolve();
        }


        for (size_t i=0; i<n; ++i) {
            g_labels_new[i] = g_labels[i];
            h_labels_new[i] = h_labels[i];

            g_labels_sorted.clear();
            h_labels_sorted.clear();
            for (size_t j=0; j<n; ++j) {
                if (i != j) {

                    auto it = g_games[i].alive.find(j);
                    if (it != g_games[i].alive.end()) {
                        g_labels_sorted.emplace_back(hasher(g_labels[j]));
                    }

                    it = h_games[i].alive.find(j);
                    if (it != h_games[i].alive.end()) {
                        h_labels_sorted.emplace_back(hasher(h_labels[j]));
                    }
                }
            }
            std::sort(g_labels_sorted.begin(), g_labels_sorted.end());
            std::sort(h_labels_sorted.begin(), h_labels_sorted.end());

            for (size_t jhash : g_labels_sorted) {g_labels_new[i] = hasher(g_labels_new[i] + jhash);}
            for (size_t jhash : h_labels_sorted) {h_labels_new[i] = hasher(h_labels_new[i] + jhash);}
        }

        g_labels_sorted.clear();
        h_labels_sorted.clear();
        for (size_t i=0; i<n; ++i) {
            g_labels[i] = g_labels_new[i];
            h_labels[i] = h_labels_new[i];

            g_labels_sorted.push_back(g_labels_new[i]);
            h_labels_sorted.push_back(h_labels_new[i]);
        }

        std::sort(g_labels_sorted.begin(), g_labels_sorted.end());
        std::sort(h_labels_sorted.begin(), h_labels_sorted.end());

        for (size_t i=0; i<n; ++i) {
            if (g_labels_sorted[i] != h_labels_sorted[i]) {
                return false;
            }
        }

    }

    return true;
}

void test_collection(std::string filename, size_t max_iter) {
    auto Glst = read_file(filename);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i=0; i<Glst.size(); ++i) {
        for (int j=i+1; j<Glst.size(); ++j) {
            if (if_isomorphic_hash(Glst[i], Glst[j], max_iter)) {
                std::cout << "Graphs " << i << " and " << j;
                std::cout << " coincide under GOL-test" << std::endl;
            }
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Tested " << Glst.size() << " non-isomorphic graphs in ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

}

int main() {
    test_collection("/home/mk/CLionProjects/GameOfLifeOnGraphsCPP/collections/graph7c.g6", 5);
    return 0;
}
